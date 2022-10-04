#include "PreCompile.h"
#include "MortimerFreezeMoon.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeMoon::MortimerFreezeMoon() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, MoonDir()
	, MoonMove()
	, LerpPos()
	, StartPosition()
	, EndPosition({ 0.0f,0.0f,-560.0f })
	, MoonLerpRatio(0.0f)
{
}

MortimerFreezeMoon::~MortimerFreezeMoon() 
{
}

void MortimerFreezeMoon::MoonSetting(MoonDirType _DirType, MoonMoveType _MoveType)
{
	MoonDir = _DirType;
	MoonMove = _MoveType;

	switch (_DirType)
	{
	case MoonDirType::Left:
		EndPosition.x = 100.0f;
		break;
	case MoonDirType::Right:
		EndPosition.x = 1550.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case MoonMoveType::TOP:
		GetTransform().SetLocalRotation({ 0.0f,0.0f,45.0f });
		EndPosition.y = StartPosition.y + GameEngineRandom::MainRandom.RandomFloat(250.0f, 280.0f);
		break;
	case MoonMoveType::MID:
		GetTransform().SetLocalRotation({ 0.0f,0.0f,0.0f });
		EndPosition.y = StartPosition.y + GameEngineRandom::MainRandom.RandomFloat(0.0f, 5.0f);
		break;
	case MoonMoveType::BOT:
		GetTransform().SetLocalRotation({ 0.0f,0.0f,-45.0f });
		EndPosition.y = StartPosition.y + -GameEngineRandom::MainRandom.RandomFloat(250.0f, 280.0f);
		break;
	default:
		break;
	}
}

void MortimerFreezeMoon::Start()
{
	GameEngineRandom RandomValue_;
	int RandomIntNum = RandomValue_.RandomInt(0, 1);
	
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Moon_A", FrameAnimation_DESC("Moon_A", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Moon_B", FrameAnimation_DESC("Moon_B", 0.1f, true));

		if (0 == RandomIntNum)
		{
			Renderer->ChangeFrameAnimation("Moon_A");
		}
		if (1 == RandomIntNum)
		{
			Renderer->ChangeFrameAnimation("Moon_B");
		}

		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 40,60,-1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
	}
}

void MortimerFreezeMoon::Update(float _DeltaTime)
{
	MoonLerpRatio += _DeltaTime;
	if (1.0f <= MoonLerpRatio)
	{
		MoonLerpRatio = 1.0f;
		Death();
	}
	
	LerpPos = float4::Lerp(StartPosition, EndPosition, MoonLerpRatio);

	GetTransform().SetLocalPosition(LerpPos);
}

