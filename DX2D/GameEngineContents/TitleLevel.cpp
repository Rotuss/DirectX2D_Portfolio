#include "PreCompile.h"
#include "TitleLevel.h"
//#include "TitleLogo.h"
#include "Player.h"
#include "Monster.h"
#include "UIMaster.h"
#include "Enums.h"
#include "GlobalContents.h"
#include "GameEngineCore/GEngine.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCameraActor.h>

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
		UIMaster* NewUI = CreateActor<UIMaster>(OBJECTORDER::UI);
	}

	{
		Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 100.0f, 0.0f, 0.0f });
		actor->GetTransform().SetWorldScale(float4(1.0f, 1.f, 1.0f));
	}
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		//GetMainCamera()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void TitleLevel::End()
{
}
