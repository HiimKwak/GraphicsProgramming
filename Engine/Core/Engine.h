#pragma once

#include <Windows.h>
#include <memory>
#include <string>

namespace Craft
{
	class Win32Window;
	class GraphicsContext;

	struct EngineSetting
	{
		uint32_t width = 1280;
		uint32_t height = 800;
		std::wstring title = L"Craft Engine";
		float framerate = 120.0f;
		uint32_t vsync = 0;
	};

	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		bool Initialize(HINSTANCE instance);

		void Run();

	protected:
		static LRESULT CALLBACK Win32MessageProcedure(HWND handle, UINT message, WPARAM wparam, LPARAM lparam);

	protected:
		std::unique_ptr<Win32Window> window;
		std::unique_ptr<GraphicsContext> graphicsContext;

		EngineSetting setting;
	};
}

