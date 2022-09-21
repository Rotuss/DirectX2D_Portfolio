#include "PreCompile.h"
#include "GameEngineDefaultRenderer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRenderingPipeLine.h"

GameEngineDefaultRenderer::GameEngineDefaultRenderer() 
	: PipeLine(nullptr)
{
}

GameEngineDefaultRenderer::~GameEngineDefaultRenderer() 
{
}

GameEngineRenderingPipeLine* GameEngineDefaultRenderer::GetPipeLine()
{
	if (false == PipeLine->IsOriginal())
	{
		return PipeLine;
	}

	PipeLine = GetClonePipeLine(PipeLine);

	return PipeLine;
}

void GameEngineDefaultRenderer::Render(float _DeltaTime)
{
	if (nullptr == PipeLine)
	{
		MsgBoxAssert("������ ������������ ���õ��� ������ �������� �Ҽ� �����ϴ�.");
	}

	if (false == IsInstancing)
	{
		ShaderResources.AllResourcesSetting();
		PipeLine->Rendering();
		ShaderResources.AllResourcesReset();
	}
}

void GameEngineDefaultRenderer::SetPipeLine(const std::string& _Name)
{
	PipeLine = GameEngineRenderingPipeLine::Find(_Name);

	if (nullptr == PipeLine)
	{
		MsgBoxAssert("�������� �ʴ� ������������ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ShaderResources.ResourcesCheck(PipeLine);

	if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	{
		ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	}

	if (true == ShaderResources.IsConstantBuffer("RENDEROPTION"))
	{
		ShaderResources.SetConstantBufferLink("RENDEROPTION", &RenderOption, sizeof(RenderOption));
	}
}

void GameEngineDefaultRenderer::InstancingOn()
{
	GameEngineRenderer::InstancingOn();

	if (false == PipeLine->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("�ν��Ͻ��� �Ұ����� �������Դϴ�.")
	}
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();
}

