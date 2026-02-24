#include <map>
#include <windows.h>
#include <ViGEm/Client.h>
#include <iostream>

#pragma comment(lib, "setupapi.lib")
#pragma once


class VirtualController {
private:
	PVIGEM_CLIENT client = nullptr;
	PVIGEM_TARGET pad = nullptr;
	DS4_REPORT report;

	std::map<int, DS4_BUTTONS> buttonMap;
public:
	bool Initialize();
	void RunLoop();
	void UpdateState(DS4_BUTTONS button);
	void Release();
};