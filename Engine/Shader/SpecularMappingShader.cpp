#include "SpecularMappingShader.h"
#include "Resource/TextureLoader.h"
#include "Texture/Texture.h"

namespace Craft
{
	SpecularMappingShader::SpecularMappingShader(const std::string& diffuseTexture, const std::string& specularTexture) : Shader(L"SpecularMapping")
	{
		TextureLoader::Get().Load(diffuseTexture, diffuse);
		TextureLoader::Get().Load(specularTexture, specular);
	}

	void SpecularMappingShader::Bind()
	{
		Shader::Bind();

		if (diffuse.lock() && specular.lock())
		{
			diffuse.lock()->Bind(0);
			specular.lock()->Bind(1);
		}
	}
}