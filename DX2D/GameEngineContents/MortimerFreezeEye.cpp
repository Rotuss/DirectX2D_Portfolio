#include "PreCompile.h"
#include "MortimerFreezeEye.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeEye::MortimerFreezeEye()
	: Renderer(nullptr)
	, EffectRenderer00(nullptr)
	, EffectRenderer01(nullptr)
	, Collision(nullptr)
	, LineCollision(nullptr)
	, EyePosition()
	, LerpPos()
	, StartPosition()
	, EndPosition()
	, SoundRepeatTime(0.0f)
	, EyeLerpRatio(1.0f)
	, XValue(0.0f)
	, XAdd(0.0f)
	, LineTime(0.5f)
	, EyeMoveCount(4)
{
}

MortimerFreezeEye::~MortimerFreezeEye() 
{
}

void MortimerFreezeEye::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Eyeball", FrameAnimation_DESC("Eyeball", 0.06f, true));
	
	Renderer->ChangeFrameAnimation("Eyeball");
	Renderer->SetScaleModeImage();
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);

	EffectRenderer00 = CreateComponent<GameEngineTextureRenderer>();
	EffectRenderer00->CreateFrameAnimationFolder("Eyeball_VFX_Line", FrameAnimation_DESC("Eyeball_VFX", 0, 6, 0.08f, false));
	EffectRenderer00->CreateFrameAnimationFolder("Eyeball_VFX", FrameAnimation_DESC("Eyeball_VFX", 7, 13, 0.06f, true));

	EffectRenderer00->ChangeFrameAnimation("Eyeball_VFX");
	EffectRenderer00->SetScaleModeImage();
	EffectRenderer00->ScaleToTexture();
	EffectRenderer00->SetPivot(PIVOTMODE::CENTER);

	EffectRenderer01 = CreateComponent<GameEngineTextureRenderer>();
	EffectRenderer01->CreateFrameAnimationFolder("Eyeball_VFX_LineOut", FrameAnimation_DESC("Eyeball_VFX", 14, 15, 0.08f, false));

	EffectRenderer01->ChangeFrameAnimation("Eyeball_VFX_LineOut");
	EffectRenderer01->SetScaleModeImage();
	EffectRenderer01->ScaleToTexture();
	EffectRenderer01->SetPivot(PIVOTMODE::CENTER);
	EffectRenderer01->Off();

	EffectRenderer00->AnimationBindEnd("Eyeball_VFX_Line", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EffectRenderer00->ChangeFrameAnimation("Eyeball_VFX");
			EffectRenderer01->ChangeFrameAnimation("Eyeball_VFX_LineOut", true);
			EffectRenderer01->On();

			LineCollision->Off();
		});

	EffectRenderer01->AnimationBindEnd("Eyeball_VFX_LineOut", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			LineTime = GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f);
			EffectRenderer01->Off();
		});

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 120,120,-1 });
	Collision->ChangeOrder(OBJECTORDER::Boss);

	LineCollision = CreateComponent<GameEngineCollision>();
	LineCollision->GetTransform().SetLocalScale({ 30,1500,-1 });
	LineCollision->ChangeOrder(OBJECTORDER::Boss);
	LineCollision->Off();
}

void MortimerFreezeEye::Update(float _DeltaTime)
{
	SoundRepeatTime -= _DeltaTime;
	if (0 >= SoundRepeatTime)
	{
		SoundRepeatTime = 2.0f;
		
		GameEngineSoundPlayer Tmp = GameEngineSound::SoundPlayControl("sfx_DLC_SnowCult_P3_Snowflake_Eyeball_Attack_Loop.wav");
		Tmp.Volume(0.6f);
	}
	
	if (1.0f <= EyeLerpRatio)
	{
		EyeLerpRatio = 0.0f;
		--EyeMoveCount;

		if (EyePos::LeftTop == EyePosition)
		{
			if (3 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ -600.0f,0,0 };
				XValue = 0.0f;
			}
			if (2 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,-300.0f,0 };
				XValue = 200.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 900.0f,0,0 };
				XValue = 0.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,200.0f,0 };
				XValue = 0.0f;
				EffectRenderer00->Off();
			}
		}
		if (EyePos::LeftBot == EyePosition)
		{
			if (3 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ -600.0f,0,0 };
				XValue = 0.0f;
			}
			if (2 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,300.0f,0 };
				XValue = 200.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 900.0f,0,0 };
				XValue = 0.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,-200.0f,0 };
				XValue = 0.0f;
				EffectRenderer00->Off();
			}
		}
		if (EyePos::RightTop == EyePosition)
		{
			if (3 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ 600.0f,0,0 };
				XValue = 0.0f;
			}
			if (2 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,-300.0f,0 };
				XValue = -200.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ -900.0f,0,0 };
				XValue = 0.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,200.0f,0 };
				XValue = 0.0f;
				EffectRenderer00->Off();
			}
		}
		if (EyePos::RightBot == EyePosition)
		{
			if (3 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ 600.0f,0,0 };
				XValue = 0.0f;
			}
			if (2 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,300.0f,0 };
				XValue = -200.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ -900.0f,0,0 };
				XValue = 0.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,-200.0f,0 };
				XValue = 0.0f;
				EffectRenderer00->Off();
			}
		}
	}
	
	LineTime -= _DeltaTime;
	if (0 >= LineTime)
	{
		GameEngineSoundPlayer Tmp = GameEngineSound::SoundPlayControl("sfx_DLC_SnowCult_P3_Snowflake_Eyeball_Zap_01.wav");
		Tmp.Volume(0.6f);
		
		EffectRenderer00->ChangeFrameAnimation("Eyeball_VFX_Line");
		LineCollision->On();
		
		LineTime = 5.0f;
	}

	EyeLerpRatio += _DeltaTime;
	if (1.0f <= EyeLerpRatio)
	{
		if (0 == EyeMoveCount)
		{
			Death();
		}
		EyeLerpRatio = 1.0f;
	}

	if (0 == EyeMoveCount)
	{
		Renderer->GetPixelData().MulColor.a -= _DeltaTime;
	}

	LerpPos = float4::LerpLimit(StartPosition, EndPosition, EyeLerpRatio);

	float LerpX = GameEngineMath::LerpLimit(-XValue, XValue, EyeLerpRatio) * _DeltaTime;

	XAdd += LerpX;
	if (0 < XValue)
	{
		if (0 <= XAdd)
		{
			XAdd = 0.0f;
		}
	}
	else
	{
		if (0 >= XAdd)
		{
			XAdd = 0.0f;
		}
	}
	
	float4 EyeMovePos = LerpPos + float4(XAdd, 0, 0);
	GetTransform().SetLocalPosition(EyeMovePos);
}

