#include "TextureLoader.h"
#include "Texture/Texture.h"
#include <cassert>

namespace Craft
{
	TextureLoader* TextureLoader::instance = nullptr;

	TextureLoader::TextureLoader()
	{
		assert(!instance);
		instance = this;
	}

	void TextureLoader::Load(const std::string& name, std::weak_ptr<Texture>& outTexture)
	{
		auto result = textureMap.find(name);
		if (result != textureMap.end())
		{
			outTexture = result->second;
			return;
		}

		std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(name);
		textureMap.insert({ name, newTexture });
		outTexture = newTexture;
	}

	TextureLoader& TextureLoader::Get()
	{
		assert(instance);
		return *instance;
	}
}
