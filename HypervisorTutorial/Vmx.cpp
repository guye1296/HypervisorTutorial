#include <intrin.h>

#include "Vmx.h"


static constexpr UINT64 IA32_FEATURE_CONTROL_MSR = 0x3A;


// calls `vmxon` with the dereference of `vmxonRegion`
extern "C" void vmxonInternal(SIZE_T* vmxonRegion);


SIZE_T vmx::vmxonRegionAddress = { 0 };


bool vmx::vmxNotLocked()
{
	UINT64 featureControlMsr =
		__readmsr(IA32_FEATURE_CONTROL_MSR);

	return 0x1 & featureControlMsr;
}


void vmx::enterVmxOperation()
{
	// turn on 14th bit of cr4
	auto cr4 = __readcr4();
	cr4 |= (1 << 13);
	(void)__writecr4(cr4);
	(void)vmxonInternal(&vmx::vmxonRegionAddress);

	// turn off VMX for now
	(void)__vmx_off();
}
