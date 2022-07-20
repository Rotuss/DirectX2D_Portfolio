#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

// Resources Header
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start()
{
	GetActor()->GetLevel()->PushRenderer(this);
}

void GameEngineRenderer::Render(float _DeltaTime)
{
	GameEngineVertexBuffer* Vertex = GameEngineVertexBuffer::Find("Box");
	GameEngineIndexBuffer* Index = GameEngineIndexBuffer::Find("Box");

	std::vector<POINT> DrawVertex;
	DrawVertex.resize(Index->Indexs.size());

	std::vector<float4> CopyBuffer;
	CopyBuffer.resize(Index->Indexs.size());

	for (size_t i = 0; i < Index->Indexs.size(); i++)
	{
		int TriIndex = Index->Indexs[i];

		CopyBuffer[i] = Vertex->Vertexs[TriIndex];
		auto& tran = GetTransform();
		CopyBuffer[i] = CopyBuffer[i] * GetTransform().GetWorldViewProjection();
		CopyBuffer[i] = CopyBuffer[i] / CopyBuffer[i].w;
		CopyBuffer[i] = CopyBuffer[i] * ViewPort;

		DrawVertex[i] = CopyBuffer[i].GetConvertWindowPOINT();
	}

	for (size_t i = 0; i < DrawVertex.size(); i += 3)
	{
		Polygon(GameEngineWindow::GetHDC(), &DrawVertex[i], 3);
	}
}

