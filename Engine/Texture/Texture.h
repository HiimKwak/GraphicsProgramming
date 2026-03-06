#pragma once

#include "Core/Common.h"
#include <string>
#include <memory>
#include <d3d11.h>

namespace Craft
{
	struct TextureData
	{
		TextureData() = default;
		~TextureData()
		{
			free(pixelArray);
			pixelArray = nullptr;
		}

		int width = 0, height = 0;
		int channelCount = 0;
		void* pixelArray = nullptr;
	};

	class CRAFT_API Texture
	{
		enum class BindType // supposed to be located in shader.h
		{
			VertexShader,
			PixelShader
		};

	public:
		Texture(const std::string& name, BindType bindType = BindType::PixelShader);
		virtual ~Texture();

		void Bind(uint32_t index = 0); // supposed to be located in shader.h

	private:
		std::string name;
		BindType bindType = BindType::PixelShader;
		std::unique_ptr<TextureData> data;

		ID3D11ShaderResourceView* shaderResourceView = nullptr; // texture resource(direct3D) using in shader
		ID3D11SamplerState* samplerState = nullptr;
	};
}
