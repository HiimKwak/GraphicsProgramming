#include "TextureMappingShader.h"
#include "Texture/Texture.h"
#include "Resource/TextureLoader.h"

namespace Craft
{
	TextureMappingShader::TextureMappingShader(const std::string& textureName) : Shader(L"TextureMapping")
	{
		TextureLoader::Get().Load(textureName, texture);
	}

	void TextureMappingShader::Bind()
	{
		Shader::Bind();

		if (texture.lock())
			texture.lock()->Bind();
	}
}