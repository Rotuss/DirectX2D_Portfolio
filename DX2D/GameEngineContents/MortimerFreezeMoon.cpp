#include "PreCompile.h"
#include "MortimerFreezeMoon.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeMoon::MortimerFreezeMoon() 
	: Renderer(nullptr)
	, MoonDir()
	, MoonMove()
	, LerpPos()
	, StartPosition()
	, EndPosition({ 0.0f,0.0f,-1.0f })
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
		// 수치 수정 필요
		EndPosition.x = 0.0f;
		break;
	case MoonDirType::Right:
		// 수치 수정 필요
		EndPosition.x = 1580.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case MoonMoveType::TOP:
		// 랜덤 수정 필요
		GetTransform().SetLocalRotation({ 0.0f,0.0f,45.0f });
		EndPosition.y = StartPosition.y + GameEngineRandom::MainRandom.RandomFloat(80.0f, 100.0f);
		break;
	case MoonMoveType::MID:
		// 랜덤 수정 필요
		GetTransform().SetLocalRotation({ 0.0f,0.0f,0.0f });
		EndPosition.y = StartPosition.y + GameEngineRandom::MainRandom.RandomFloat(0.0f, 5.0f);
		break;
	case MoonMoveType::BOT:
		// 랜덤 수정 필요
		GetTransform().SetLocalRotation({ 0.0f,0.0f,-45.0f });
		EndPosition.y = StartPosition.y + -GameEngineRandom::MainRandom.RandomFloat(80.0f, 100.0f);
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
}

void MortimerFreezeMoon::Update(float _DeltaTime)
{
	MoonLerpRatio += _DeltaTime;
	if (1.0f <= MoonLerpRatio)
	{
		MoonLerpRatio = 1.0f;
	}
	
	LerpPos = float4::Lerp(StartPosition, EndPosition, MoonLerpRatio);

	GetTransform().SetLocalPosition(LerpPos);
}

