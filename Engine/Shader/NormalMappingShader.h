#pragma once

#include "Shader.h"
#include <memory>
#include <string>

namespace Craft
{
	class Texture;

	class CRAFT_API NormalMappingShader : public Shader
	{
	public:
		NormalMappingShader(const std::string& diffuseTexture, const std::string& specularTexture, const std::string& normalTexture);

		virtual void Bind() override;

	private:
		std::weak_ptr<Texture> diffuse;
		std::weak_ptr<Texture> specular;
		std::weak_ptr<Texture> normal;
	};
}

