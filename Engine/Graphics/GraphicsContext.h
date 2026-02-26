#pragma once

#include <d3d11.h> // Direct3D 11 보일러플레이트
#include <dxgi.h> // DXGI 장치 관련(swap chain)
#include <string>

namespace Craft
{
	class Win32Window;

	class GraphicsContext // 그래픽스 관련 기능 제공 및 리소스 관리 클래스
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Initialize(const Win32Window& window);

		void BeginScene(float red, float green, float blue); // 프레임 준비 함수
		void EndScene(uint32_t vsync); // 완성된 프레임을 모니터에 보내는 함수(chain swapping). vsync == 0이면 수직동기화 x

	private:
		void CreateDevice();
		void CreateSwapChain(const Win32Window& window);
		void CreateViewport(const Win32Window& window);
		void CreateRenderTargetView();

	private:
		// 장치류 리소스, 생성/해제를 API에 요청할 때 사용
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr; // draw call 발생
		IDXGISwapChain* swapChain = nullptr;
		ID3D11RenderTargetView* renderTargetView = nullptr;

		D3D11_VIEWPORT viewport = { }; // 화면크기(viewport), 클라영역을 얼만큼 쓸지 설정

		uint32_t width = 0, height = 0;
	};
}

