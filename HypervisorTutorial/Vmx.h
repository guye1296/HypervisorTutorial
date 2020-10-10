#pragma once

#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>


namespace vmx 
{
	// try to enable VMX in FEATURE_CONTROL MSR
	// returns false if can't be enabled because locked
	bool enableVmxInFeatureControl();


	// check if vmx is supported by hardware
	bool vmxSupportedByHardware();


	inline bool vmxSupported() {
		return vmxSupportedByHardware() && enableVmxInFeatureControl();
	}

	void enableVmxOperation();
}
