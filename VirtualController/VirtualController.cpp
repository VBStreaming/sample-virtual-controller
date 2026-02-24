#include "VirtualController.h"
#include <iostream>


bool VirtualController::Initialize() {
	buttonMap['W'] = DS4_BUTTON_TRIANGLE;
	buttonMap['A'] = DS4_BUTTON_CIRCLE;
	buttonMap['S'] = DS4_BUTTON_CROSS;
	buttonMap['D'] = DS4_BUTTON_SQUARE;

	client = vigem_alloc();
	if (client == nullptr || !VIGEM_SUCCESS(vigem_connect(client))) {
		std::cerr << "ViGEmBus 드라이버 연결에 실패했습니다. 설치 여부를 확인하세요." << std::endl;
		return false;
	}

	pad = vigem_target_ds4_alloc();
	const auto res = vigem_target_add(client, pad);
	if (!VIGEM_SUCCESS(res)) {
		std::cerr << "가상 컨트롤러 연결 실패!" << std::endl;
		return false;
	}

	DS4_REPORT_INIT(&report);

	return true;
}

void VirtualController::Release() {
	if (client && pad) {
		vigem_target_remove(client, pad);
		vigem_target_free(pad);
		vigem_free(client);
	}
}

void VirtualController::UpdateState(DS4_BUTTONS button) {
	report.wButtons |= button;
}

void VirtualController::RunLoop() {
	std::cout << "가상 컨트롤러 작동 중... (W 키 = A 버튼)" << std::endl;
	std::cout << "프로그램을 종료하려면 'ESC' 키를 누르세요." << std::endl;
	
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;
		report.wButtons = 0;

		for (const auto& [key, button] : buttonMap) {
			if (GetAsyncKeyState(key)& 0x8000) {
				UpdateState(button);
			}
		}

		vigem_target_ds4_update(client, pad, report);
		Sleep(10);
	}
}