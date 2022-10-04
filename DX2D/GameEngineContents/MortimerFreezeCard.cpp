#include "PreCompile.h"
#include "MortimerFreezeCard.h"
#include "Player.h"
#include "MsChalice.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeCard::MortimerFreezeCard()
	: ColorCheck(nullptr)
	, ColRenderer(nullptr)
	, Renderer(nullptr)
	, RendererEffect(nullptr)
	, Collision(nullptr)
	, CollisionParry(nullptr)
	, Speed(100.0f)
	, IsRanding(false)
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
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	{
		RendererEffect = CreateComponent<GameEngineTextureRenderer>();
		RendererEffect->CreateFrameAnimationFolder("Peashot_Card_SparklesB", FrameAnimation_DESC("Peashot_Card_SparklesB", 0.04f, false));
		
		RendererEffect->CreateFrameAnimationFolder("Peashot_CardDeath_AngleA", FrameAnimation_DESC("Peashot_CardDeath_AngleA", 0.04f, false));
		RendererEffect->CreateFrameAnimationFolder("Peashot_CardDeath_AngleB", FrameAnimation_DESC("Peashot_CardDeath_AngleB", 0.04f, false));
		RendererEffect->CreateFrameAnimationFolder("Peashot_CardDeath_Flat", FrameAnimation_DESC("Peashot_CardDeath_Flat", 0.04f, false));
	
		RendererEffect->ChangeFrameAnimation("Peashot_Card_SparklesB");
		RendererEffect->SetScaleModeImage();
		RendererEffect->ScaleToTexture();
		RendererEffect->SetPivot(PIVOTMODE::CENTER);

		RendererEffect->AnimationBindEnd("Peashot_Card_SparklesB", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				RendererEffect->Off();
			});

		RendererEffect->AnimationBindEnd("Peashot_CardDeath_AngleA", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				Death();
			});

		RendererEffect->AnimationBindEnd("Peashot_CardDeath_AngleB", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				Death();
			});

		RendererEffect->AnimationBindEnd("Peashot_CardDeath_Flat", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				Death();
			});
	}

	CurPosition = MortimerFreezeBoss::MFBoss->GetTransform().GetLocalPosition();
	PlayerPosition = MsChalice::Chalice->GetTransform().GetLocalPosition();
}

void MortimerFreezeCard::Update(float _DeltaTime)
{
	ColorCheck = ColRenderer->GetCurTexture();
	if (nullptr == ColorCheck)
	{
		return;
	}
	if (true == ColorCheck->GetPixelToFloat4(GetTransform().GetLocalPosition().ix(), -GetTransform().GetLocalPosition().iy()).CompareInt4D(float4::BLACK) && false == IsRanding)
	{
		IsRanding = true;
		/*Renderer->Off();
		Collision->Off();
		CollisionParry->Off();
		PlayerPosition = GetTransform().GetLocalPosition();

		int RandomDeathNum = GameEngineRandom::MainRandom.RandomInt(1, 3);

		if (1 == RandomDeathNum)
		{
			RendererEffect->ChangeFrameAnimation("Peashot_CardDeath_AngleA");
			RendererEffect->On();
		}
		if (2 == RandomDeathNum)
		{
			RendererEffect->ChangeFrameAnimation("Peashot_CardDeath_AngleB");
			RendererEffect->On();
		}
		if (3 == RandomDeathNum)
		{
			RendererEffect->ChangeFrameAnimation("Peashot_CardDeath_Flat");
			RendererEffect->On();
		}*/
	}
	
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

