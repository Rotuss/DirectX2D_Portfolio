#include "PreCompile.h"
#include "TitleLevel.h"
//#include "TitleLogo.h"
#include "Player.h"
#include "Monster.h"
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
	{
		GameEngineCameraActor* actor = CreateActor<GameEngineCameraActor>();
		actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	}

	Player* NewPlayer;

	{
		NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
	}

	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 100.0f, 0.0f, 0.0f });
		actor->GetTransform().SetWorldScale(float4(1.0f, 1.f, 1.0f));
	}
}

void TitleLevel::Update(float _DeltaTime)
{
}

void TitleLevel::End()
{
}
