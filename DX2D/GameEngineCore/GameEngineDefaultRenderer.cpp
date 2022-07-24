#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineRenderingPipeLine.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
	:PipeLine(nullptr)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

void GameEngineDefaultRenderer::Render(float _DeltaTime)
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할수 없습니다.");
	}

	PipeLineHelper.AllResourcesSetting();
	PipeLine->Rendering();
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("존재하지 않는 파이프라인을 세팅하려고 했습니다.");
		return;
	}

	PipeLineHelper.ResourcesCheck(PipeLine);

	if (true == PipeLineHelper.IsConstantBufferSetter("TRANSFORMDATA"))
	{
		PipeLineHelper.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	}
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();
}

