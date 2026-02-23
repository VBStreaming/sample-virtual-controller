

#include <windows.h>
#include <ViGEm/Client.h>
#include <iostream>

#pragma comment(lib, "setupapi.lib")

int main()
{
    auto client = vigem_alloc();
    if (client == nullptr || !VIGEM_SUCCESS(vigem_connect(client))) {
        std::cerr << "ViGEmBus 드라이버 연결에 실패했습니다. 설치 여부를 확인하세요." << std::endl;
        return -1;
    }

    // 2. 가상 듀얼쇼크4 컨트롤러 생성 및 연결
    auto pad = vigem_target_ds4_alloc();
    const auto target_add_res = vigem_target_add(client, pad);
    if (!VIGEM_SUCCESS(target_add_res)) {
        std::cerr << "가상 컨트롤러 연결 실패!" << std::endl;
        return -1;
    }

    std::cout << "가상 컨트롤러 작동 중... (W 키 = A 버튼)" << std::endl;
    std::cout << "프로그램을 종료하려면 'ESC' 키를 누르세요." << std::endl;

    DS4_REPORT report;
    DS4_REPORT_INIT(&report);

    // 3. 입력 감지 루프
    while (true) {
        // ESC 키를 누르면 루프 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;
        report.wButtons = 0;

        // 'W' 키 상태 체크
        if (GetAsyncKeyState('W') & 0x8000) {
            report.wButtons |= DS4_BUTTON_TRIANGLE; // A 버튼 누름
        }
        if (GetAsyncKeyState('A') & 0x8000) {
            report.wButtons |= DS4_BUTTON_CIRCLE;
        }

        // 상태 업데이트 전송
        vigem_target_ds4_update(client, pad, report);

        // CPU 점유율 과다 방지를 위해 짧은 대기 (10ms)
        Sleep(10);
    }

    // 4. 리소스 정리
    vigem_target_remove(client, pad);
    vigem_target_free(pad);
    vigem_free(client);

    return 0;
}

