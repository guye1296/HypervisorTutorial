#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>

#include "Utilities.h"


constexpr WCHAR DOS_DEVICE_NAME[] = LR"(\DosDevices\MyHypervisor)";


extern void inline assemblyFunction1(void);

extern void inline assemblyFunction2(void);


extern "C"
{
	// @note: naming is against the convention due to `DriverEntry`
	//        being the driver's entrypoint
	DRIVER_INITIALIZE DriverEntry;
	DRIVER_UNLOAD driverUnload;
	DRIVER_DISPATCH hvDefaultIrpHandler;
}

#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, driverUnload)

NTSTATUS 
hvDefaultIrpHandler(
	_In_ struct _DEVICE_OBJECT* DeviceObject,
	_Inout_ struct _IRP* Irp
)
{
	UNUSED_PARAMETER(Irp);
	UNUSED_PARAMETER(DeviceObject);

	DbgPrint(__FUNCTION__ ": \n");

	return STATUS_NOT_SUPPORTED;
}

// `DriverEntry` and `driverUnload` should have C linkage
_Use_decl_annotations_
NTSTATUS DriverEntry(
	IN PDRIVER_OBJECT driverObject,
	IN PUNICODE_STRING registryPath
)
{
	UNUSED_PARAMETER(registryPath);

	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT deviceObject = nullptr;
	UNICODE_STRING driverName, dosDeviceName;

	DbgPrint(__FUNCTION__ ": loaded\n");

	RtlInitUnicodeString(&driverName, LR"(\Device\MyHypervisor)");
	RtlInitUnicodeString(&dosDeviceName, DOS_DEVICE_NAME);

	status = IoCreateDevice(
		driverObject,
		0,
		&driverName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		false,
		&deviceObject
	);

	if (STATUS_SUCCESS != status) {
		status = STATUS_FAILED_DRIVER_ENTRY;
		goto cleanup;
	}


	for (size_t i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; ++i) {
		driverObject->MajorFunction[i] = hvDefaultIrpHandler;
	}


	driverObject->DriverUnload = driverUnload;
	driverObject->Flags |= IO_TYPE_DEVICE;
	driverObject->Flags &= (~DO_DEVICE_INITIALIZING);

	status = IoCreateSymbolicLink(&dosDeviceName, &driverName);

cleanup:
	return status;
}

VOID driverUnload(PDRIVER_OBJECT driverObject)
{
	UNICODE_STRING symlinkName;
	RtlInitUnicodeString(&symlinkName, DOS_DEVICE_NAME);

	DbgPrint(__FUNCTION__ ": called\n");

	(void)IoDeleteDevice(driverObject->DeviceObject);
	(void)IoDeleteSymbolicLink(&symlinkName);
}
