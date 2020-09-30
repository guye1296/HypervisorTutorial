#include "HvMajorFunctions.h"


NTSTATUS hvDefaultIrpHandler(
	IN struct _DEVICE_OBJECT* DeviceObject,
	IN OUT struct _IRP* Irp
)
{
	UNUSED_PARAMETER(DeviceObject);

	DbgPrint(__FUNCTION__ ": Handling IRP\n");

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	(void)IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}


NTSTATUS hvReadIrpHandler(
	IN struct _DEVICE_OBJECT* deviceObject,
	IN OUT struct _IRP* irp
)
{
	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


NTSTATUS hvWriteIrpHandler(
	IN struct _DEVICE_OBJECT* deviceObject,
	IN OUT struct _IRP* irp
)
{
	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


NTSTATUS hvCloseIrpHandler(
	IN struct _DEVICE_OBJECT* deviceObject,
	IN OUT struct _IRP* irp
)
{
	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


NTSTATUS hvCreateIrpHandler(
	IN struct _DEVICE_OBJECT* deviceObject,
	IN OUT struct _IRP* irp
)
{

	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}


NTSTATUS hvDeviceControlIrpHandler(
	IN struct _DEVICE_OBJECT* deviceObject,
	IN OUT struct _IRP* irp
)
{

	return hvDefaultIrpHandler(
		deviceObject,
		irp
	);
}
		


