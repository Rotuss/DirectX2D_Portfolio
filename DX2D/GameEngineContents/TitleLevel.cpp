#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleScreenBackGround.h"
#include "TitleScreenCuphead.h"
#include "TitleScreenChalice.h"
#include "TitleScreenMugman.h"
#include "TitleScreenChips.h"
#include "Player.h"
#include "GlobalContents.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GEngine.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	{
		TitleScreenBackGround* TitleBackGround = CreateActor<TitleScreenBackGround>(OBJECTORDER::Title);
	}

	{
		TitleScreenCuphead* TitleCuphead = CreateActor<TitleScreenCuphead>(OBJECTORDER::Title);
	}

	{
		TitleScreenChalice* TitleChalice = CreateActor<TitleScreenChalice>(OBJECTORDER::Title);
	}

	{
		TitleScreenMugman* TitleMugman = CreateActor<TitleScreenMugman>(OBJECTORDER::Title);
	}

	{
		TitleScreenChips* TitleChips = CreateActor<TitleScreenChips>(OBJECTORDER::Title);
	}

	/*{
		Player* title = CreateActor<Player>(OBJECTORDER::Title);
	}*/
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void TitleLevel::End()
{
}
