#pragma once
#include <ntddk.h>

#include "Vmcs.h"
#include "Vmx.h"


class VirtualProcessor
{
private:
	vmx::Vmcs m_vmxonRegion;
	vmx::Vmcs m_vmcs;
public:
	VirtualProcessor();

	// note: running on IRQL_IPI
	bool start();
};

