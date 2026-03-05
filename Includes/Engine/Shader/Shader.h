#pragma once

#include "Core/Common.h"
#include <d3d11.h>
#include <string>

namespace Craft
{
	class CRAFT_API Shader
	{
	public:
		Shader(const std::wstring& name);
		virtual ~Shader();

		virtual void Bind();

		inline ID3D11VertexShader* GetVertexShader() const { return vertexShader; }
		inline ID3D11PixelShader* GetPixelShader() const { return pixelShader; }
		inline ID3D11InputLayout* GetInputLayout() const { return inputLayout; }

	protected:
		std::wstring name;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;
		ID3D11InputLayout* inputLayout = nullptr;
	};
}