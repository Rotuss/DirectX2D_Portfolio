#include "PreCompile.h"
#include "MortimerFreezeCard.h"
#include "Player.h"
#include "MsChalice.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeCard::MortimerFreezeCard() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, CollisionParry(nullptr)
	, Speed(100.0f)
{
}

MortimerFreezeCard::~MortimerFreezeCard() 
{
}

void MortimerFreezeCard::Start()
{
	GameEngineRandom RandomValue_;
	int RandomItemNum = RandomValue_.RandomInt(0, 4);
	
	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 25,110,-1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
		Collision->Off();
	}
	{
		CollisionParry = CreateComponent<GameEngineCollision>();
		CollisionParry->GetTransform().SetLocalScale({ 25,110,-1 });
		CollisionParry->ChangeOrder(OBJECTORDER::Parry);
		CollisionParry->Off();
	}
	
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CardPinkA", FrameAnimation_DESC("Peashot_Card_PinkA", 0.04f, true));
		Renderer->CreateFrameAnimationFolder("CardPinkB", FrameAnimation_DESC("Peashot_Card_PinkB", 0.04f, true));
		Renderer->CreateFrameAnimationFolder("CardA", FrameAnimation_DESC("Peashot_CardA", 0.04f, true));
		Renderer->CreateFrameAnimationFolder("CardB", FrameAnimation_DESC("Peashot_CardB", 0.04f, true));
		Renderer->CreateFrameAnimationFolder("CardC", FrameAnimation_DESC("Peashot_CardC", 0.04f, true));
		
		if (0 == RandomItemNum)
		{
			Renderer->ChangeFrameAnimation("CardPinkA");
			CollisionParry->On();
		}
		if (1 == RandomItemNum)
		{
			Renderer->ChangeFrameAnimation("CardPinkB");
			CollisionParry->On();
		}
		if (2 == RandomItemNum)
		{
			Renderer->ChangeFrameAnimation("CardA");
			Collision->On();
		}
		if (3 == RandomItemNum)
		{
			Renderer->ChangeFrameAnimation("CardB");
			Collision->On();
		}
		if (4 == RandomItemNum)
		{
			Renderer->ChangeFrameAnimation("CardC");
			Collision->On();
		}
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	CurPosition = MortimerFreezeBoss::MFBoss->GetTransform().GetLocalPosition();
	PlayerPosition = MsChalice::Chalice->GetTransform().GetLocalPosition();
}

void MortimerFreezeCard::Update(float _DeltaTime)
{
	if (-10.0f > GetTransform().GetLocalPosition().x)
	{
		Death();
		return;
	}
	if (1650.0f < GetTransform().GetLocalPosition().x)
	{
		Death();
		return;
	}
	
	float AccTime = GetAccTime();
	float AccDeltaTime = AccTime / 1.0f;
	
	float4 LerpPos = float4::Lerp(CurPosition , PlayerPosition, AccDeltaTime);

	GetTransform().SetLocalRotation({0,0,float4::VectorXYtoDegree(PlayerPosition, CurPosition) -90});
	GetTransform().SetLocalPosition(LerpPos);
}

