#include "Win32Window.h"

namespace Craft
{
	Win32Window::Win32Window(
		uint32_t width,
		uint32_t height,
		const std::wstring& title,
		HINSTANCE instance,
		WNDPROC messageProcedure)
		: width(width), height(height), title(title),
		instance(instance),
		messageProcedure(messageProcedure)
	{
	}

	Win32Window::~Win32Window()
	{
		// â ��� ����.
		UnregisterClass(className.c_str(), instance);
	}

	bool Win32Window::Initialize()
	{
		// â ������ �ʿ��� ����(����ü) ä���.
		WNDCLASS wc = { };
		wc.lpfnWndProc = messageProcedure;
		wc.hInstance = instance;       // ���α׷� ������.
		wc.lpszClassName = className.c_str();

		// Ŭ���� ���.
		if (!RegisterClass(&wc))
		{
			return 0;
		}

		// â ũ�� ���ϱ�.
		RECT rect = {};
		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		// â ũ��.
		uint32_t windowWidth = rect.right - rect.left;
		uint32_t windowHeight = rect.bottom - rect.top;

		// â ���� ��ġ �����.
		uint32_t positionX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
		uint32_t positionY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

		// â ��ü ����.
		handle = CreateWindow(
			className.c_str(),               // Window class
			title.c_str(),                   // Window text
			WS_OVERLAPPEDWINDOW,            // Window style

			// ��ġ �� ũ��
			positionX, positionY,
			windowWidth, windowHeight,

			nullptr,       // Parent window    
			nullptr,       // Menu
			instance,      // Instance handle
			nullptr        // Additional application data
		);

		// â ���� ���� ó��.
		if (!handle)
		{
			return false;
		}

		// â�� Ŭ���̾�Ʈ ���� ũ�� ���ϱ�.
		//RECT rect2;
		//GetClientRect(hwnd, &rect2);

		// â ���̱� ����.
		ShowWindow(handle, SW_SHOW);
		return true;
	}
}