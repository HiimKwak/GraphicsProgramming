#pragma once

#include <d3d11.h>		
#include <dxgi.h>		
#include <string>

namespace Craft
{
	class Win32Window;

	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Initialize(const Win32Window& window);

		void BeginScene(float red, float green, float blue);

		void EndScene(uint32_t vsync);

		void OnResize(uint32_t width, uint32_t height);

		inline ID3D11Device& GetDevice() const { return *device; }
		inline ID3D11DeviceContext& GetDeviceContext() const { return *context; }

		static GraphicsContext& Get();

	private:
		void CreateDevice();
		void CreateSwapChain(const Win32Window& window);
		void CreateViewport(const Win32Window& window);

		void CreateRenderTargetView();
		void CreateDepthStencilView(uint32_t width, uint32_t height);

	private:
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr;

		ID3D11RenderTargetView* renderTargetView = nullptr;

		ID3D11DepthStencilView* depthStencilView = nullptr;

		D3D11_VIEWPORT viewport = { };

		uint32_t width = 0;
		uint32_t height = 0;

		static GraphicsContext* instance;
	};
}