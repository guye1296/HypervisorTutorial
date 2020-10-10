#pragma once
#include <ntddk.h>
#include <cstddef>

// inspired by hvpp

namespace vmx
{

struct alignas(PAGE_SIZE) Vmcs {
	UINT32 revisionID;
	UINT32 abortIndicator;
private:
	UINT32 data[PAGE_SIZE - 2 * sizeof(UINT32)];
public:
	enum class Field {

	};

};

}
