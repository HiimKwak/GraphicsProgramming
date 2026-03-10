#pragma once

#include <vector>
#include <d3d11.h>
#include <memory>

namespace Craft
{
	class StaticMesh;
	class Shader;
	class Transform;

	struct RenderCommand
	{
		std::shared_ptr<StaticMesh> mesh;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Transform> transform;
	};

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Initialize();

		void Submit(std::shared_ptr<StaticMesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<Transform> transform);

		void DrawScene();

		static Renderer& Get();

	private:
		std::vector<RenderCommand> renderQueue;

		static Renderer* instance;
	};
}