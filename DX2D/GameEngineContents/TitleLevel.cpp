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
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	
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
		Iris* FX = CreateActor<Iris>(OBJECTORDER::Title);
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
