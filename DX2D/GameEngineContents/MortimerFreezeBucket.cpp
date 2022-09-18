#include "PreCompile.h"
#include "MortimerFreezeBucket.h"
#include "MortimerFreezeMoon.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeBucket::MortimerFreezeBucket() 
	: Renderer(nullptr)
	, BucketDir()
	, BucketMove()
	, LerpPos()
	, StartPosition()
	, EndPosition()
	, BucketLerpRatio(0.0f)
{
}

MortimerFreezeBucket::~MortimerFreezeBucket() 
{
}

void MortimerFreezeBucket::BucketSetting(BucketDirType _DirType, BucketMoveType _MoveType)
{
	BucketDir = _DirType;
	BucketMove = _MoveType;

	switch (_DirType)
	{
	case BucketDirType::Left:
		// ��ġ ���� �ʿ�
		EndPosition.x = 0.0f;
		break;
	case BucketDirType::Right:
		// ��ġ ���� �ʿ�
		EndPosition.x = 1280.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case BucketMoveType::TOP:
		// ���� ���� �ʿ�
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	case BucketMoveType::MID:
		// ���� ���� �ʿ�
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	case BucketMoveType::BOT:
		// ���� ���� �ʿ�
		EndPosition.y = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
		break;
	default:
		break;
	}
}

void MortimerFreezeBucket::Start()
{
}

void MortimerFreezeBucket::Update(float _DeltaTime)
{
	// ��->��
	// ��ġ ���� �ʿ�
	if (0.0f >= GetTransform().GetLocalPosition().x)
	{
		{
			// �� 3�� ����
			MortimerFreezeMoon* Ptr1 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr2 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr3 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);

			Ptr1->MoonSetting(MoonDirType::Right, MoonMoveType::TOP);
			Ptr1->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr2->MoonSetting(MoonDirType::Right, MoonMoveType::MID);
			Ptr2->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr3->MoonSetting(MoonDirType::Right, MoonMoveType::BOT);
			Ptr3->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
		}
		
		Death();
	}
	// ��->��
	// ��ġ ���� �ʿ�
	if (1280.0f <= GetTransform().GetLocalPosition().x)
	{
		{
			// �� 3�� ����
			MortimerFreezeMoon* Ptr1 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr2 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr3 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);

			Ptr1->MoonSetting(MoonDirType::Left, MoonMoveType::TOP);
			Ptr1->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr2->MoonSetting(MoonDirType::Left, MoonMoveType::MID);
			Ptr2->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr3->MoonSetting(MoonDirType::Left, MoonMoveType::BOT);
			Ptr3->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
		}

		Death();
	}

	LerpPos = float4::Lerp(StartPosition, EndPosition, BucketLerpRatio);

	GetTransform().SetLocalPosition(LerpPos);
}

