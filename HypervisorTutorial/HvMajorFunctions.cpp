#include "HvMajorFunctions.h"
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
NTSTATUS hvCreateIrpHandler(
	IN PDEVICE_OBJECT deviceObject,
	IN OUT PIRP irp
)
{
	UNUSED_PARAMETER(deviceObject);

	DbgPrint("Entered " __FUNCTION__ "\n");

	if (!vmx::vmxNotLocked()) {
		irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
		goto cleanup;
	}

	// TODO: allocate space for the vmx region

	(void)vmx::enterVmxOperation();
	irp->IoStatus.Status = STATUS_SUCCESS;

cleanup:
	irp->IoStatus.Information = 0;
	(void)IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;


	
}


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
		


