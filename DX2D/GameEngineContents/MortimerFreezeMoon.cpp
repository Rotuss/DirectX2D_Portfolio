#include "PreCompile.h"
#include "MortimerFreezeMoon.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeMoon::MortimerFreezeMoon() 
	: Renderer(nullptr)
	, MoonDir()
	, MoonMove()
	, LerpPos()
	, StartPosition()
	, EndPosition()
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
		EndPosition.x = 1280.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case MoonMoveType::TOP:
		// 랜덤 수정 필요
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	case MoonMoveType::MID:
		// 랜덤 수정 필요
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	case MoonMoveType::BOT:
		// 랜덤 수정 필요
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	default:
		break;
	}
}

void MortimerFreezeMoon::Start()
{
}

void MortimerFreezeMoon::Update(float _DeltaTime)
{
	LerpPos = float4::Lerp(StartPosition, EndPosition, MoonLerpRatio);

	GetTransform().SetLocalPosition(LerpPos);
}

