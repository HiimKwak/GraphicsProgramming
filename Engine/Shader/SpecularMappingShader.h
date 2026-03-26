#pragma once

#include "Shader.h"
#include <memory>
#include <string>

namespace Craft
{
	class Texture;

	class CRAFT_API SpecularMappingShader : public Shader
	{
	public:
		SpecularMappingShader(const std::string& diffuseTexture, const std::string& specularTexture);

		virtual void Bind() override;

	private:
		std::weak_ptr<Texture> diffuse;
		std::weak_ptr<Texture> specular;
	};
}

