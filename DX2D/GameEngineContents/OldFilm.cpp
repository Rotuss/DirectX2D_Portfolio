#include "PreCompile.h"
#include "OldFilm.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineCore/GameEngineShaderResourcesHelper.h>

OldFilm::OldFilm() 
	: CopyTarget(nullptr)
{
}

OldFilm::~OldFilm() 
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void OldFilm::EffectInit()
{
	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	EffectSet.SetPipeLine("Old");

	//GameEngineShaderResourcesHelper ShaderResources;
	//ShaderResources.ResourcesCheck(EffectSet.GetPipeLine());
	//if (true == ShaderResources.IsConstantBuffer("TRANSFORMDATA"))
	//{
	//	ShaderResources.SetConstantBufferLink("TRANSFORMDATA", &GetTransformData(), sizeof(GetTransformData()));
	//}
}

void OldFilm::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}

