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
		MsgBoxAssert("랜더링 파이프라인이 세팅되지 않으면 랜더링을 할수 없습니다.");
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
		MsgBoxAssert("존재하지 않는 파이프라인을 세팅하려고 했습니다.");
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
		MsgBoxAssert("인스턴싱이 불가능한 렌더러입니다.")
	}
}

void GameEngineDefaultRenderer::Start()
{
	GameEngineRenderer::Start();
}

