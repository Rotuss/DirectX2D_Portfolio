#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "MortimerFreezeBlade.h"
#include <GameEngineBase/GameEngineRandom.h>

void MortimerFreezeBoss::Phase2Start(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsKey("Num1_Peashot"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1_Dash", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Num2_Fridge", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Num3_Smash", VK_NUMPAD3);
	}

	StateManager2.CreateStateMember("MF2Idle", std::bind(&MortimerFreezeBoss::P2IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P2IdleStart, this, std::placeholders::_1));

	StateManager2.CreateStateMember("Dash", std::bind(&MortimerFreezeBoss::AttackDashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackDashStart, this, std::placeholders::_1));
	StateManager2.CreateStateMember("Fridge", std::bind(&MortimerFreezeBoss::AttackFridgeUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackFridgeStart, this, std::placeholders::_1));
	StateManager2.CreateStateMember("Smash", std::bind(&MortimerFreezeBoss::AttackSmashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackSmashStart, this, std::placeholders::_1));
	StateManager2.CreateStateMember("Transition_Phase3", std::bind(&MortimerFreezeBoss::Phase2to3Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase2to3Start, this, std::placeholders::_1));

	StateManager2.ChangeState("MF2Idle");
}

void MortimerFreezeBoss::Phase2Update(float _DeltaTime, const StateInfo& _Info)
{
	StateManager2.Update(_DeltaTime);
}

void MortimerFreezeBoss::P2IdleStart(const StateInfo& _Info)
{
}

void MortimerFreezeBoss::P2IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float DashRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float FridgeRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float SmashRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);

	{
		if (0.8f >= DashRandomPer && 0 >= DashTime)
		{
			if (PrevSkill == 1)
			{
				return;
			}
			DashTime = GameEngineRandom::MainRandom.RandomFloat(0.2f, 1.0f);
			StateManager2.ChangeState("Dash");
			PrevSkill = 1;
			return;
		}

		if (0 >= DashTime)
		{
			DashTime = GameEngineRandom::MainRandom.RandomFloat(0.2f, 0.5f);
		}
	}

	{
		if (0.8f >= FridgeRandomPer && 0 >= FridgeTime)
		{
			if (PrevSkill == 2)
			{
				return;
			}
			FridgeTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f);
			StateManager2.ChangeState("Fridge");
			PrevSkill = 2;
			return;
		}

		if (0 >= FridgeTime)
		{
			FridgeTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 0.8f);
		}
	}

	{
		if (0.8f >= SmashRandomPer && 0 >= SmashTime)
		{
			/*if (PrevSkill == 3)
			{
				return;
			}*/
			SmashTime = GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f);
			StateManager2.ChangeState("Smash");
			PrevSkill = 3;
			return;
		}

		if (0 >= SmashTime)
		{
			SmashTime = GameEngineRandom::MainRandom.RandomFloat(0.8f, 0.9f);
		}
	}

	DashTime -= _DeltaTime;
	FridgeTime -= _DeltaTime;
	SmashTime -= _DeltaTime;
}

void MortimerFreezeBoss::AttackDashStart(const StateInfo& _Info)
{
	DashMove = GameEngineRandom::MainRandom.RandomInt(1, 3);
}

void MortimerFreezeBoss::AttackDashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;

	if (0 >= DashMove)
	{
		StateManager2.ChangeState("MF2Idle");
		return;
	}

	if(MFBossDIR::LEFT == CurMFDir)
	{
		// 왼쪽 방향으로 가다가 분기점 도달했을 때, 오른쪽 방향으로 이동할 수 있게 전환
		if (StartPos[2].x >= MFCurXPos && IdleLerpRatio >= 1.0f)
		{
			CurMFDir = MFBossDIR::RIGHT;
			Num = 2;
			IdleLerpRatio = 0.0f;
			IsJump = static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1));
			DashMove -= 1;
			return;
		}
	}
	else
	{
		if (StartPos[3].x <= MFCurXPos)
		{
			CurMFDir = MFBossDIR::LEFT;
			Num = 3;
			IdleLerpRatio = 0.0f;
			IsJump = static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1));
			DashMove -= 1;
			return;
		}
	}
	
	IdleLerpRatio += _DeltaTime;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	if (true == IsJump)
	{
		float LerpY = GameEngineMath::LerpLimit(500, -500, IdleLerpRatio) * _DeltaTime;

		YAdd += LerpY;
		if (0 >= YAdd)
		{
			YAdd = 0.0f;
		}
	}
	else
	{
		YAdd = 0.0f;
	}

	LerpPos = float4::LerpLimit(StartPos[Num], EndPos[Num], IdleLerpRatio);

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

void MortimerFreezeBoss::AttackFridgeStart(const StateInfo& _Info)
{
	IceCubeCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
	IceBatCount = 4;
	// Fridge 애니메이션 끝났을 때 상태 전환(바인드엔드)
}

void MortimerFreezeBoss::AttackFridgeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	IceTime -= _DeltaTime;

	if (0.0f >= IceTime)
	{
		if (0 == IceBatCount)
		{
			return;
		}

		if (0 == IceCubeCount)
		{
			IceTime = 0.1f;
			--IceBatCount;
			// 배트 생성

			if (0 == IceBatCount)
			{
				// Fridge 애니메이션 변경
			}
			return;
		}

		IceTime = 1.0f;
		--IceCubeCount;
		// 큐브 생성

		if (0 == IceCubeCount)
		{
			IceTime = 0.5f;
		}
	}
}

void MortimerFreezeBoss::AttackSmashStart(const StateInfo& _Info)
{
	// 스매시 애니메이션바인드엔드에 BladeTime 시간설정 + BladeCount 4 설정, StateManager2.ChangeState("MF2Idle");
	BladeTime = 0.0f;
	BladeCount = 4;
}

void MortimerFreezeBoss::AttackSmashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	BladeTime -= _DeltaTime;

	if (0.0f < BladeTime)
	{
		return;
	}

	if (0 < BladeCount)
	{
		BladeTime = 1.0f;
		--BladeCount;

		// Blade 생성(좌우 방향 CurMFDir 확인 후 간격 조정-카운트에 맞춰-)
		if (MFBossDIR::LEFT == CurMFDir)
		{
			MortimerFreezeBlade* Ptr = GetLevel()->CreateActor<MortimerFreezeBlade>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() - float4{ 100.0f * (4 - BladeCount),0,0});
		}
		if (MFBossDIR::RIGHT == CurMFDir)
		{
			MortimerFreezeBlade* Ptr = GetLevel()->CreateActor<MortimerFreezeBlade>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 100.0f * (4 - BladeCount),0,0});
		}
	}
}

void MortimerFreezeBoss::Phase2to3Start(const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase2to3Update(float _DeltaTime, const StateInfo& _Info)
{
}
