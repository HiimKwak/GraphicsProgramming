#pragma once

#include <Windows.h>
#include <string>
#include <stdint.h>

namespace Craft
{
	class Win32Window
	{
	public:
		Win32Window(
			uint32_t width = 1280,
			uint32_t height = 800,
			const std::wstring& title = L"",
			HINSTANCE instance = nullptr,
			WNDPROC messageProcedure = nullptr
		);
		~Win32Window();

		bool Initialize();

		inline uint32_t Width() const { return width; }
		inline uint32_t Height() const { return height; }
		inline void SetWidthAndHeight(uint32_t newWidth, uint32_t newHeight) {
			width = newWidth;
			height = newHeight;
		}
		inline HWND Handle() const { return handle; }

	private:
		std::wstring title;
		std::wstring className = L"Craft Engine Class";
		uint32_t width = 0;
		uint32_t height = 0;
		HWND handle = nullptr;
		HINSTANCE instance = nullptr;
		WNDPROC messageProcedure = nullptr;
	};
}