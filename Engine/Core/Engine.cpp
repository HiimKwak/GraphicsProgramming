#include "Engine.h"
#include "Win32Window.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"

namespace Craft
{
	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}

	bool Engine::Initialize(HINSTANCE instance)
	{
		window = std::make_unique<Win32Window>(
			setting.width,
			setting.height,
			setting.title,
			instance,
			Win32MessageProcedure
		);

		if (!window->Initialize())
		{
			__debugbreak();
			return false;
		}

		graphicsContext = std::make_unique<GraphicsContext>();
		graphicsContext->Initialize(*window);

		renderer = std::make_unique<Renderer>();
		renderer->Initialize();

		return true;
	}

	void Engine::Run()
	{
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
			else
			{
				graphicsContext->BeginScene(0.6f, 0.7f, 0.8f);
				renderer->DrawScene();
				graphicsContext->EndScene(setting.vsync);
			}
		}
	}

	LRESULT Engine::Win32MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(handle, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(handle, &ps);
		}
		return 0;
		}

		return DefWindowProc(handle, message, wparam, lparam);
	}
}