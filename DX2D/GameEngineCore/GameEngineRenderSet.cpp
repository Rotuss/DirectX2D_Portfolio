#include "PreCompile.h"
#include "GameEngineRenderSet.h"

GameEngineRenderSet::GameEngineRenderSet() 
{
}

GameEngineRenderSet::~GameEngineRenderSet() 
{
}

void GameEngineRenderSet::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("존재하지 않는 파이프라인을 세팅하려고 했습니다.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);
}

void GameEngineRenderSet::Render()
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할 수 없습니다.");
	}

	ShaderResources.AllResourcesSetting();
	PipeLine->Rendering();
}

GameEngineRenderingPipeLine* GameEngineRenderSet::GetPipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	GameEngineRenderingPipeLine* Clone = GameEngineRenderingPipeLine::Create();
	Clone->Copy(PipeLine);
	PipeLine = Clone;

	return PipeLine;
}
