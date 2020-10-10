#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>

#include "OsServices.h"


uintptr_t os::virtualToPhysical(PVOID virtualAddress) {
	return static_cast<uintptr_t>(
		MmGetPhysicalAddress(virtualAddress).QuadPart
	);
}


size_t os::getCpuNum()
{
	return KeQueryActiveProcessorCount(0);
}


void os::callOnEachCpu(Callback callback, PVOID context)
{
	// function is executed at IRQL_IPI
	// cast arguments to windows-like arguments
	(void)KeIpiGenericCall(
		reinterpret_cast<PKIPI_BROADCAST_WORKER>(callback), 
		reinterpret_cast<ULONG_PTR>(context)
	);
}


uintptr_t os::physicalToVirtual(uintptr_t physicalAddress) {
	PHYSICAL_ADDRESS windowsPhysicalAddress;
	windowsPhysicalAddress.QuadPart = physicalAddress;
	return reinterpret_cast<uintptr_t>(MmGetVirtualForPhysical(windowsPhysicalAddress));
}