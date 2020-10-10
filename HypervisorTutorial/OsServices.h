#pragma once

typedef void(*Callback)(void);

namespace os
{
	size_t getCpuNum();

	void callOnEachCpu(Callback callback, PVOID context);

	uintptr_t virtualToPhysical(PVOID virtualAddress);

	uintptr_t physicalToVirtual(uintptr_t physicalAddres);
}


