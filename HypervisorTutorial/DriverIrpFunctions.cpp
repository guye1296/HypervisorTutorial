#include "DriverIrpFunctions.h"
#include "Utilities.h"
#include "Vmx.h"


#pragma warning(disable: 4505)
// TODO: Implement
static VOID printIrpInfo(
	IN PIRP irp
) 
{
	UNUSED_PARAMETER(irp);
}
#pragma warning(default: 4505)


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

	/* 
	* Will be enabled in later chapters
	if (!vmx::vmxEnabledByBios()) {
		DEBUG_TRACE_ERROR("Vmx operation not avialable :(");
		goto cleanup;
	}
	*/

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

	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}
		


