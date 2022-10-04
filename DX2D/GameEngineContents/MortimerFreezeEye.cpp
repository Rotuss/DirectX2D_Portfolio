#include "PreCompile.h"
#include "MortimerFreezeEye.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeEye::MortimerFreezeEye() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, EyePosition()
	, LerpPos()
	, StartPosition()
	, EndPosition()
	, EyeLerpRatio(1.0f)
	, XValue(0.0f)
	, XAdd(0.0f)
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

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 120,120,-1 });
	Collision->ChangeOrder(OBJECTORDER::Boss);
}

void MortimerFreezeEye::Update(float _DeltaTime)
{
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
			}
		}
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

