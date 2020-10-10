#include <intrin.h>

#include "VirtualProcessor.h"
#include "Utilities.h"
#include "OsServices.h"
#include "Arch.h"


VirtualProcessor::VirtualProcessor()
{
	DEBUG_TRACE_INFO(
		"VMCS Physical address: %p", os::virtualToPhysical(&m_vmcs)
	);

	DEBUG_TRACE_INFO(
		"VMXON Region Physical address: %p", os::virtualToPhysical(&m_vmxonRegion)
	);
}


bool VirtualProcessor::start()
{
	// get physical address
	auto vmxonPhysicalAddress =
		os::virtualToPhysical(&m_vmxonRegion);

	HV_ASSERT((0 == vmxonPhysicalAddress % PAGE_SIZE), "wrong alignment");

	// write revision identifiers
	intel::msr::VmxBasic vmxBasic;
	vmxBasic.all = __readmsr(intel::msr::VmxBasic::code);

	DEBUG_TRACE_INFO(
		"VMX revision id: %d", vmxBasic.fields.revisionIdentifier
	);

	m_vmcs.revisionID = vmxBasic.fields.revisionIdentifier;
	m_vmxonRegion.revisionID = m_vmcs.revisionID;

	auto errorStatus = __vmx_on(&vmxonPhysicalAddress);
	if (errorStatus) {
		DEBUG_TRACE_ERROR(
			"__vmx_on failed with code %d", errorStatus
		);
		return false;
	}

	return true;
}
