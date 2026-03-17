#pragma once

#include <d3d11.h>		// Direct3D 11 �Ϲ����� ����.
#include <dxgi.h>		// DXGI ��ġ ����(����ü��).
#include <string>

// ��ġ(�׷���ī��).
// Direct3D���� "��ġ"�� �ٷ�� ��ü�� 3��.
// Device: ���ҽ� ����.
// DeviceContext: ������ ���ҽ��� �׷���ī�忡 �Ҵ�(���ε�)/��ο���.
// SwapChain(����ü��): �����-����Ʈ���� ��ȯ.
// RenderTargetView(���� Ÿ�� ��): ȭ�鿡 �׸� ������(�̹���) ���ҽ�.
// View(��): Ư���� ���ҽ� CPU<->GPU���� ������ ���� ���.
// -> CPU���� ���ҽ��� �����ϸ� �̰� ������ GPU���� �������� ����� �����.
// ������ ������(Forward Renderer) -> �츮�� �̰�.
// ���۵� ������(Deffered Renderer).

namespace Craft
{
	// ���漱��.
	class Win32Window;

	// �׷��Ƚ� ���� ����� ���� �� ���ҽ� ����.
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
		// ��ġ ����.
		void CreateDevice();
		void CreateSwapChain(const Win32Window& window);
		void CreateViewport(const Win32Window& window);

		// ���� Ÿ�� �� ����.
		void CreateRenderTargetView();

	private:
		// ��ġ��.
		// Direct3D ���ҽ��� �����ͷθ� �ٷ� �� ����.
		// ����/������ API�� ��û.
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		IDXGISwapChain* swapChain = nullptr;

		// ���ҽ�.
		// RTV - �׸��� ��� ���ҽ�.
		ID3D11RenderTargetView* renderTargetView = nullptr;

		// ����Ʈ.
		D3D11_VIEWPORT viewport = { };

		// ȭ�� ũ��.
		uint32_t width = 0;
		uint32_t height = 0;

		// ���� ����.
		static GraphicsContext* instance;
	};
}