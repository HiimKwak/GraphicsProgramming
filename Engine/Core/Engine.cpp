#include "Engine.h"
#include "Win32Window.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Level/Level.h"
#include "Resource/MeshLoader.h"
#include "Resource/TextureLoader.h"
#include "Input.h"
#include <windowsx.h>

namespace Craft
{
	Engine* Engine::instance = nullptr;
	Engine::Engine()
	{
		assert(!instance);
		instance = this;
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

		meshLoader = std::make_unique<MeshLoader>();
		textureLoader = std::make_unique<TextureLoader>();

		input = std::make_unique<Input>();

		return true;
	}

	void Engine::Run()
	{
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		int64_t currentTime = counter.QuadPart;
		int64_t previousTime = currentTime;

		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		float oneFrameTime = 1.0f / setting.framerate;

		MSG msg = { };

		while (msg.message != WM_QUIT)
		{
			if (isQuit) break;

			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
			else
			{
				QueryPerformanceCounter(&counter);
				currentTime = counter.QuadPart;

				float deltaTime = static_cast<float>(currentTime - previousTime)
					/ static_cast<float>(frequency.QuadPart);

				if (deltaTime >= oneFrameTime)
				{
					OnInitialized();

					BeginPlay();

					Tick(deltaTime);

					Draw();

					if (mainLevel)
					{
						mainLevel->ProcessAddAndDestroyActors();
					}

					if (nextLevel)
					{
						if (mainLevel)
						{
							mainLevel.reset();
						}

						mainLevel = std::move(nextLevel);
						nextLevel.reset();
					}

					input->ResetInputs();

					previousTime = currentTime;
				}
			}
		}
	}

	void Engine::Quit()
	{
		isQuit = true;
	}

	void Engine::OnResize(uint32_t width, uint32_t height)
	{
		if (graphicsContext)
			graphicsContext->OnResize(width, height);

		window->SetWidthAndHeight(width, height);
	}

	Engine& Engine::Get()
	{
		assert(instance);
		return *instance;
	}

	uint32_t Engine::GetWidth() const
	{
		return window->Width();
	}

	uint32_t Engine::GetHeight() const
	{
		return window->Height();
	}

	LRESULT Engine::Win32MessageProcedure(
		HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
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

		case WM_SIZE:
		{
			if (wparam == SIZE_MINIMIZED) break;
			if (!instance) break;

			uint32_t width = LOWORD(lparam);
			uint32_t height = HIWORD(lparam);
			instance->OnResize(width, height);
		}
		return 0;

		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		{
			if (GetFocus() != handle) break; // only if focused on the program window
			if (!Input::IsValid()) break;

			bool isKeyUp = (lparam & ((int64_t)1 << 30)) != 0;
			bool isKeyDown = (lparam & ((int64_t)1 << 31)) == 0;

			if (isKeyUp != isKeyDown)
			{
				uint32_t vkCode = static_cast<uint32_t>(wparam);
				Input::Get().SetKeyUpDown(vkCode, isKeyUp, isKeyDown);
			}
		}
		return 0;

		case WM_LBUTTONDOWN:
		{
			if (Input::IsValid()) break;

			Input::Get().SetButtonUpDown(0, false, true);
		}
		return 0;
		case WM_LBUTTONUP:
		{
			if (Input::IsValid()) break;

			Input::Get().SetButtonUpDown(0, true, false);
		}
		return 0;

		case WM_RBUTTONDOWN:
		{
			if (Input::IsValid()) break;

			Input::Get().SetButtonUpDown(1, false, true);
		}
		return 0;
		case WM_RBUTTONUP:
		{
			if (Input::IsValid()) break;

			Input::Get().SetButtonUpDown(1, true, false);
		}
		return 0;

		case WM_MOUSEMOVE:
		{
			if (!Input::IsValid()) break;

			//int xPosition = LOWORD(lparam);
			//int yPosition = HIWORD(lparam);
			int xPosition = GET_X_LPARAM(lparam);
			int yPosition = GET_Y_LPARAM(lparam);

			Input::Get().SetMousePosition(xPosition, yPosition);
		}
		return 0;

		}
		return DefWindowProc(handle, message, wparam, lparam);
	}

	void Engine::OnInitialized()
	{
		if (!mainLevel || mainLevel->HasInitialized())
		{
			return;
		}

		mainLevel->OnInitialized();
	}

	void Engine::BeginPlay()
	{
		if (!mainLevel)
		{
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		if (!mainLevel)
		{
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		if (!mainLevel)
		{
			return;
		}

		graphicsContext->BeginScene(0.6f, 0.7f, 0.8f);

		mainLevel->Draw();
		renderer->DrawScene();

		graphicsContext->EndScene(setting.vsync);
	}
}