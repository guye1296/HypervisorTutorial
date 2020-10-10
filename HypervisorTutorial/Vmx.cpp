#include <intrin.h>

#include "Vmx.h"
#include "Arch.h"
#include "Utilities.h"


bool vmx::enableVmxInFeatureControl()
{
	intel::msr::FeatureControl featureControl;

	// check if FEATURE_CONTROL_MSR is locked
	featureControl.all = __readmsr(intel::msr::FeatureControl::code);

	if (featureControl.fields.locked) {
		if (!featureControl.fields.vmxNonSmxEnabled) {
			DEBUG_TRACE_ERROR(
				"FEATURE_CONTROL_MSR is locked by BIOS, Virtualization can't be enabled"
			);
			return false;
		}
	}
	else {
		featureControl.fields.vmxSmxEnabled = true;
		featureControl.fields.vmxNonSmxEnabled = true;
		(void)__writemsr(intel::msr::FeatureControl::code, featureControl.all);
	}

	return true;
}


bool vmx::vmxSupportedByHardware()
{
	UINT32 cpuidResult[4];
	UINT32 eax = 1;

	__cpuid(reinterpret_cast<INT*>(cpuidResult), eax);
	auto constexpr cpuidFeatureEcxVmx = 1 << 5;
	auto constexpr cpuidInfoEcxIndex = 2;

	// check if vmx is supported by the processor
	return (cpuidFeatureEcxVmx & cpuidResult[cpuidInfoEcxIndex]);
}


void vmx::enableVmxOperation()
{
	// turn on 14th bit of cr4
	auto cr4 = __readcr4();
	cr4 |= (1 << 13);
	(void)__writecr4(cr4);
}
