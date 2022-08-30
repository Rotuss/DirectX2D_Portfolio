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
		MsgBoxAssert("�������� �ʴ� ������������ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);
}

void GameEngineRenderSet::Render()
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("������ ������������ ���õ��� ������ �������� �� �� �����ϴ�.");
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
