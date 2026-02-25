#pragma once

#include <Windows.h>
#include <string>
#include <stdint.h>

namespace Craft
{
	class Win32Window // WIN32 API로 생성하는 창 클래스
	{
	public:
		Win32Window(
			uint32_t width = 1280,
			uint32_t height = 800,
			HINSTANCE instance = nullptr,
			WNDPROC messageProcedure = nullptr
		);
		~Win32Window();

		bool Initialize();

		inline uint32_t Width() const { return width; }
		inline uint32_t Height() const { return height; }
		inline HWND Handle() const { return handle; }

	private:
		std::wstring title;
		std::wstring className = L"Craft Engine Class";

		uint32_t width = 0;
		uint32_t height = 0;

		HWND handle = nullptr; // 창 객체 핸들
		HINSTANCE instance = nullptr; // 프로그램 포인터
		WNDPROC messageProcedure = nullptr; // 메시지 처리 함수 포인터
	};
}

