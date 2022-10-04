#include "PreCompile.h"
#include "MortimerFreezeBucket.h"
#include "MortimerFreezeBoss.h"
#include "MortimerFreezeMoon.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeBucket::MortimerFreezeBucket() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, CollisionParry(nullptr)
	, BucketDir()
	, BucketMove()
	, LerpPos()
	, StartPosition()
	, EndPosition({ 0.0f,0.0f,-560.0f })
	, BucketLerpRatio(0.0f)
	, IsBucketMove(false)
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
		EndPosition.x = 200.0f;
		break;
	case BucketDirType::Right:
		EndPosition.x = 1450.0f;
		break;
	default:
		break;
	}

	switch (_MoveType)
	{
	case BucketMoveType::TOP:
		EndPosition.y = -GameEngineRandom::MainRandom.RandomFloat(20.0f, 50.0f);
		break;
	case BucketMoveType::MID:
		EndPosition.y = -GameEngineRandom::MainRandom.RandomFloat(300.0f, 350.0f);
		break;
	case BucketMoveType::BOT:
		EndPosition.y = -GameEngineRandom::MainRandom.RandomFloat(550.0f, 600.0f);
		break;
	default:
		break;
	}
}

void MortimerFreezeBucket::Start()
{
	GameEngineRandom RandomValue_;
	int RandomIntNum = RandomValue_.RandomInt(0, 1);
	
	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 60,80,-1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
		Collision->Off();
	}
	{
		CollisionParry = CreateComponent<GameEngineCollision>();
		CollisionParry->GetTransform().SetLocalScale({ 60,80,-1 });
		CollisionParry->ChangeOrder(OBJECTORDER::Parry);
		CollisionParry->Off();
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Bucket_Normal_Start", FrameAnimation_DESC("Bucket_Normal", 0, 11, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("Bucket_Normal", FrameAnimation_DESC("Bucket_Normal", 12, 20, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Bucket_Pink_Start", FrameAnimation_DESC("Bucket_Pink", 0, 11, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("Bucket_Pink", FrameAnimation_DESC("Bucket_Pink", 12, 20, 0.1f, true));
		
		if (0 == RandomIntNum)
		{
			Renderer->ChangeFrameAnimation("Bucket_Normal_Start");
			Collision->On();
		}
		if (1 == RandomIntNum)
		{
			Renderer->ChangeFrameAnimation("Bucket_Pink_Start");
			CollisionParry->On();
		}

		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	Renderer->AnimationBindEnd("Bucket_Normal_Start", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsBucketMove = true;
			MortimerFreezeBoss::MFBoss->SetBucketMove(IsBucketMove);
			Renderer->ChangeFrameAnimation("Bucket_Normal");
		});

	Renderer->AnimationBindEnd("Bucket_Pink_Start", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsBucketMove = true;
			MortimerFreezeBoss::MFBoss->SetBucketMove(IsBucketMove);
			Renderer->ChangeFrameAnimation("Bucket_Pink");
		});
}

void MortimerFreezeBucket::Update(float _DeltaTime)
{
	// 오->왼
	if (200.0f >= GetTransform().GetLocalPosition().x)
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
	if (1450.0f <= GetTransform().GetLocalPosition().x)
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

	if (true == IsBucketMove)
	{
		BucketLerpRatio += _DeltaTime;
		if (1.0f <= BucketLerpRatio)
		{
			BucketLerpRatio = 1.0f;
		}

		LerpPos = float4::Lerp(StartPosition, EndPosition, BucketLerpRatio);

		GetTransform().SetLocalPosition(LerpPos);
	}
}

