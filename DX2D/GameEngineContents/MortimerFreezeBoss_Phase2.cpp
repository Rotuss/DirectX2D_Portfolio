#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "MortimerFreezeIceCube.h"
#include "MortimerFreezeIceBat.h"
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
	Renderer->ChangeFrameAnimation("MF2Idle");
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
			if (PrevSkill == 3)
			{
				return;
			}
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
	Renderer->ChangeFrameAnimation("SnowBeastFridge_Morph");
	
	Renderer->AnimationBindEnd("SnowBeastFridge_Morph", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeastFridge_Shoot");
			IsShoot = true;
		});

	Renderer->AnimationBindEnd("SnowBeastFridge_Shoot", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			//--IceCubeCount;
			
			if (0 == IceCubeCount)
			{
				Renderer->ChangeFrameAnimation("SnowBeastFridge_Freezer");

				/*if (MFBossDIR::LEFT == CurMFDir)
				{
					AddRenderer->ChangeFrameAnimation("SnowBeastFridgeFreezer_Top");
					AddRenderer->GetTransform().PixLocalPositiveX();
					AddRenderer->GetTransform().SetLocalPosition(float4{ 100, 100, -1.5 });
					AddRenderer->On();
				}
				if (MFBossDIR::RIGHT == CurMFDir)
				{
					AddRenderer->ChangeFrameAnimation("SnowBeastFridgeFreezer_Top");
					AddRenderer->GetTransform().PixLocalNegativeX();
					AddRenderer->GetTransform().SetLocalPosition(float4{ -100, 100, -1.5 });
					AddRenderer->On();
				}*/

				return;
			}

			--IceCubeCount;
		});

	Renderer->AnimationBindFrame("SnowBeastFridge_Freezer", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if ( 4 == _Info.CurFrame)
			{
				IsBatOpen = true;
			}
		});

	Renderer->AnimationBindEnd("SnowBeastFridge_Freezer_Outro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager2.ChangeState("MF2Idle");
		});

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

		if (0 == IceCubeCount && true == IsBatOpen)
		{
			IceTime = 0.5f;
			--IceBatCount;

			float BatRandomMove = GameEngineRandom::MainRandom.RandomFloat(100.0f, 500.0f);
			// 배트 생성
			MortimerFreezeIceBat* BPtr = GetLevel()->CreateActor<MortimerFreezeIceBat>(OBJECTORDER::Boss);
			if (MFBossDIR::LEFT == CurMFDir)
			{
				BPtr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 0,-30,0 }, GetTransform().GetLocalPosition() + float4{ -BatRandomMove, 300 });
			}
			if (MFBossDIR::RIGHT== CurMFDir)
			{
				BPtr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 0,-30,0 }, GetTransform().GetLocalPosition() + float4{ BatRandomMove, 300 });
			}
			BPtr->SetColorType(static_cast<ColorType>(GameEngineRandom::MainRandom.RandomInt(0, 2)));
			BPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-30,0 });
			BPtr->SetReAppearTime(GameEngineRandom::MainRandom.RandomFloat(3.0f, 5.0f) * (4 - IceBatCount));
			
			if (0 == IceBatCount)
			{
				IceBatCount = -1;
				IsBatOpen = false;
				// Fridge 애니메이션 변경
				Renderer->ChangeFrameAnimation("SnowBeastFridge_Freezer_Outro");
			}
			return;
		}

		if (true == IsShoot)
		{
			IceTime = 1.0f;
			//--IceCubeCount;
			// 큐브 생성
			MortimerFreezeIceCube* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCube>(OBJECTORDER::Boss);
			Ptr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 0,-200,0 }, MsChalice::Chalice->GetTransform().GetLocalPosition());
			Ptr->SetSizeType(static_cast<SizeType>(GameEngineRandom::MainRandom.RandomInt(0, 1)));
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-200,0 });
			Ptr->SetColMap(MsChalice::Chalice->GetColMap());

			if (0 == IceCubeCount)
			{
				//IceTime = 0.5f;
				IsShoot = false;
			}
		}
	}
}

void MortimerFreezeBoss::AttackSmashStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("SnowBeastSmash");
	
	Renderer->AnimationBindEnd("SnowBeastSmash", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeastSmashOutro");
		});

	Renderer->AnimationBindEnd("SnowBeastSmashOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager2.ChangeState("MF2Idle");
		});

	// 스매시 애니메이션바인드엔드에 BladeTime 시간설정 + BladeCount 4 설정, StateManager2.ChangeState("MF2Idle");
	BladeTime = 2.0f;
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
		BladeTime = 0.3f;
		--BladeCount;

		// Blade 생성(좌우 방향 CurMFDir 확인 후 간격 조정-카운트에 맞춰-)
		if (MFBossDIR::LEFT == CurMFDir)
		{
			MortimerFreezeBlade* Ptr = GetLevel()->CreateActor<MortimerFreezeBlade>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() - float4{ 265.0f * (4 - BladeCount),480,0});
		}
		if (MFBossDIR::RIGHT == CurMFDir)
		{
			MortimerFreezeBlade* Ptr = GetLevel()->CreateActor<MortimerFreezeBlade>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 265.0f * (4 - BladeCount),-480,0});
		}
	}
}

void MortimerFreezeBoss::Phase2to3Start(const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase2to3Update(float _DeltaTime, const StateInfo& _Info)
{
}
