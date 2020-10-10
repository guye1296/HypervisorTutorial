#pragma once

#include <ntddk.h>

namespace intel
{
	namespace msr
	{
		typedef union _FeatureControl{
			static constexpr UINT64 code = 0x3A;

			UINT64 all;
			struct {
				UINT64 locked : 1;
				UINT64 vmxNonSmxEnabled : 1;
				UINT64 vmxSmxEnabled : 1;
			} fields;
		} FeatureControl;

		typedef union _VmxBasic {
			static constexpr UINT64 code = 0x480;

			UINT64 all;
			struct {
				UINT64 revisionIdentifier : 31;
			} fields;
		} VmxBasic;
	}
}
