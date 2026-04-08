#include "GraphicsContext.h"
#include "Core/Win32Window.h"
#include "Core/Common.h"
#include <cassert>

namespace Craft
{
	GraphicsContext* GraphicsContext::instance = nullptr;

	GraphicsContext::GraphicsContext()
	{
		assert(!instance);
		instance = this;
	}

	GraphicsContext::~GraphicsContext()
	{
		SafeRelease(device);
		SafeRelease(context);
		SafeRelease(swapChain);
		SafeRelease(renderTargetView);
		SafeRelease(depthStencilView);
	}

	void GraphicsContext::Initialize(const Win32Window& window)
	{
		width = window.Width();
		height = window.Height();

		CreateDevice();

		CreateSwapChain(window);

		CreateViewport(window);

		CreateRenderTargetView();

		CreateDepthStencilView(width, height);

		context->RSSetViewports(1, &viewport);
	}

	void GraphicsContext::BeginScene(float red, float green, float blue)
	{
		context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

		float backgroundColor[4] = { red, green, blue, 1.0f };
		context->ClearRenderTargetView(renderTargetView, backgroundColor);

		context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void GraphicsContext::EndScene(uint32_t vsync)
	{
		swapChain->Present(vsync, 0);
	}

	void GraphicsContext::OnResize(uint32_t width, uint32_t height)
	{
		if (!device || !context || !swapChain) return;

		context->ClearState();
		context->Flush();

		SafeRelease(renderTargetView);
		SafeRelease(depthStencilView);

		ThrowIfFailed(swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0), L"Failed to resize swap-chain buffer.");

		CreateRenderTargetView();
		CreateDepthStencilView(width, height);

		viewport.Width = static_cast<float>(width);
		viewport.Height = static_cast<float>(height);
		context->RSSetViewports(1, &viewport); // Rasterizer needs viewport size for calculating pixels,
	}

	GraphicsContext& GraphicsContext::Get()
	{
		assert(instance);
		return *instance;
	}

	void GraphicsContext::CreateDevice()
	{
		uint32_t flag = 0;

#if _DEBUG
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

		/*
		*   IDXGIAdapter* pAdapter,
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
		HRESULT result = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
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
		HRESULT result = CreateDXGIFactory(
			__uuidof(IDXGIFactory),
			reinterpret_cast<void**>(&factory)
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		/*
		*   DXGI_MODE_DESC BufferDesc;
			DXGI_SAMPLE_DESC SampleDesc;
			DXGI_USAGE BufferUsage;
			UINT BufferCount;
			HWND OutputWindow;
			BOOL Windowed;
			DXGI_SWAP_EFFECT SwapEffect;
			UINT Flags;
		*/
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.Windowed = true;
		swapChainDesc.OutputWindow = window.Handle();
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferDesc.Width = window.Width();
		swapChainDesc.BufferDesc.Height = window.Height();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

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
		ID3D11Texture2D* backbuffer = nullptr;
		HRESULT result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		result = device->CreateRenderTargetView(
			backbuffer, nullptr, &renderTargetView
		);

		if (FAILED(result))
		{
			SafeRelease(backbuffer);

			__debugbreak();
			return;
		}

		SafeRelease(backbuffer);
	}

	void GraphicsContext::CreateDepthStencilView(uint32_t width, uint32_t height)
	{
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ID3D11Texture2D* depthStencilTexture = nullptr;
		ThrowIfFailed(device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilTexture), L"Failed to create depth stencil texture");

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = depthStencilDesc.Format;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		ThrowIfFailed(device->CreateDepthStencilView(depthStencilTexture, &depthStencilViewDesc, &depthStencilView), L"Failed to create depth stencil view");

		SafeRelease(depthStencilTexture);
	}
}