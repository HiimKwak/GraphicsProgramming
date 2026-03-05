#include "Engine.h"
#include "Win32Window.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Level/Level.h"
#include "Resource/MeshLoader.h"

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

		meshLoader = std::make_unique<MeshLoader>();

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

		// �޽��� ó�� ����.
		// â���� �߻��ϴ� �޽��� ó�� ����.
		// GetMessage - ���� ���(Blocking ���).
		// PeekMessage - �񵿱� ���(Non Blocking ���).
		// ����: ó���Ǳ� ������ �ٸ� ���� ����.
		// �񵿱�: ó������ �ʾƵ� �Ѿ.
		MSG msg = { };

		// â ���� �޽����� �߻��� ������ ����.
		while (msg.message != WM_QUIT)
		{
			// â �޽��� ó��.
			// �񵿱� ������� �޽����� ���Դ��� Ȯ��.
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				// ���޹��� �޽����� �����ϰ� ��ȯ.
				TranslateMessage(&msg);

				// ��ȯ�� �޽����� ó�� �Լ��� ����.
				DispatchMessage(&msg);
			}

			// â �޽����� ������ ���� ���� ó��.
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

					previousTime = currentTime;
				}
			}
		}
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