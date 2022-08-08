#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "GlobalContents.h"
#include <iostream>

MortimerFreezeBoss::MortimerFreezeBoss() 
	: Renderer(nullptr)
	, CurrentDir(MFDir::RIGHT)
	, Dir(float4::ZERO)
	, Speed(200.0f)
{
}

MortimerFreezeBoss::~MortimerFreezeBoss() 
{
}

void MortimerFreezeBoss::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("MFIdle", FrameAnimation_DESC("MFIdle", 0, 23, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("MFIdleTrans", FrameAnimation_DESC("MFIdle", 24, 32, 0.1f, true));
		Renderer->ChangeFrameAnimation("MFIdle");
		//Renderer->AnimationBindEnd("Move", &Player::TestFunction, this);
		Renderer->ScaleToTexture();
		//Renderer->SetPivot(PIVOTMODE::CENTER);
		//Renderer->GetTransform().SetLocalPosition({ 1350, -380, -1 });
	}

	StateManager.CreateStateMember("MFIdle", this, &MortimerFreezeBoss::IdleUpdate, &MortimerFreezeBoss::IdleStart);
	StateManager.ChangeState("MFIdle");
}

void MortimerFreezeBoss::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);
}

void MortimerFreezeBoss::IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFIdle");
	Dir = GetTransform().GetDownVector() * 100.0f;
	Dir += GetTransform().GetLeftVector() * 400.0f;
}

void MortimerFreezeBoss::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Renderer->GetTransform().SetLocalMove(Dir * _DeltaTime);

	if (MFDir::LEFT == CurrentDir)
	{
		if (-100 > Renderer->GetTransform().GetLocalPosition().y)
		{
			Dir = GetTransform().GetUpVector() * 100.0f;
			Dir += GetTransform().GetRightVector() * 400.0f;
		}
		else if (0 < Renderer->GetTransform().GetLocalPosition().y)
		{
			Dir = GetTransform().GetDownVector() * 100.0f;
			Dir += GetTransform().GetRightVector() * 400.0f;
		}

		// 픽셀 충돌을 이용하여 방향 전환이 옳은 듯
		if (-100 < Renderer->GetTransform().GetLocalPosition().x)
		{
			Renderer->ChangeFrameAnimation("MFIdleTrans");
			CurrentDir = MFDir::RIGHT;
		}
	}
	
	if (MFDir::RIGHT == CurrentDir)
	{
		if (-100 > Renderer->GetTransform().GetLocalPosition().y)
		{
			Dir = GetTransform().GetUpVector() * 100.0f;
			Dir += GetTransform().GetLeftVector() * 400.0f;
		}
		else if (0 < Renderer->GetTransform().GetLocalPosition().y)
		{
			Dir = GetTransform().GetDownVector() * 100.0f;
			Dir += GetTransform().GetLeftVector() * 400.0f;
		}

		// 픽셀 충돌을 이용하여 방향 전환이 옳은 듯
		if (-800 > Renderer->GetTransform().GetLocalPosition().x)
		{
			Renderer->ChangeFrameAnimation("MFIdleTrans");
			CurrentDir = MFDir::LEFT;
		}
	}
}
