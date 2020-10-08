#include <intrin.h>

#include "Vmx.h"


static constexpr UINT64 IA32_FEATURE_CONTROL_MSR = 0x3A;


// calls `vmxon` with the dereference of `vmxonRegion`
extern "C" void vmxonInternal(SIZE_T* vmxonRegion);


SIZE_T vmx::vmxonRegionAddress = { 0 };


bool vmx::vmxEnabledByBios()
{
	bool locked;
	bool vmxNonSmxEnabled;

	// check if FEATURE_CONTROL_MSR is locked
	UINT64 featureControlMsr =
		__readmsr(IA32_FEATURE_CONTROL_MSR);

	locked = featureControlMsr & 0x1;
	vmxNonSmxEnabled = featureControlMsr & (0x1 << 1);

	// currently just assuming that not running in SMX
	// TODO: fix
	return locked && vmxNonSmxEnabled;
}


void vmx::enableVmxOperation()
{
	// turn on 14th bit of cr4
	auto cr4 = __readcr4();
	cr4 |= (1 << 13);
	(void)__writecr4(cr4);
}
