#pragma once

#include <vector>
#include <d3d11.h>

namespace Craft
{
	struct RenderCommand
	{
		ID3D11Buffer* vertexBuffer = nullptr; // 용도가 지정돼있는 정점 데이터 메모리 덩어리
		ID3D11Buffer* indexBuffer = nullptr; // 인덱스 버퍼(옵션이나 상용엔진은 모두 사용)
		ID3D11InputLayout* inputLayout = nullptr; // 정점 데이터의 생김새, 얼마만큼 읽으면 무슨 정보인지 알려줘야 그래픽카드가 해석할 수 있음

		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader* pixelShader = nullptr;

		uint32_t indexCount = 0; // vertexBuffer와 연결된 색인을 어디까지 그릴지 지정
	};

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Initialize();
		void DrawScene();

	private:
		std::vector<RenderCommand> renderQueue;
	};
}

