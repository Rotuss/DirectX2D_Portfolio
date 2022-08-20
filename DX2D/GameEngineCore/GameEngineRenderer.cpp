#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

// Resources Header
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

GameEngineRenderer::GameEngineRenderer() 
	: CameraOrder(CAMERAORDER::MAINCAMERA)
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

GameEngineRenderingPipeLine* GameEngineRenderer::GetClonePipeLine(GameEngineRenderingPipeLine* _Rendering)
{
	GameEngineRenderingPipeLine* Clone = GameEngineRenderingPipeLine::Create();
	Clone->Copy(_Rendering);

	return Clone;
}

void GameEngineRenderer::ChangeCamera(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushRenderer(this, _Order);
}

void GameEngineRenderer::Start()
{
}

void GameEngineRenderer::PushRendererToMainCamera()
{
	GetActor()->GetLevel()->PushRendererToMainCamera(this);
}

void GameEngineRenderer::PushRendererToUICamera()
{
	GetActor()->GetLevel()->PushRendererToUICamera(this);
}

