#include "Renderer.h"
#include "Core/Common.h"
#include "GraphicsContext.h"
#include "StaticMesh.h"
#include "Shader/Shader.h"
#include "Math/Transform.h"

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
		SafeRelease(cameraBuffer);
	}

	void Renderer::Initialize()
	{
		auto& device = GraphicsContext::Get().GetDevice();

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(Matrix4);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ThrowIfFailed(device.CreateBuffer(&bufferDesc, nullptr, &cameraBuffer), L"Failed to create camera buffer.")
	}

	void Renderer::Submit(std::shared_ptr<StaticMesh> mesh, std::shared_ptr<Shader> shader, std::shared_ptr<Transform> transform)
	{
		RenderCommand command;
		command.mesh = mesh;
		command.shader = shader;
		command.transform = transform;

		renderQueue.emplace_back(command);
	}

	void Renderer::UpdateCameraMatrix(const Matrix4& viewMatrix, const Matrix4& projectionMatrix)
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();

		D3D11_MAPPED_SUBRESOURCE resource = {};
		ThrowIfFailed(context.Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource), L"Failed to map camera buffer.");

		Matrix4 cameraMatrixRef = Matrix4::Transpose(viewMatrix * projectionMatrix);
		memcpy(resource.pData, &cameraMatrixRef, sizeof(Matrix4));
		context.Unmap(cameraBuffer, 0);
	}

	void Renderer::DrawScene()
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();

		for (const RenderCommand& command : renderQueue)
		{
			command.mesh->Bind();
			command.shader->Bind();
			command.transform->Bind();
			context.VSSetConstantBuffers(1, 1, &cameraBuffer);

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