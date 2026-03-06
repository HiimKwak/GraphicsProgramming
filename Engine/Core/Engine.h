#pragma once

#include "Core/Common.h"
#include <Windows.h>
#include <memory>
#include <string>

namespace Craft
{
	class Win32Window;
	class GraphicsContext;
	class Level;
	class MeshLoader;
	class TextureLoader;

	struct EngineSetting
	{
		uint32_t width = 1280;
		uint32_t height = 800;
		std::wstring title = L"Craft Engine";
		float framerate = 120.0f;
		uint32_t vsync = 0;
	};

	class CRAFT_API Engine
	{
	public:
		Engine();
		virtual ~Engine();

		bool Initialize(HINSTANCE instance);

		void Run();

		template<typename T, typename ...Args,
			typename = std::enable_if_t<std::is_base_of<Level, T>::value>>
			void AddNewLevel(Args&&... args)
		{
			nextLevel = std::make_shared<T>(std::forward<Args>(args)...);
		}

	protected:
		static LRESULT CALLBACK Win32MessageProcedure(
			HWND handle,
			UINT message,
			WPARAM wparam,
			LPARAM lparam
		);

		void OnInitialized();
		void BeginPlay();
		void Tick(float deltaTime);
		void Draw();

	protected:
		std::unique_ptr<Win32Window> window;

		std::unique_ptr<GraphicsContext> graphicsContext;

		std::unique_ptr<class Renderer> renderer;
		std::unique_ptr<MeshLoader> meshLoader;
		std::unique_ptr<TextureLoader> textureLoader;

		std::shared_ptr<Level> mainLevel;

		std::shared_ptr<Level> nextLevel;

		EngineSetting setting;
	};
}