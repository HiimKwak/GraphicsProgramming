#include "Texture.h"
#include "Graphics/GraphicsContext.h"

namespace Craft
{
#define STB_IMAGE_IMPLEMENTATION
#include "Library/StbImage.h"

	Texture::Texture(const std::string& name, BindType bindType) : name(name), bindType(bindType)
	{
		data = std::make_unique<TextureData>();

		// load texture from image
		std::string path = std::string("../Assets/Textures/") + name;
		data->pixelArray = stbi_load(
			path.c_str(),
			&data->width,
			&data->height,
			&data->channelCount,
			0
		);

		if (!data->pixelArray)
		{
			__debugbreak();
			return;
		}

		auto& device = GraphicsContext::Get().GetDevice();

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.ArraySize = 1;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.Width = data->width;
		textureDesc.Height = data->height;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.MipLevels = 1;

		D3D11_SUBRESOURCE_DATA textureData = {};
		textureData.pSysMem = data->pixelArray;
		textureData.SysMemPitch = data->width * data->channelCount;

		ID3D11Texture2D* texture = nullptr;
		HRESULT result = device.CreateTexture2D(&textureDesc, &textureData, &texture);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		device.CreateShaderResourceView(
			texture,
			nullptr,
			&shaderResourceView
		);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		SafeRelease(texture);

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MaxAnisotropy = 3;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MinLOD = -FLT_MAX;
		samplerDesc.MaxLOD = FLT_MAX;

		result = device.CreateSamplerState(&samplerDesc, &samplerState);

		if (FAILED(result))
		{
			__debugbreak();
			return;
		}
	}
	Texture::~Texture()
	{
		SafeRelease(shaderResourceView);
		SafeRelease(samplerState);
	}

	void Texture::Bind(uint32_t index)
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();
		if (bindType == BindType::VertexShader)
		{
			context.VSGetShaderResources(index, 1, &shaderResourceView);
			context.VSSetSamplers(index, 1, &samplerState);
		}
		else if (bindType == BindType::PixelShader)
		{
			context.PSGetShaderResources(index, 1, &shaderResourceView);
			context.PSSetSamplers(index, 1, &samplerState);
		}
	}
}