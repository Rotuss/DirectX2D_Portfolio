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
		// 수치 수정 필요
		EndPosition.x = 0.0f;
		break;
	case BucketDirType::Right:
		// 수치 수정 필요
		EndPosition.x = 1580.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case BucketMoveType::TOP:
		// 랜덤 수정 필요
		EndPosition.y = -GameEngineRandom::MainRandom.RandomFloat(400.0f, 450.0f);
		break;
	case BucketMoveType::MID:
		// 랜덤 수정 필요
		EndPosition.y = -GameEngineRandom::MainRandom.RandomFloat(650.0f, 700.0f);
		break;
	case BucketMoveType::BOT:
		// 랜덤 수정 필요
		EndPosition.y = -GameEngineRandom::MainRandom.RandomFloat(850.0f, 900.0f);
		break;
	default:
		break;
	}
}

void MortimerFreezeBucket::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale(float4{ 50,50,0 });
}

void MortimerFreezeBucket::Update(float _DeltaTime)
{
	// 오->왼
	// 수치 수정 필요
	if (250.0f >= GetTransform().GetLocalPosition().x)
	{
		{
			// 달 3개 생성
			MortimerFreezeMoon* Ptr1 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr2 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr3 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);

			Ptr1->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr1->MoonSetting(MoonDirType::Right, MoonMoveType::TOP);
			Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr2->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr2->MoonSetting(MoonDirType::Right, MoonMoveType::MID);
			Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr3->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr3->MoonSetting(MoonDirType::Right, MoonMoveType::BOT);
			Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
		}
		
		Death();
	}
	// 왼->오
	// 수치 수정 필요
	if (1380.0f <= GetTransform().GetLocalPosition().x)
	{
		{
			// 달 3개 생성
			MortimerFreezeMoon* Ptr1 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr2 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);
			MortimerFreezeMoon* Ptr3 = GetLevel()->CreateActor<MortimerFreezeMoon>(OBJECTORDER::Boss);

			Ptr1->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr1->MoonSetting(MoonDirType::Left, MoonMoveType::TOP);
			Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr2->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr2->MoonSetting(MoonDirType::Left, MoonMoveType::MID);
			Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

			Ptr3->SetStartPosition(GetTransform().GetLocalPosition());
			Ptr3->MoonSetting(MoonDirType::Left, MoonMoveType::BOT);
			Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
		}

		Death();
	}

	BucketLerpRatio += _DeltaTime;
	if (1.0f <= BucketLerpRatio)
	{
		BucketLerpRatio = 1.0f;
	}

	LerpPos = float4::Lerp(StartPosition, EndPosition, BucketLerpRatio);

	GetTransform().SetLocalPosition(LerpPos);
}

