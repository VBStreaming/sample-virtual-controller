#include "VirtualController.h"
#include <iostream>


bool VirtualController::Initialize() {
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