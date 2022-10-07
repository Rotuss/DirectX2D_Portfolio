#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleScreenBackGround.h"
#include "TitleScreenCuphead.h"
#include "TitleScreenChalice.h"
#include "TitleScreenMugman.h"
#include "TitleScreenChips.h"
#include "ScreenFX.h"
#include "Iris.h"
//#include "HourGlass.h"
#include "TitleMainLevel.h"
#include "GlobalContents.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineBlur.h>

TitleLevel::TitleLevel() 
	: Renderer(nullptr)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::LevelStartEvent()
{
	GlobalContents::Actors::BGM = GameEngineSound::SoundPlayControl("mus_dlc_title.wav");
}

void TitleLevel::LevelEndEvent()
{
}

void TitleLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetIrisCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	if (false == GameEngineInput::GetInst()->IsKey("ChangeNextTitle"))
	{
		GameEngineInput::GetInst()->CreateKey("ChangeNextTitle", 'P');
	}

	{
		TitleScreenBackGround* TitleBackGround = CreateActor<TitleScreenBackGround>(OBJECTORDER::Title);
		TitleScreenCuphead* TitleCuphead = CreateActor<TitleScreenCuphead>(OBJECTORDER::Title);
		TitleScreenChalice* TitleChalice = CreateActor<TitleScreenChalice>(OBJECTORDER::Title);
		TitleScreenMugman* TitleMugman = CreateActor<TitleScreenMugman>(OBJECTORDER::Title);
		TitleScreenChips* TitleChips = CreateActor<TitleScreenChips>(OBJECTORDER::Title);
	}

	{
		{
			GameEngineActor* Ptr = CreateActor<GameEngineActor>(OBJECTORDER::Title);
			Renderer = Ptr->CreateComponent<GameEngineTextureRenderer>();
			Renderer->CreateFrameAnimationFolder("AnyKeyPush", FrameAnimation_DESC("AnyKeyPush", 0.5f, true));
			Renderer->ChangeFrameAnimation("AnyKeyPush");
			Renderer->GetTransform().SetLocalScale({ 400.0f, 50.0f });
			Renderer->GetTransform().SetLocalPosition({ 0.0f, -290.0f });
		}
	}

	{
		ScreenFX* SFX = CreateActor<ScreenFX>(100);
		SFX->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	}
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (GameEngineInput::GetInst()->IsDown("ChangeNextTitle"))
	{
		GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
		Iris* FX = CreateActor<Iris>(OBJECTORDER::Title);
		FX->SetAnimType(AnimType::Front);
		FX->GetRenderer()->AnimationBindEnd("IrisFX", std::bind(&TitleLevel::EndFunction, this, std::placeholders::_1));
	}
}

void TitleLevel::End()
{
}

void TitleLevel::EndFunction(const FrameAnimation_DESC& _Info)
{
	//레벨 체인지(메인타이틀)
	//HourGlass* Hourglass = CreateActor<HourGlass>(OBJECTORDER::Title);
	GEngine::ChangeLevel("TitleMain");
}
