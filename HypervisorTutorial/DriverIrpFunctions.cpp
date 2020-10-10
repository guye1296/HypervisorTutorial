#include "DriverIrpFunctions.h"
#include "Utilities.h"
#include "Vmx.h"


static VOID printIrpInfo(
	IN PIRP irp
) 
{
	PIO_STACK_LOCATION  irpSp;
	irpSp = IoGetCurrentIrpStackLocation(irp);

	PAGED_CODE();

	DEBUG_TRACE_INFO("\tIrp->AssociatedIrp.SystemBuffer = 0x%p",
		irp->AssociatedIrp.SystemBuffer);
	DEBUG_TRACE_INFO("\tIrp->UserBuffer = 0x%p", irp->UserBuffer);
	DEBUG_TRACE_INFO("\tirpSp->Parameters.DeviceIoControl.Type3InputBuffer = 0x%p",
		irpSp->Parameters.DeviceIoControl.Type3InputBuffer);
	DEBUG_TRACE_INFO("\tirpSp->Parameters.DeviceIoControl.InputBufferLength = %d",
		irpSp->Parameters.DeviceIoControl.InputBufferLength);
	DEBUG_TRACE_INFO("\tirpSp->Parameters.DeviceIoControl.OutputBufferLength = %dn",
		irpSp->Parameters.DeviceIoControl.OutputBufferLength);
	return;
}


NTSTATUS hvDefaultIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	UNUSED_PARAMETER(deviceObject);

	DbgPrint(__FUNCTION__ ": Handling IRP\n");

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	(void)IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}


NTSTATUS hvReadIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


NTSTATUS hvWriteIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


NTSTATUS hvCloseIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


// enter VMX operation upon creating the device
#pragma warning(disable : 4102)
NTSTATUS hvCreateIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	UNUSED_PARAMETER(deviceObject);

	DbgPrint("Entered " __FUNCTION__ "\n");

	(void)vmx::enableVmxOperation();
	DEBUG_TRACE_INFO("VMX Enabled");

cleanup:
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	(void)IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
#pragma warning(default : 4102)

NTSTATUS hvDeviceControlIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	UNUSED_PARAMETER(deviceObject);
	constexpr auto deviceType = FILE_DEVICE_UNKNOWN;
	auto status = STATUS_SUCCESS;

	enum ControlCodes {
		InDirect = 
			CTL_CODE(deviceType, 0x900, METHOD_IN_DIRECT, FILE_ANY_ACCESS),
		OutDirect = 
			CTL_CODE(deviceType, 0x901, METHOD_OUT_DIRECT, FILE_ANY_ACCESS),
		Buffered = 
			CTL_CODE(deviceType, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS),
		Neither = 
		CTL_CODE(deviceType, 0x903, METHOD_NEITHER, FILE_ANY_ACCESS)
	};

	// guarantees that IRQL <= APC
	PAGED_CODE();

	auto irpStackPointer = IoGetCurrentIrpStackLocation(irp);

	auto inputerBufferLength = 
		irpStackPointer->Parameters.DeviceIoControl.InputBufferLength;
	auto outputBufferLength = 
		irpStackPointer->Parameters.DeviceIoControl.OutputBufferLength;

	if(!inputerBufferLength || !outputBufferLength) {
		DEBUG_TRACE_ERROR("both IO passed are of length 0");
		status = STATUS_INVALID_DEVICE_REQUEST;
		goto cleanup;
	}

	// Determine which I/O control code was	specified
	switch (irpStackPointer->Parameters.DeviceIoControl.IoControlCode) {
	case ControlCodes::Buffered:
	{
		// TODO: figure out if macro is needed for block
		PAGED_CODE();
		DEBUG_TRACE_INFO("Called METHOD_BUFFERED");
		printIrpInfo(irp);

		DEBUG_TRACE_INFO("Data From user: ");
		auto inputBuffer = irp->AssociatedIrp.SystemBuffer;
		printBuffer(inputBuffer, inputerBufferLength);

		constexpr auto data = "This is from device driver";
		// can't be constexpr for some reason
		auto dataLength = strlen(data);

		auto outputBuffer = irp->AssociatedIrp.SystemBuffer;

		// copy device driver data to user
		RtlCopyBytes(outputBuffer, data, dataLength);
		irp->IoStatus.Information = min(dataLength, outputBufferLength);
		status = STATUS_SUCCESS;
	}
		break;

	// All of the following are unsupported
	case ControlCodes::InDirect:
	case ControlCodes::OutDirect:
	case ControlCodes::Neither:
		irp->IoStatus.Information = 0;
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

cleanup:
	(void)IoCompleteRequest(irp, IO_NO_INCREMENT);
	irp->IoStatus.Status = status;
	return status;
}
