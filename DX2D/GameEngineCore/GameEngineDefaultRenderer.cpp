#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
	:PipeLine(nullptr)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

void GameEngineDefaultRenderer::Render(float _DeltaTime)
{
	GameEngineRenderer::Start();
}

void GameEngineDefaultRenderer::Start()
{
}

