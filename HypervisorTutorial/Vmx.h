#pragma once

#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>


namespace vmx 
{
	typedef struct _Vmcs {
		UINT8 buffer[PAGE_SIZE];
	} Vmcs;


	// vmxon regious physical address
	// should be a pointer to a page-alined 4K buffer
	// should have external linkge so it won't be declared multiple times
	extern SIZE_T vmxonRegionAddress;

	// check whether IA32_FEATURE_CONTROL_MSR[0] (lock bit) is turned on
	bool vmxNotLocked();


	// dirty hack so `enterVmxOperation` can be included in the namespace
	void enterVmxOperation();
}
