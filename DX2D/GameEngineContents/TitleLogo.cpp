#include "PreCompile.h"
#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

TitleLogo::TitleLogo() 
	: Renderer(nullptr)
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Logo", FrameAnimation_DESC("MDHR_Logo", 0.05f, false));
		Renderer->ChangeFrameAnimation("Logo");
		Renderer->AnimationBindEnd("Logo", std::bind(&TitleLogo::EndFunction, this, std::placeholders::_1));
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}
}

void TitleLogo::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

void TitleLogo::End()
{
}

void TitleLogo::EndFunction(const FrameAnimation_DESC& _Info)
{
	//GEngine::ChangeLevel("Title");
}
