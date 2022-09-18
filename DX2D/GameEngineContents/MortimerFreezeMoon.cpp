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
		// ��ġ ���� �ʿ�
		EndPosition.x = 0.0f;
		break;
	case MoonDirType::Right:
		// ��ġ ���� �ʿ�
		EndPosition.x = 1280.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case MoonMoveType::TOP:
		// ���� ���� �ʿ�
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	case MoonMoveType::MID:
		// ���� ���� �ʿ�
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	case MoonMoveType::BOT:
		// ���� ���� �ʿ�
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

