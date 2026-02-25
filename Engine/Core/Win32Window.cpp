#include "Win32Window.h"

namespace Craft
{
	Win32Window::Win32Window(
		uint32_t width,
		uint32_t height,
		HINSTANCE instance,
		WNDPROC messageProcedure
	) : width(width), height(height), instance(instance), messageProcedure(messageProcedure)
	{
	}

	Win32Window::~Win32Window()
	{
		UnregisterClass(className.c_str(), instance); // 창 등록 해제
	}

	bool Win32Window::Initialize()
	{
		// 창 생성에 필요한 정보(구조체) 채우기
		WNDCLASS wc = { };
		wc.lpfnWndProc = messageProcedure;
		wc.hInstance = instance; // 프로그램 포인터
		wc.lpszClassName = className.c_str(); // wstring을 wchar 로우 포인터로 변경해주는 함수

		if (!RegisterClass(&wc)) // 등록 실패 핸들
			return 0;

		/* 창 클라이언트 영역 딱 맞춰주기 */
		RECT rect = {};
		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		uint32_t windowWidth = rect.right - rect.left;
		uint32_t windowHeight = rect.bottom - rect.top;

		/* 창 생성 위치 가운데 고정 */
		uint32_t positionX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
		uint32_t positionY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

		// Create the window.
		handle = CreateWindow(
			className.c_str(),                     // Window class
			title.c_str(),    // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			positionX, positionY, // 위치
			windowWidth, windowHeight, // 크기

			nullptr,       // Parent window    
			nullptr,       // Menu
			instance,  // Instance handle
			nullptr        // Additional application data
		);

		// 창 생성 실패 시
		if (!handle)
			return false;


		ShowWindow(handle, SW_SHOW);
		return true;
	}
}