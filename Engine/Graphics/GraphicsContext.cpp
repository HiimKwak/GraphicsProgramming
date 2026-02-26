#include "GraphicsContext.h"
#include "Core/Win32Window.h"
#include "Core/Common.h"

namespace Craft
{
	GraphicsContext::GraphicsContext()
	{
	}

	GraphicsContext::~GraphicsContext()
	{
		SafeRelease(device);
		SafeRelease(context);
		SafeRelease(swapChain);
	}

	void GraphicsContext::Initialize(const Win32Window& window)
	{
		width = window.Width();
		height = window.Height();

		CreateDevice();
		CreateSwapChain(window);
		CreateViewport(window);
		CreateRenderTargetView();

		context->RSSetViewports(1, &viewport); // 뷰포트 변경이 필요없으므로 여기서 한 번만 설정
	}

	void GraphicsContext::BeginScene(float red, float green, float blue)
	{
		context->OMSetRenderTargets(1, &renderTargetView, nullptr); // 도화지 설정
		float bgColor[4] = { red, green, blue, 1.f };
		context->ClearRenderTargetView(renderTargetView, bgColor); // 도화지 흰색으로 칠하기(내부적으로 memset함)
	}

	void GraphicsContext::EndScene(uint32_t vsync)
	{
		swapChain->Present(0, 0);
	}

	void GraphicsContext::CreateDevice()
	{
		uint32_t flag = 0;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG; // 설정 안해주면 디버그 정보가 안생김
#endif

		D3D_FEATURE_LEVEL featureLevels[] = // Direct3D API 버전 정보, 그래픽카드 지원 확인 
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		/*
		IDXGIAdapter* pAdapter,
		D3D_DRIVER_TYPE DriverType,
		HMODULE Software,
		UINT Flags,
		CONST D3D_FEATURE_LEVEL* pFeatureLevels,
		UINT FeatureLevels,
		UINT SDKVersion,
		ID3D11Device** ppDevice,
		D3D_FEATURE_LEVEL* pFeatureLevel,
		ID3D11DeviceContext** ppImmediateContext );
		*/
		HRESULT result = D3D11CreateDevice( // 오류 발생 시 음수 반환
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION, // dx11 sdk 버전 매크로, 임의 변경 x
			&device,
			nullptr,
			&context
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}
	}

	void GraphicsContext::CreateSwapChain(const Win32Window& window)
	{
		IDXGIFactory* factory = nullptr;
		HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		/*
		DXGI_MODE_DESC BufferDesc;
		DXGI_SAMPLE_DESC SampleDesc;
		DXGI_USAGE BufferUsage;
		UINT BufferCount;
		HWND OutputWindow;
		BOOL Windowed;
		DXGI_SWAP_EFFECT SwapEffect;
		UINT Flags;
		*/
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.Windowed = true; // 창모드로 시작
		swapChainDesc.OutputWindow = window.Handle();
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 화면 출력 용도로 버퍼 설정
		swapChainDesc.BufferCount = 2;
		// anti-aliasing에 샘플링 수준 설정 코드, 지금은 off(쓰려면 글카에게 먼저 물어봐야함)
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		// 버퍼(프레임 이미지) 설정
		swapChainDesc.BufferDesc.Width = window.Width();
		swapChainDesc.BufferDesc.Height = window.Height();
		// 이미지 픽셀 포맷
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // rgba(8x4=32비트), 픽셀 라이트이므로 부호없고(unsigned), 0~1 사이 정규화(normalized)
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discard는 즉시, sequential은 차례대로, flip_은 최신 API

		result = factory->CreateSwapChain(
			device,
			&swapChainDesc,
			&swapChain
		);
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		SafeRelease(factory);
	}

	void GraphicsContext::CreateViewport(const Win32Window& window)
	{
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.Width = static_cast<float>(window.Width());
		viewport.Height = static_cast<float>(window.Height());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
	}

	void GraphicsContext::CreateRenderTargetView()
	{
		ID3D11Texture2D* backbuffer = nullptr; // 백버퍼 정보 저장 변수
		HRESULT result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer)); // IID_PPV_ARGS(&backbuffer) = __uuidof(ID3D11Texture2D)

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		result = device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView // renderTargetView에 backbuffer 내용 복사했으므로 backbuffer 해제해줘야 함
		);

		if (FAILED(result))
		{
			SafeRelease(backbuffer);
			__debugbreak();
			return;
		}

		SafeRelease(backbuffer);

	}
}