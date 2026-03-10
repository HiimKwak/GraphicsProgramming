#include "Transform.h"
#include "Graphics/GraphicsContext.h"

namespace Craft
{
	Transform::Transform()
	{
		transformMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);

		transformMatrix = Matrix4::Transpose(transformMatrix); // row matrix(CPU), column matrix(GPU)

		auto& device = GraphicsContext::Get().GetDevice();

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(Matrix4);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		HRESULT result = device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer);
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}
	}

	Transform::~Transform()
	{
		SafeRelease(constantBuffer);
	}

	void Transform::Update()
	{
		transformMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);

		transformMatrix = Matrix4::Transpose(transformMatrix); // row matrix(CPU), column matrix(GPU)
	}

	void Transform::Bind()
	{
		auto& context = GraphicsContext::Get().GetDeviceContext();

		D3D11_MAPPED_SUBRESOURCE mappedSubresource = {};

		HRESULT result = context.Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource); // lock thread to process mappedSubresources
		if (FAILED(result))
		{
			__debugbreak();
			return;
		}

		memcpy(mappedSubresource.pData, &transformMatrix, sizeof(Matrix4)); // update data

		context.Unmap(constantBuffer, 0); // unlock thread

		context.VSSetConstantBuffers(0, 1, &constantBuffer);
	}
}