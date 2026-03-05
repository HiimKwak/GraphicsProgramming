#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include "StaticMesh.h"
#include "Shader/Shader.h"
#include <d3dcompiler.h>
#include <cassert>

namespace Craft
{
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer()
	{
		assert(!instance);
		instance = this;
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Initialize()
	{
	}

	void Renderer::Submit(std::shared_ptr<StaticMesh> mesh, std::shared_ptr<Shader> shader)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.shader = shader;

		renderQueue.emplace_back(command);
	}

	void Renderer::DrawScene()
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();

		for (const RenderCommand& command : renderQueue)
		{
			command.mesh->Bind();
			command.shader->Bind();

			context.DrawIndexed(command.mesh->GetIndexCount(), 0, 0);
		}

		renderQueue.clear();
	}

	Renderer& Renderer::Get()
	{
		assert(instance);
		return *instance;
	}
}