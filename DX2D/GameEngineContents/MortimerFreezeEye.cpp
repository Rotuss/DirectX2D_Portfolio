#include "PreCompile.h"
#include "MortimerFreezeEye.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeEye::MortimerFreezeEye() 
	: Renderer(nullptr)
	, EyePosition()
	, LerpPos()
	, StartPosition()
	, EndPosition()
	, EyeLerpRatio(1.0f)
	, XValue(0.0f)
	, XAdd(0.0f)
	, EyeMoveCount(3)
{
}

MortimerFreezeEye::~MortimerFreezeEye() 
{
}

void MortimerFreezeEye::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
}

void MortimerFreezeEye::Update(float _DeltaTime)
{
	if (0 > EyeMoveCount)
	{
		//
	}
	
	if (1.0f <= EyeLerpRatio)
	{
		EyeLerpRatio = 0.0f;
		--EyeMoveCount;

		if (EyePos::LeftTop == EyePosition)
		{
			if (2 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ 300.0f,0,0 };
				XValue = 0.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,-100.0f,0 };
				XValue = 200.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ -300.0f,0,0 };
				XValue = 0.0f;
			}
		}
		if (EyePos::LeftBot == EyePosition)
		{
			if (2 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ 300.0f,0,0 };
				XValue = 0.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,100.0f,0 };
				XValue = 200.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ -300.0f,0,0 };
				XValue = 0.0f;
			}
		}
		if (EyePos::RightTop == EyePosition)
		{
			if (2 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ -300.0f,0,0 };
				XValue = 0.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,-100.0f,0 };
				XValue = 200.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 300.0f,0,0 };
				XValue = 0.0f;
			}
		}
		if (EyePos::RightBot == EyePosition)
		{
			if (2 == EyeMoveCount)
			{
				EndPosition = StartPosition + float4{ -300.0f,0,0 };
				XValue = 0.0f;
			}
			if (1 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 0,100.0f,0 };
				XValue = 200.0f;
			}
			if (0 == EyeMoveCount)
			{
				StartPosition = EndPosition;
				EndPosition = StartPosition + float4{ 300.0f,0,0 };
				XValue = 0.0f;
			}
		}
	}
	
	LerpPos = float4::LerpLimit(StartPosition, EndPosition, EyeLerpRatio);

	float LerpX = GameEngineMath::LerpLimit(-XValue, XValue, EyeLerpRatio) * _DeltaTime;

	XAdd += LerpX;
	if (0 <= XAdd)
	{
		XAdd = 0.0f;
	}
	
	float4 EyeMovePos = LerpPos + float4(XAdd, 0, 0);
	GetTransform().SetLocalPosition(EyeMovePos);
}

