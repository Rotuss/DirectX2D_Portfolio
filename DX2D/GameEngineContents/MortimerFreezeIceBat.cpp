#include "PreCompile.h"
#include "MortimerFreezeIceBat.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeIceBat::MortimerFreezeIceBat()
	: BatColor()
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

void MortimerFreezeIceBat::SetColorType(ColorType _Type)
{
	BatColor = _Type;

	if (BatColor == ColorType::Green && CurBatDir == BatDIR::LEFT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
	}
	if (BatColor == ColorType::Green && CurBatDir == BatDIR::RIGHT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		//Renderer->GetTransform().PixLocalNegativeX();
	}

	if (BatColor == ColorType::Pink && CurBatDir == BatDIR::LEFT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
	}
	if (BatColor == ColorType::Pink && CurBatDir == BatDIR::RIGHT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		//Renderer->GetTransform().PixLocalNegativeX();
	}

	if (BatColor == ColorType::Yellow && CurBatDir == BatDIR::LEFT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
	}
	if (BatColor == ColorType::Yellow && CurBatDir == BatDIR::RIGHT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		//Renderer->GetTransform().PixLocalNegativeX();
	}

	//Renderer->SetScaleModeImage();
	//Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void MortimerFreezeIceBat::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 50, 50, 1 });
	}
}

void MortimerFreezeIceBat::Update(float _DeltaTime)
{
	ReAppearTime -= _DeltaTime;

	if (-100.0f <= GetTransform().GetLocalPosition().y && false == IsYOut && 0.0f >= ReAppearTime)
	{
		IsYOut = true;
		YValue = 1000.0f;
		CurBatDir = static_cast<BatDIR>(GameEngineRandom::MainRandom.RandomInt(0, 1));
		float BatRandomMove = GameEngineRandom::MainRandom.RandomFloat(1300.0f, 1400.0f);
		float YRandom = -GameEngineRandom::MainRandom.RandomFloat(100.0f, 200.0f);
		if (BatDIR::LEFT == CurBatDir)
		{
			SetMovePos(float4{ 1500, YRandom, 0 }, float4{ 1500, YRandom, 0 } + float4{ -BatRandomMove, 0 });
			GetTransform().SetLocalPosition(float4{ 1500, YRandom, 0 });
		}
		if (BatDIR::RIGHT == CurBatDir)
		{
			SetMovePos(float4{ 0, YRandom, 0 }, float4{ 0, YRandom, 0 } + float4{ BatRandomMove, 0 });
			GetTransform().SetLocalPosition(float4{ 0, YRandom,0 });
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
	float4 MFMovePos = LerpPos + AddPos;
	GetTransform().SetLocalPosition(MFMovePos);
}

