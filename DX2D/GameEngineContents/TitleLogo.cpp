#include "PreCompile.h"
#include "TitleLogo.h"
#include "GlobalContents.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

TitleLogo::TitleLogo() 
	: Renderer(nullptr)
	, LogoTime(3.0f)
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	GameEngineSound::SoundPlayControl("sfx_Optical_Start_001.wav");
	
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("LogoStart", FrameAnimation_DESC("MDHR_Logo", 0, 0, 0.0f, false));
		Renderer->CreateFrameAnimationFolder("Logo", FrameAnimation_DESC("MDHR_Logo", 1, 100, 0.05f, false));
		Renderer->ChangeFrameAnimation("LogoStart");
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

	LogoTime -= _DeltaTime;
	if (0 >= LogoTime)
	{
		LogoTime = 10.0f;
		Renderer->ChangeFrameAnimation("Logo");
		GlobalContents::Actors::BGM = GameEngineSound::SoundPlayControl("MDHR_LOGO_STING.wav");
	}
}

void TitleLogo::End()
{
}

void TitleLogo::EndFunction(const FrameAnimation_DESC& _Info)
{
	GlobalContents::Actors::BGM.Stop();
	GEngine::ChangeLevel("Title");
}
