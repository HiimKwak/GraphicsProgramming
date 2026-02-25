#include <windows.h>
#include <string>
#include <stdint.h>

// 창 메시지 처리할 떄 사용
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
int main()
{
	// Register the window class: 운영체제에 창 등록할 때 사용할 클래스명(unique해야함)
	std::wstring className = L"Craft Engine Window";
	std::wstring title = L"Craft Engine";

	// 창 크기
	uint32_t width = 1280;
	uint32_t height = 800;

	HINSTANCE hInstance = GetModuleHandle(nullptr); // 이 프로그램의 포인터를 운영체제가 구해서 넣어줌
	// 창 생성에 필요한 정보(구조체) 채우기
	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance; // 프로그램 포인터
	wc.lpszClassName = className.c_str(); // wstring을 wchar 로우 포인터로 변경해주는 함수

	if (!RegisterClass(&wc)) // 등록 실패 핸들
		return 0;

	// Create the window.
	HWND hwnd = CreateWindow(
		className.c_str(),                     // Window class
		title.c_str(),    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		CW_USEDEFAULT, CW_USEDEFAULT, // 위치
		width, height, // 크기

		nullptr,       // Parent window    
		nullptr,       // Menu
		hInstance,  // Instance handle
		nullptr        // Additional application data
	);

	// 창 생성 실패 시
	if (hwnd == NULL)
		return 0;

	ShowWindow(hwnd, SW_SHOW);

	// 게임 루프같은 메시지 처리 루프.
	MSG msg = { };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 들어온 메시지 변환
			TranslateMessage(&msg);
			// 변환한 메시지 처리 함수(WindowProc)에 전달
			DispatchMessage(&msg);
		}
		// 창 메세지가 없으면 엔진 로직 처리

	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}