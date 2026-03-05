#pragma once

#include "Core/Common.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace Craft
{
	class StaticMesh;

	class CRAFT_API MeshLoader
	{
	public:
		MeshLoader();
		~MeshLoader() = default;

		void GetMesh(const std::string& name, std::weak_ptr<StaticMesh>& outMesh);

		static MeshLoader& Get();

	private:
		void LoadMesh(const std::string& name, std::weak_ptr<StaticMesh>& outMesh);

	private:
		std::unordered_map<std::string, std::shared_ptr<StaticMesh>> meshList; // todo: submesh 구현필요
		static MeshLoader* instance;
	};
}

