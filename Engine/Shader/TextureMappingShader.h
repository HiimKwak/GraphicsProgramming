#pragma once

#include "Core/Common.h"
#include "Shader.h"
#include <memory>
#include <string>

namespace Craft
{
	class Texture;

	class CRAFT_API TextureMappingShader : public Shader
	{
	public:
		TextureMappingShader(const std::string& textureName);

		virtual void Bind() override;
	private:
		std::weak_ptr<Texture> texture;
	};
}

