#include "PreCompile.h"
#include "MortimerFreezeIceBat.h"
#include "MortimerFreezeLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeIceBat::MortimerFreezeIceBat()
	: DeathRenderer(nullptr)
	, Collision(nullptr)
	, CollisionParry(nullptr)
	, BatColor()
	, CurBatDir()
	, StartPosition(float4::ZERO)
	, EndPosition(float4::ZERO)
	, LerpPos(float4::ZERO)
	, BatLerpRatio(0.0f)
	, YValue(500.0f)
	, YAdd(0.0f)
	, ReAppearTime(0.0f)
	, IsYOut(false)
{
}

MortimerFreezeIceBat::~MortimerFreezeIceBat()
{
}
	
CollisionReturn MortimerFreezeIceBat::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	GameEngineSoundPlayer Tmp = GameEngineSound::SoundPlayControl("sfx_DLC_SnowCult_P2_Popsicle_Bat_Death_01.wav");
	Tmp.Volume(0.3f);

	_This->Death();

	if (BatColor == ColorType::Green)
	{
		Renderer->ChangeFrameAnimation("IceBatDeath_Green");
	}
	if (BatColor == ColorType::Pink)
	{
		Renderer->ChangeFrameAnimation("IceBatDeath_Pink");
	}
	if (BatColor == ColorType::Yellow)
	{
		Renderer->ChangeFrameAnimation("IceBatDeath_Yellow");
	}

	DeathRenderer->ChangeFrameAnimation("IceBat_DeathB", true);
	DeathRenderer->GetTransform().SetLocalPosition(float4{ 0.0f,-20.0f });
	DeathRenderer->On();

	_Other->GetActor<Weapon>()->Attacked();
	
	return CollisionReturn::ContinueCheck;
}

void MortimerFreezeIceBat::SetColorType(ColorType _Type)
{
	BatColor = _Type;

	if (BatColor == ColorType::Green && CurBatDir == BatDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceBatFlap_Antic_Green");
		Collision->On();
	}
	if (BatColor == ColorType::Green && CurBatDir == BatDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceBatFlap_Antic_Green");
		Renderer->GetTransform().PixLocalNegativeX();
		Collision->On();
	}

	if (BatColor == ColorType::Pink && CurBatDir == BatDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceBatFlap_Antic_Pink");
		CollisionParry->On();
	}
	if (BatColor == ColorType::Pink && CurBatDir == BatDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceBatFlap_Antic_Pink");
		Renderer->GetTransform().PixLocalNegativeX();
		CollisionParry->On();
	}

	if (BatColor == ColorType::Yellow && CurBatDir == BatDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceBatFlap_Antic_Yellow");
		Collision->On();
	}
	if (BatColor == ColorType::Yellow && CurBatDir == BatDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceBatFlap_Antic_Yellow");
		Renderer->GetTransform().PixLocalNegativeX();
		Collision->On();
	}

	Renderer->SetScaleModeImage();
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void MortimerFreezeIceBat::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		// Green
		Renderer->CreateFrameAnimationFolder("IceBatFlap_Antic_Green", FrameAnimation_DESC("IceBat_Flap_Antic", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("IceBatFlap_Green", FrameAnimation_DESC("IceBat_Flap_Green", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatSwoop_Green", FrameAnimation_DESC("IceBat_Swoop_Green", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatOutro_Trans_Green", FrameAnimation_DESC("IceBat_Outro_Trans_Green", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("IceBatOutro_Green", FrameAnimation_DESC("IceBat_Outro_Green", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatDeath_Green", FrameAnimation_DESC("IceBat_DeathA_Green", 0.06f, false));

		// Pink
		Renderer->CreateFrameAnimationFolder("IceBatFlap_Antic_Pink", FrameAnimation_DESC("IceBat_Flap_Antic_Pink", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("IceBatFlap_Pink", FrameAnimation_DESC("IceBat_Flap_Pink", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatSwoop_Pink", FrameAnimation_DESC("IceBat_Swoop_Pink", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatOutro_Trans_Pink", FrameAnimation_DESC("IceBat_Outro_Trans_Pink", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("IceBatOutro_Pink", FrameAnimation_DESC("IceBat_Outro_Pink", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatDeath_Pink", FrameAnimation_DESC("IceBat_DeathA_Pink", 0.06f, false));
		
		// Yellow
		Renderer->CreateFrameAnimationFolder("IceBatFlap_Antic_Yellow", FrameAnimation_DESC("IceBat_Flap_Antic_Yellow", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("IceBatFlap_Yellow", FrameAnimation_DESC("IceBat_Flap_Yellow", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatSwoop_Yellow", FrameAnimation_DESC("IceBat_Swoop_Yellow", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatOutro_Trans_Yellow", FrameAnimation_DESC("IceBat_Outro_Trans_Yellow", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("IceBatOutro_Yellow", FrameAnimation_DESC("IceBat_Outro_Yellow", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("IceBatDeath_Yellow", FrameAnimation_DESC("IceBat_DeathA_Yellow", 0.06f, false));
	}

	{
		DeathRenderer = CreateComponent<GameEngineTextureRenderer>();
		DeathRenderer->CreateFrameAnimationFolder("IceBat_DeathB", FrameAnimation_DESC("IceBat_DeathB", 0.06f, false));

		DeathRenderer->ChangeFrameAnimation("IceBat_DeathB");
		DeathRenderer->SetScaleModeImage();
		DeathRenderer->ScaleToTexture();
		DeathRenderer->SetPivot(PIVOTMODE::CENTER);
		DeathRenderer->Off();
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 50,80,-1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
		Collision->Off();
	}
	{
		CollisionParry = CreateComponent<GameEngineCollision>();
		CollisionParry->GetTransform().SetLocalScale({ 50,80,-1 });
		CollisionParry->ChangeOrder(OBJECTORDER::Parry);
		CollisionParry->Off();
	}

	Renderer->AnimationBindEnd("IceBatFlap_Antic_Green", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("IceBatFlap_Green");
		});

	Renderer->AnimationBindEnd("IceBatFlap_Antic_Pink", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("IceBatFlap_Pink");
		});

	Renderer->AnimationBindEnd("IceBatFlap_Antic_Yellow", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("IceBatFlap_Yellow");
		});

	Renderer->AnimationBindEnd("IceBatDeath_Green", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	Renderer->AnimationBindEnd("IceBatDeath_Pink", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	Renderer->AnimationBindEnd("IceBatDeath_Yellow", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});
}

void MortimerFreezeIceBat::Update(float _DeltaTime)
{
	ReAppearTime -= _DeltaTime;

	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Weapon, CollisionType::CT_OBB2D, std::bind(&MortimerFreezeIceBat::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	CollisionParry->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Weapon, CollisionType::CT_OBB2D, std::bind(&MortimerFreezeIceBat::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));


	if (-400.0f <= GetTransform().GetLocalPosition().y && false == IsYOut && 0.0f >= ReAppearTime)
	{
		Renderer->On();
		IsYOut = true;
		YValue = 1000.0f;
		CurBatDir = static_cast<BatDIR>(GameEngineRandom::MainRandom.RandomInt(0, 1));
		float BatRandomMove = GameEngineRandom::MainRandom.RandomFloat(1300.0f, 1400.0f);
		float YRandom = -GameEngineRandom::MainRandom.RandomFloat(100.0f, 200.0f);
		if (BatDIR::LEFT == CurBatDir)
		{
			SetMovePos(float4{ 1500, YRandom, -1 }, float4{ 1500, YRandom, -1 } + float4{ -BatRandomMove, 0 });
			GetTransform().SetLocalPosition(float4{ 1500, YRandom, 0 });
			Renderer->GetTransform().PixLocalPositiveX();
		}
		if (BatDIR::RIGHT == CurBatDir)
		{
			SetMovePos(float4{ 0, YRandom, -1 }, float4{ 0, YRandom, -1 } + float4{ BatRandomMove, 0 });
			GetTransform().SetLocalPosition(float4{ 0, YRandom,0 });
			Renderer->GetTransform().PixLocalNegativeX();
		}

		BatLerpRatio = 0.0f;
	}

	if (BatDIR::LEFT == CurBatDir && true == IsYOut)
	{
		if (1510.0f <= GetTransform().GetLocalPosition().x)
		{
			Death();
		}
	}
	if (BatDIR::RIGHT == CurBatDir && true == IsYOut)
	{
		if (-10.0f >= GetTransform().GetLocalPosition().x)
		{
			Death();
		}
	}

	if (true == IsYOut)
	{
		BatLerpRatio += _DeltaTime * 0.4f;
	}
	else
	{
		BatLerpRatio += _DeltaTime;
	}

	LerpPos = float4::LerpLimit(StartPosition, EndPosition, BatLerpRatio);

	float LerpY = GameEngineMath::LerpLimit(-YValue, YValue, BatLerpRatio) * _DeltaTime;

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 AddPos = float4(0, YAdd, 0);
	if (YAdd <= -600)
	{
		AddPos = float4(0, -600, 0);
	}
	if (true == GetLevel<MortimerFreezeLevel>()->GetIsMove())
	{
		float Phase3Y = GameEngineMath::LerpLimit(0, -700, GetLevel<MortimerFreezeLevel>()->GetMoveTImer() * 0.5f);
		AddPos += float4(0, Phase3Y, 0);
	}

	float4 MFMovePos = LerpPos + AddPos;
	GetTransform().SetLocalPosition(MFMovePos);

	if (1.0 <= BatLerpRatio)
	{
		if (true == IsYOut)
		{
			Death();
		}

		Renderer->Off();
	}
}

