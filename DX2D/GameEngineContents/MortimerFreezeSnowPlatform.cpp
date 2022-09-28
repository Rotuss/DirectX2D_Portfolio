#include "PreCompile.h"
#include "MortimerFreezeSnowPlatform.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeSnowPlatform::MortimerFreezeSnowPlatform() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, CurPlatformType()
	, FollowObj(nullptr)
	, PrevPosition(float4::ZERO)
	, CurPosition(float4::ZERO)
{
}

MortimerFreezeSnowPlatform::~MortimerFreezeSnowPlatform() 
{
}

void MortimerFreezeSnowPlatform::SetPlatformType(PlatformType _Type)
{
	CurPlatformType = _Type;

	switch (_Type)
	{
	case PlatformType::Intro:
		Renderer->ChangeFrameAnimation("SnowCult_Platform_Intro");
		break;
	case PlatformType::TypeA:
		Renderer->ChangeFrameAnimation("SnowCult_Platform_A");
		break;
	case PlatformType::TypeB:
		Renderer->ChangeFrameAnimation("SnowCult_Platform_B");
		break;
	case PlatformType::TypeC:
		Renderer->ChangeFrameAnimation("SnowCult_Platform_C");
		break;
	case PlatformType::TypeD:
		Renderer->ChangeFrameAnimation("SnowCult_Platform_D");
		break;
	case PlatformType::TypeE:
		Renderer->ChangeFrameAnimation("SnowCult_Platform_E");
		break;
	default:
		break;
	}

	Renderer->SetScaleModeImage();
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

float4 MortimerFreezeSnowPlatform::GetMovePos()
{
	return CurPosition - PrevPosition;
}

void MortimerFreezeSnowPlatform::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SnowCult_Platform_Intro", FrameAnimation_DESC("SnowCult_Platform_Intro", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("SnowCult_Platform_A", FrameAnimation_DESC("SnowCult_Platform_A", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("SnowCult_Platform_B", FrameAnimation_DESC("SnowCult_Platform_B", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("SnowCult_Platform_C", FrameAnimation_DESC("SnowCult_Platform_C", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("SnowCult_Platform_D", FrameAnimation_DESC("SnowCult_Platform_D", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("SnowCult_Platform_E", FrameAnimation_DESC("SnowCult_Platform_E", 0.1f, true));
	
	Renderer->AnimationBindEnd("SnowCult_Platform_Intro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			int RandomIntNum = GameEngineRandom::MainRandom.RandomInt(1, 5);

			if (1 == RandomIntNum)
			{
				Renderer->ChangeFrameAnimation("SnowCult_Platform_A");
			}
			if (2 == RandomIntNum)
			{
				Renderer->ChangeFrameAnimation("SnowCult_Platform_B");
			}
			if (3 == RandomIntNum)
			{
				Renderer->ChangeFrameAnimation("SnowCult_Platform_C");
			}
			if (4 == RandomIntNum)
			{
				Renderer->ChangeFrameAnimation("SnowCult_Platform_D");
			}
			if (5 == RandomIntNum)
			{
				Renderer->ChangeFrameAnimation("SnowCult_Platform_E");
			}
		});

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 200.0f, 40.0f, 0.0f });
	Collision->ChangeOrder(OBJECTORDER::SnowPlatform);
}

void MortimerFreezeSnowPlatform::Update(float _DeltaTime)
{
	if (nullptr == FollowObj)
	{
		return;
	}

	PrevPosition = GetTransform().GetWorldPosition();
	GetTransform().SetWorldPosition(FollowObj->GetWorldPosition());
	CurPosition = GetTransform().GetWorldPosition();
}

