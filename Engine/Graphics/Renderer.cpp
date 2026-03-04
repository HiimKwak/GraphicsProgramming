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

	// �ʱ�ȭ.
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

	// DrawCall �߻� ó��.
	// -> ������ ���������� ����(����).
	void Renderer::DrawScene()
	{
		// ���ε�.
		// -> ���̴� �� �ܰ迡 �ʿ��� ���� ���� �� ����.
		// State ����.
		auto& context = GraphicsContext::Get().GetDeviceContext();

		// ���� Ŀ�ǵ� ��������.
		for (const RenderCommand& command : renderQueue)
		{
			auto vertexBuffer = command.mesh->GetVertexBuffer();
			uint32_t stride = command.mesh->GetStride();
			uint32_t offset = 0;

			context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			context.IASetIndexBuffer(command.mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
			context.IASetInputLayout(command.shader->GetInputLayout());
			// �� 3���� �߶� �а�, �ﰢ���� ������ִ� ���.
			context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// ���̴� ����.
			context.VSSetShader(command.shader->GetVertexShader(), nullptr, 0);
			context.PSSetShader(command.shader->GetPixelShader(), nullptr, 0);

			// ��ο� ��.
			// ������ ���������� ����.
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