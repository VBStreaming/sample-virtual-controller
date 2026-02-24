#include <windows.h>
#include <ViGEm/Client.h>

#pragma comment(lib, "setupapi.lib")
#pragma once

class VirtualController {
private:
	PVIGEM_CLIENT client = nullptr;
	PVIGEM_TARGET pad = nullptr;
	DS4_REPORT report;
public:
	bool Initialize();


	void Release();
};