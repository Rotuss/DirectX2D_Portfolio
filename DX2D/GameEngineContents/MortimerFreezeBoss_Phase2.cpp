#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "MortimerFreezeLevel.h"
#include "MortimerFreezeIceCube.h"
#include "MortimerFreezeIceBat.h"
#include "MortimerFreezeBlade.h"
#include "MortimerFreezeSnowPlatform.h"
#include <GameEngineBase/GameEngineRandom.h>

void MortimerFreezeBoss::Phase2Start(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsKey("Num1_Peashot"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1_Dash", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Num2_Fridge", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Num3_Smash", VK_NUMPAD3);
	}

	HP = 1;
	Renderer->SetPivot(PIVOTMODE::BOT);
	Collision->GetTransform().SetLocalScale(float4{ 300.0f,400.0f,0.0f });
	Collision->GetTransform().SetLocalPosition(float4{ 0.0f,200.0f,0.0f });
	GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0.0f,-130.0f,0.0f });
	
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
	if (false == Renderer->IsUpdate())
	{
		if (MFBossDIR::LEFT == CurMFDir)
		{
			Renderer->GetTransform().SetLocalPosition(float4{ 21.5f,0.0f,0.0f });
		}
		if (MFBossDIR::RIGHT == CurMFDir)
		{
			Renderer->GetTransform().SetLocalPosition(float4{ -21.5f,0.0f,0.0f });
		}
		
		Renderer->On();
	}
}

void MortimerFreezeBoss::P2IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float DashRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float FridgeRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float SmashRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);

	if (0 == HP)
	{
		StateManager2.ChangeState("Transition_Phase3");
		return;
	}

	if ("Smash" == PrevState && 0 <= SmashTime)
	{
		SmashTime -= _DeltaTime;
		if (0 >= SmashTime)
		{
			PrevState = "";
		}
		return;
	}

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
			SmashTime = 0.8f;
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
	Renderer->ChangeFrameAnimation("SnowBeast_DashPreAttack");

	Renderer->AnimationBindEnd("SnowBeast_Jump_Attack", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsPreparing = false;
			CurMeltingDir = CurMFDir;
			Renderer->ChangeFrameAnimation("SnowBeast_DashSnowBeastBall");
			if (MFBossDIR::LEFT == CurMFDir)
			{
				// 출발 앞
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA", true);
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				/*EffectRenderer00->ChangeFrameAnimation("SnowBeast_Jump_FXA", true);
				EffectRenderer00->GetTransform().PixLocalPositiveX();
				EffectRenderer00->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer00->On();*/

				// 출발 뒤
				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB", true);
				SubRenderer01->GetTransform().PixLocalPositiveX();
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				/*EffectRenderer01->ChangeFrameAnimation("SnowBeast_Jump_FXB", true);
				EffectRenderer01->GetTransform().PixLocalPositiveX();
				EffectRenderer01->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer01->On();*/

				// 도착 앞
				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA", true);
				SubRenderer02->GetTransform().PixLocalNegativeX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				// 도착 뒤
				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB", true);
				SubRenderer03->GetTransform().PixLocalNegativeX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
			else
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA", true);
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				/*EffectRenderer00->ChangeFrameAnimation("SnowBeast_Jump_FXA", true);
				EffectRenderer00->GetTransform().PixLocalNegativeX();
				EffectRenderer00->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer00->On();*/

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB", true);
				SubRenderer01->GetTransform().PixLocalNegativeX();
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				/*EffectRenderer01->ChangeFrameAnimation("SnowBeast_Jump_FXB", true);
				EffectRenderer01->GetTransform().PixLocalNegativeX();
				EffectRenderer01->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer01->On();*/

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA", true);
				SubRenderer02->GetTransform().PixLocalPositiveX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB", true);
				SubRenderer03->GetTransform().PixLocalPositiveX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
		});
	
	Renderer->AnimationBindEnd("SnowBeast_Jump_Attack_NotFirst", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsPreparing = false;
			CurMeltingDir = CurMFDir;
			Renderer->ChangeFrameAnimation("SnowBeast_DashSnowBeastBall");
			if (MFBossDIR::LEFT == CurMFDir)
			{
				// 출발 앞
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA", true);
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				/*EffectRenderer00->ChangeFrameAnimation("SnowBeast_Jump_FXA", true);
				EffectRenderer00->GetTransform().PixLocalPositiveX();
				EffectRenderer00->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer00->On();*/

				// 출발 뒤
				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB", true);
				SubRenderer01->GetTransform().PixLocalPositiveX();
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				/*EffectRenderer01->ChangeFrameAnimation("SnowBeast_Jump_FXB", true);
				EffectRenderer01->GetTransform().PixLocalPositiveX();
				EffectRenderer01->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer01->On();*/

				// 도착 앞
				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA", true);
				SubRenderer02->GetTransform().PixLocalNegativeX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				// 도착 뒤
				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB", true);
				SubRenderer03->GetTransform().PixLocalNegativeX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
			else
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA", true);
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				/*EffectRenderer00->ChangeFrameAnimation("SnowBeast_Jump_FXA", true);
				EffectRenderer00->GetTransform().PixLocalNegativeX();
				EffectRenderer00->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer00->On();*/

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB", true);
				SubRenderer01->GetTransform().PixLocalNegativeX();
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				/*EffectRenderer01->ChangeFrameAnimation("SnowBeast_Jump_FXB", true);
				EffectRenderer01->GetTransform().PixLocalNegativeX();
				EffectRenderer01->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer01->On();*/

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA", true);
				SubRenderer02->GetTransform().PixLocalPositiveX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB", true);
				SubRenderer03->GetTransform().PixLocalPositiveX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
		});

	Renderer->AnimationBindEnd("SnowBeast_Dash_Attack", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsPreparing = false;
			CurMeltingDir = CurMFDir;
			Renderer->ChangeFrameAnimation("SnowBeast_DashSnowBeastBall");
			if (MFBossDIR::LEFT == CurMFDir)
			{
				EffectRenderer02->GetTransform().PixLocalPositiveX();
				EffectRenderer02->GetTransform().SetLocalPosition(float4{ 35.0f,28.0f });
				EffectRenderer02->On();

				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA", true);
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				/*EffectRenderer00->ChangeFrameAnimation("SnowBeast_Dash_FXA", true);
				EffectRenderer00->GetTransform().PixLocalPositiveX();
				EffectRenderer00->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer00->On();*/

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB", true);
				SubRenderer01->GetTransform().PixLocalPositiveX();
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				/*EffectRenderer01->ChangeFrameAnimation("SnowBeast_Dash_FXB", true);
				EffectRenderer01->GetTransform().PixLocalPositiveX();
				EffectRenderer01->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer01->On();*/

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA", true);
				SubRenderer02->GetTransform().PixLocalNegativeX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB", true);
				SubRenderer03->GetTransform().PixLocalNegativeX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
			else
			{
				EffectRenderer02->GetTransform().PixLocalNegativeX();
				EffectRenderer02->GetTransform().SetLocalPosition(float4{ -35.0f,28.0f });
				EffectRenderer02->On();
				
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA", true);
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				/*EffectRenderer00->ChangeFrameAnimation("SnowBeast_Dash_FXA", true);
				EffectRenderer00->GetTransform().PixLocalNegativeX();
				EffectRenderer00->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer00->On();*/

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB", true);
				SubRenderer01->GetTransform().PixLocalNegativeX();
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				/*EffectRenderer01->ChangeFrameAnimation("SnowBeast_Dash_FXB", true);
				EffectRenderer01->GetTransform().PixLocalNegativeX();
				EffectRenderer01->SetPivot(PIVOTMODE::BOT);;
				EffectRenderer01->On();*/

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA", true);
				SubRenderer02->GetTransform().PixLocalPositiveX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB", true);
				SubRenderer03->GetTransform().PixLocalPositiveX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
		});

	Renderer->AnimationBindEnd("SnowBeast_JumptoJump_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_Jump_Attack_NotFirst");
		});

	Renderer->AnimationBindEnd("SnowBeast_DashtoJump_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_Jump_Attack_NotFirst");
		});

	Renderer->AnimationBindEnd("SnowBeast_DashtoAny_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_Dash_Attack");
		});

	Renderer->AnimationBindEnd("SnowBeast_JumptoDash_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_Dash_Attack");
		});

	Renderer->AnimationBindEnd("SnowBeast_JumptoIdle_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_AttacktoIdle_Trans");
		});

	Renderer->AnimationBindEnd("SnowBeast_DashtoIdle_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_AttacktoIdle_Trans");
		});

	Renderer->AnimationBindEnd("SnowBeast_AttacktoIdle_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager2.ChangeState("MF2Idle");
		});

	SubRenderer00->AnimationBindTime("SnowBeast_Limbs_MeltingA", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (MFBossDIR::LEFT == CurMeltingDir)
			{
				SubRenderer00->GetTransform().SetWorldPosition({ 1330,-946,-1 });
			}
			else
			{
				SubRenderer00->GetTransform().SetWorldPosition({ 315,-946,-1 });
			}
		});

	SubRenderer00->AnimationBindEnd("SnowBeast_Limbs_MeltingA", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->CurAnimationReset();
			SubRenderer00->Off();
		});

	EffectRenderer00->AnimationBindTime("SnowBeast_Dash_FXA", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				EffectRenderer00->GetTransform().SetWorldPosition({ 1330,-946,-1 });
			}
			else
			{
				EffectRenderer00->GetTransform().SetWorldPosition({ 315,-946,-1 });
			}
		});

	EffectRenderer00->AnimationBindEnd("SnowBeast_Dash_FXA", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EffectRenderer00->CurAnimationReset();
			EffectRenderer00->Off();
		});

	SubRenderer01->AnimationBindTime("SnowBeast_Limbs_MeltingB", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (MFBossDIR::LEFT == CurMeltingDir)
			{
				SubRenderer01->GetTransform().SetWorldPosition({ 1250,-850,-0.5 });
			}
			else
			{
				SubRenderer01->GetTransform().SetWorldPosition({ 400,-850,-0.5 });
			}
		});

	SubRenderer01->AnimationBindEnd("SnowBeast_Limbs_MeltingB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer01->CurAnimationReset();
			SubRenderer01->Off();
		});
	
	EffectRenderer01->AnimationBindTime("SnowBeast_Dash_FXB", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				EffectRenderer01->GetTransform().SetWorldPosition({ 1250,-850,-0.5 });
			}
			else
			{
				EffectRenderer01->GetTransform().SetWorldPosition({ 400,-850,-0.5 });
			}
		});

	EffectRenderer01->AnimationBindEnd("SnowBeast_Dash_FXB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EffectRenderer01->CurAnimationReset();
			EffectRenderer01->Off();
		});

	SubRenderer02->AnimationBindTime("SnowBeast_Limbs_RMeltingA", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (MFBossDIR::LEFT == CurMeltingDir)
			{
				SubRenderer02->GetTransform().SetWorldPosition({ 315,-946,-1 });
			}
			else
			{
				SubRenderer02->GetTransform().SetWorldPosition({ 1330,-946,-1 });
			}
		});

	//SubRenderer02->AnimationBindFrame("SnowBeast_Limbs_RMeltingA", [/*&*/=](const FrameAnimation_DESC& _Info)
	//	{
	//		if (10 == _Info.CurFrame)
	//		{
	//			if (MFBossDIR::LEFT == CurMeltingDir)
	//			{
	//				AddRenderer->ChangeFrameAnimation("SnowBeast_Limbs_ReformingA", true);
	//				AddRenderer->GetTransform().PixLocalNegativeX();
	//				AddRenderer->SetPivot(PIVOTMODE::BOT);;
	//				AddRenderer->On();
	//			}
	//			else
	//			{
	//				AddRenderer->ChangeFrameAnimation("SnowBeast_Limbs_ReformingA", true);
	//				AddRenderer->GetTransform().PixLocalPositiveX();
	//				AddRenderer->SetPivot(PIVOTMODE::BOT);;
	//				AddRenderer->On();
	//			}
	//		}
	//	});

	SubRenderer02->AnimationBindEnd("SnowBeast_Limbs_RMeltingA", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer02->CurAnimationReset();
			SubRenderer02->Off();
		});

	SubRenderer03->AnimationBindTime("SnowBeast_Limbs_RMeltingB", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (MFBossDIR::LEFT == CurMeltingDir)
			{
				SubRenderer03->GetTransform().SetWorldPosition({ 400,-850,-0.5 });
			}
			else
			{
				SubRenderer03->GetTransform().SetWorldPosition({ 1250,-850,-0.5 });
			}
		});

	//SubRenderer03->AnimationBindFrame("SnowBeast_Limbs_RMeltingB", [/*&*/=](const FrameAnimation_DESC& _Info)
	//	{
	//		if (10 == _Info.CurFrame)
	//		{
	//			if (MFBossDIR::LEFT == CurMeltingDir)
	//			{
	//				AddRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_ReformingB", true);
	//				AddRenderer01->GetTransform().PixLocalNegativeX();
	//				AddRenderer01->SetPivot(PIVOTMODE::BOT);;
	//				AddRenderer01->On();
	//			}
	//			else
	//			{
	//				AddRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_ReformingB", true);
	//				AddRenderer01->GetTransform().PixLocalPositiveX();
	//				AddRenderer01->SetPivot(PIVOTMODE::BOT);;
	//				AddRenderer01->On();
	//			}
	//		}
	//	});

	SubRenderer03->AnimationBindEnd("SnowBeast_Limbs_RMeltingB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer03->CurAnimationReset();
			SubRenderer03->Off();
		});

	AddRenderer->AnimationBindTime("SnowBeast_Limbs_ReformingA", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			// 위치 조정 필요
			if (MFBossDIR::LEFT == CurMeltingDir)
			{
				AddRenderer->GetTransform().SetWorldPosition({ 500,-850,-1.5f });
			}
			else
			{
				AddRenderer->GetTransform().SetWorldPosition({ 1150,-850,-1.5f });
			}
		});

	AddRenderer->AnimationBindEnd("SnowBeast_Limbs_ReformingA", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			AddRenderer->CurAnimationReset();
			AddRenderer->Off();
		});

	AddRenderer01->AnimationBindTime("SnowBeast_Limbs_ReformingB", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			// 위치 조정 필요
			if (MFBossDIR::LEFT == CurMeltingDir)
			{
				AddRenderer01->GetTransform().SetWorldPosition({ 500,-850,-1.5f });
			}
			else
			{
				AddRenderer01->GetTransform().SetWorldPosition({ 1150,-850,-1.5f });
			}
		});

	AddRenderer01->AnimationBindEnd("SnowBeast_Limbs_ReformingB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			AddRenderer01->CurAnimationReset();
			AddRenderer01->Off();
		});

	DashMove = GameEngineRandom::MainRandom.RandomInt(1, 3);
	IsDashPatternBegin = true;
	IsPreparing = false;
	IsPrevDash = false;
	IsPrevJump = false;
}

void MortimerFreezeBoss::AttackDashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;

	if (0 >= DashMove)
	{
		if (0 > DashMove)
		{
			return;
		}

		if (true == IsJump)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_JumptoIdle_Trans");
		}
		else
		{
			Renderer->ChangeFrameAnimation("SnowBeast_DashtoIdle_Trans");
		}
		DashMove = -1;
		return;
	}

	if (true == IsPreparing)
	{
		return;
	}

	if(MFBossDIR::LEFT == CurMFDir)
	{
		if (true == IsDashPatternBegin)
		{
			IsDashPatternBegin = false;
			Num = 3;
			IdleLerpRatio = 0.0f;
			IsJump = static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1));
			if (true == IsJump)
			{
				if (false == IsPrevDash && false == IsPrevJump)
				{
					IsPrevJump = true;
					Renderer->ChangeFrameAnimation("SnowBeast_Jump_Attack");
				}
			}
			else
			{
				if (false == IsPrevDash && false == IsPrevJump)
				{
					IsPrevDash = true;
					Renderer->ChangeFrameAnimation("SnowBeast_Dash_Attack");
				}
			}
			IsPreparing = true;
			return;
		}
		
		// 왼쪽 방향으로 가다가 분기점 도달했을 때, 오른쪽 방향으로 이동할 수 있게 전환
		if (StartPos[2].x >= MFCurXPos && IdleLerpRatio >= 1.0f)
		{
			CurMFDir = MFBossDIR::RIGHT;
			Renderer->GetTransform().PixLocalNegativeX();
			Num = 2;
			IdleLerpRatio = 0.0f;
			IsJump = static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1));
			if (true == IsJump)
			{
				if (true == IsPrevDash)
				{
					IsPrevDash = false;
					IsPrevJump = true;
					Renderer->ChangeFrameAnimation("SnowBeast_DashtoJump_Trans");
					EffectRenderer02->Off();
				}
				if (true == IsPrevJump)
				{
					IsPrevDash = false;
					IsPrevJump = true;
					Renderer->ChangeFrameAnimation("SnowBeast_JumptoJump_Trans");
				}
			}
			else
			{
				if (true == IsPrevDash)
				{
					IsPrevDash = true;
					IsPrevJump = false;
					Renderer->ChangeFrameAnimation("SnowBeast_DashtoAny_Trans");
					EffectRenderer02->Off();
				}
				if (true == IsPrevJump)
				{
					IsPrevDash = true;
					IsPrevJump = false;
					Renderer->ChangeFrameAnimation("SnowBeast_JumptoDash_Trans");
				}
			}
			DashMove -= 1;
			IsPreparing = true;
			return;
		}
	}
	else
	{
		if (true == IsDashPatternBegin)
		{
			IsDashPatternBegin = false;
			Num = 2;
			IdleLerpRatio = 0.0f;
			IsJump = static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1));
			if (true == IsJump)
			{
				if (false == IsPrevDash && false == IsPrevJump)
				{
					IsPrevJump = true;
					Renderer->ChangeFrameAnimation("SnowBeast_Jump_Attack");
				}
			}
			else
			{
				if (false == IsPrevDash && false == IsPrevJump)
				{
					IsPrevDash = true;
					Renderer->ChangeFrameAnimation("SnowBeast_Dash_Attack");
				}
			}
			IsPreparing = true;
			return;
		}
		
		if (StartPos[3].x <= MFCurXPos && IdleLerpRatio >= 1.0f)
		{
			CurMFDir = MFBossDIR::LEFT;
			Renderer->GetTransform().PixLocalPositiveX();
			Num = 3;
			IdleLerpRatio = 0.0f;
			IsJump = static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1));
			if (true == IsJump)
			{
				if (true == IsPrevDash)
				{
					IsPrevDash = false;
					IsPrevJump = true;
					Renderer->ChangeFrameAnimation("SnowBeast_DashtoJump_Trans");
					EffectRenderer02->Off();
				}
				if (true == IsPrevJump)
				{
					IsPrevDash = false;
					IsPrevJump = true;
					Renderer->ChangeFrameAnimation("SnowBeast_JumptoJump_Trans");
				}
			}
			else
			{
				if (true == IsPrevDash)
				{
					IsPrevDash = true;
					IsPrevJump = false;
					Renderer->ChangeFrameAnimation("SnowBeast_DashtoAny_Trans");
					EffectRenderer02->Off();
				}
				if (true == IsPrevJump)
				{
					IsPrevDash = true;
					IsPrevJump = false;
					Renderer->ChangeFrameAnimation("SnowBeast_JumptoDash_Trans");
				}
			}
			DashMove -= 1;
			IsPreparing = true;
			return;
		}
	}
	
	IdleLerpRatio += _DeltaTime * 1.3f;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	if (true == IsJump)
	{
		float LerpY = GameEngineMath::LerpLimit(1600, -1600, IdleLerpRatio) * _DeltaTime;

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
	Renderer->GetTransform().SetLocalPosition(float4{ 0.0f,-20.0f,0.0f });

	Renderer->AnimationBindEnd("SnowBeastFridge_Morph", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeastFridge_Shoot");
			Renderer->GetTransform().SetLocalPosition(float4{ 0.0f,30.0f,0.0f });
			IceTime = 0.1f;
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

	Renderer->AnimationBindEnd("SnowBeastFridge_Freezer", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsBatOpen = true;
			Renderer->ChangeFrameAnimation("SnowBeastFridge_Freezer_Repeat");
		});
	
	Renderer->AnimationBindTime("SnowBeastFridge_Freezer_Repeat", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (false == IsBatOpen)
			{
				Renderer->ChangeFrameAnimation("SnowBeastFridge_Freezer_Outro");
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
			IceTime = 0.15f;
			--IceBatCount;

			float BatRandomMove = GameEngineRandom::MainRandom.RandomFloat(100.0f, 500.0f);
			// 배트 생성
			MortimerFreezeIceBat* BPtr = GetLevel()->CreateActor<MortimerFreezeIceBat>(OBJECTORDER::Boss);
			if (MFBossDIR::LEFT == CurMFDir)
			{
				BPtr->SetMovePos(GetTransform().GetLocalPosition() + float4{ -50.0f,480,0 }, GetTransform().GetLocalPosition() + float4{ -BatRandomMove, 1000 });
			}
			if (MFBossDIR::RIGHT== CurMFDir)
			{
				BPtr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 50.0f,480,0 }, GetTransform().GetLocalPosition() + float4{ BatRandomMove, 1000 });
			}
			BPtr->SetColorType(static_cast<ColorType>(GameEngineRandom::MainRandom.RandomInt(0, 2)));
			BPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,450,0 });
			BPtr->SetReAppearTime(GameEngineRandom::MainRandom.RandomFloat(2.0f, 5.0f) * (4 - IceBatCount));
			
			if (0 == IceBatCount)
			{
				IceBatCount = -1;
				IsBatOpen = false;
			}
			return;
		}

		if (true == IsShoot)
		{
			IceTime = 1.3f;
			//--IceCubeCount;
			// 큐브 생성
			MortimerFreezeIceCube* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCube>(OBJECTORDER::Boss);
			Ptr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 0,300,0 }, MsChalice::Chalice->GetTransform().GetLocalPosition());
			Ptr->SetSizeType(static_cast<SizeType>(GameEngineRandom::MainRandom.RandomInt(0, 1)));
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,300,0 });
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
	PrevState = "Smash";
	Renderer->ChangeFrameAnimation("SnowBeastSmash");
	
	Renderer->AnimationBindEnd("SnowBeastSmash", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeastSmashRepeat");
		});

	Renderer->AnimationBindEnd("SnowBeastSmashRepeat", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == SmashRepeatCount)
			{
				Renderer->ChangeFrameAnimation("SnowBeastSmashOutro");
			}

			SmashRepeatCount -= 1;
		});

	Renderer->AnimationBindEnd("SnowBeastSmashOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager2.ChangeState("MF2Idle");
		});

	// 스매시 애니메이션바인드엔드에 BladeTime 시간설정 + BladeCount 4 설정, StateManager2.ChangeState("MF2Idle");
	BladeTime = 1.0f;
	BladeCount = 4;
	SmashRepeatCount = 3;
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
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() - float4{ 330.0f + (250.0f * (3 - BladeCount)),-45,0});
		}
		if (MFBossDIR::RIGHT == CurMFDir)
		{
			MortimerFreezeBlade* Ptr = GetLevel()->CreateActor<MortimerFreezeBlade>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 340.0f + (250.0f * (3 - BladeCount)),45,0});
		}
	}
}

void MortimerFreezeBoss::Phase2to3Start(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFPhase3Transition0");

	Renderer->AnimationBindEnd("MFPhase3Transition0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("MFPhase3Transition1");
			IsPlatformOn = true;
		});

	Renderer->AnimationBindEnd("MFPhase3Transition1", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == Phase3TransitionMotionCount)
			{
				Renderer->ChangeFrameAnimation("MFPhase3Transition2");
			}

			--Phase3TransitionMotionCount;
		});

	Renderer->AnimationBindEnd("MFPhase3Transition2", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			//Phase3TransitionMotionCount = 5;
			Renderer->ChangeFrameAnimation("MFPhase3Transition3");
		});

	Renderer->AnimationBindEnd("MFPhase3Transition3", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			//if (0 == Phase3TransitionMotionCount)
			{
				Renderer->ChangeFrameAnimation("MFPhase3Transition_Legs");
				
				// 터지는 효과
				EffectRenderer00->ChangeFrameAnimation("SnowBeast_Death_VFX_Front");
				EffectRenderer00->SetPivot(PIVOTMODE::CENTER);
				EffectRenderer00->On();

				// 얼음결정 올라가는 모션
				SubRenderer00->GetTransform().SetLocalPosition(float4::ZERO);
				SubRenderer00->ChangeFrameAnimation("SnowFlake_Ph2_ShootUp");
				SubRenderer00->On();
			}

			//--Phase3TransitionMotionCount;
		});

	Renderer->AnimationBindEnd("MFPhase3Transition_Legs", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == LegCount)
			{
				Renderer->ChangeFrameAnimation("MFPhase3Transition_LegsMove");
				IsLegMove = true;
			}

			--LegCount;
		});

	EffectRenderer00->AnimationBindEnd("SnowBeast_Death_VFX_Front", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EffectRenderer00->Off();
		});
}

void MortimerFreezeBoss::Phase2to3Update(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsLegMove)
	{
		if (MFBossDIR::LEFT == CurMFDir)
		{
			GetTransform().SetWorldLeftMove(800.0f, _DeltaTime);
		}
		else
		{
			GetTransform().SetWorldRightMove(800.0f, _DeltaTime);
		}
	}

	if (true == SubRenderer00->IsUpdate())
	{
		SubRenderer00->GetTransform().SetWorldUpMove(Speed * 5, _DeltaTime);
	}

	if (true == GetLevel<MortimerFreezeLevel>()->GetIsMove())
	{
		GetTransform().SetWorldDownMove(500.0f, _DeltaTime);
	}

	if (true == IsPlatformOn)
	{
		PlatformTime -= _DeltaTime;

		if (0.0f >= PlatformTime)
		{
			--PlatformCount;

			// MortimerFreezeLevel의 SetPh3MoveValue 작업 필요
			if (4 == PlatformCount)
			{
				MortimerFreezeSnowPlatform* Ptr = GetLevel()->CreateActor<MortimerFreezeSnowPlatform>(OBJECTORDER::SnowPlatform);
				Ptr->SetPlatformType(PlatformType::Intro);
				Ptr->GetTransform().SetLocalPosition({ 890.0f, -735.0f, -1.0f });
				Ptr->GetLevel<MortimerFreezeLevel>()->SetPh3MoveValue(&Ptr->GetTransform(), { 0,-700,0 });

				PlatformTime = 0.3f;
			}
			if (3 == PlatformCount)
			{
				MortimerFreezeSnowPlatform* Ptr = GetLevel()->CreateActor<MortimerFreezeSnowPlatform>(OBJECTORDER::SnowPlatform);
				Ptr->SetPlatformType(PlatformType::Intro);
				Ptr->GetTransform().SetLocalPosition({ 700.0f, -600.0f, -1.0f });
				Ptr->GetLevel<MortimerFreezeLevel>()->SetPh3MoveValue( &Ptr->GetTransform(), {0,-700,0});
				Ptr->Index = 2;

				PlatformTime = 0.3f;
			}
			if (2 == PlatformCount)
			{
				MortimerFreezeSnowPlatform* Ptr = GetLevel()->CreateActor<MortimerFreezeSnowPlatform>(OBJECTORDER::SnowPlatform);
				Ptr->SetPlatformType(PlatformType::Intro);
				Ptr->GetTransform().SetLocalPosition({ 890.0f, -465.0f, -1.0f });
				Ptr->GetLevel<MortimerFreezeLevel>()->SetPh3MoveValue(&Ptr->GetTransform(), { 0,-700,0 });
				Ptr->Index = 2;

				PlatformTime = 0.3f;
			}
			if (1 == PlatformCount)
			{
				MortimerFreezeSnowPlatform* Ptr = GetLevel()->CreateActor<MortimerFreezeSnowPlatform>(OBJECTORDER::SnowPlatform);
				Ptr->SetPlatformType(PlatformType::Intro);
				Ptr->GetTransform().SetLocalPosition({ 700.0f, -330.0f, -1.0f });
				Ptr->GetLevel<MortimerFreezeLevel>()->SetPh3MoveValue(&Ptr->GetTransform(), { 0,-700,0 });
				Ptr->Index = 2;

				PlatformTime = 0.3f;
			}
			if (0 == PlatformCount)
			{
				MortimerFreezeSnowPlatform* Ptr = GetLevel()->CreateActor<MortimerFreezeSnowPlatform>(OBJECTORDER::SnowPlatform);
				Ptr->SetPlatformType(PlatformType::Intro);
				Ptr->GetTransform().SetLocalPosition({ 890.0f, -195.0f, -1.0f });
				Ptr->GetLevel<MortimerFreezeLevel>()->SetPh3MoveValue(&Ptr->GetTransform(), { 0,-700,0 });

				PlatformTime = 0.3f;
			}
		}
	}
}
