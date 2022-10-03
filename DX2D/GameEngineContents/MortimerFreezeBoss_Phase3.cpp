#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "MortimerFreezeEye.h"
#include "MortimerFreezeIceCream.h"
#include "MortimerFreezeBucket.h"
#include "KnockOut.h"
#include <GameEngineBase/GameEngineRandom.h>

void MortimerFreezeBoss::Phase3Start(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsKey("Num1_Peashot"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1_Eye", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Num2_IceCream", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Num3_Split", VK_NUMPAD3);
	}

	HP = 1;
	PrevState = "";
	// 수치 조정 필요
	Renderer->SetPivot(PIVOTMODE::CENTER);
	Collision->GetTransform().SetLocalScale(float4{ 300.0f,600.0f,0.0f });
	Collision->GetTransform().SetLocalPosition(float4{ 0.0f,0.0f,0.0f });
	Collision->Off();
	GetTransform().SetLocalPosition(float4{ 800.0f, -200.0f, 250.0f });

	StateManager3.CreateStateMember("MF3Intro", std::bind(&MortimerFreezeBoss::P3IntroUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3IntroStart, this, std::placeholders::_1), std::bind(&MortimerFreezeBoss::P3IntroEnd, this, std::placeholders::_1));

	StateManager3.CreateStateMember("MF3Idle", std::bind(&MortimerFreezeBoss::P3IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3IdleStart, this, std::placeholders::_1));

	StateManager3.CreateStateMember("Swap", std::bind(&MortimerFreezeBoss::P3SwapUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3SwapStart, this, std::placeholders::_1), std::bind(&MortimerFreezeBoss::P3SwapEnd, this, std::placeholders::_1));
	StateManager3.CreateStateMember("Eye", std::bind(&MortimerFreezeBoss::AttackEyeUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackEyeStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("IceCream", std::bind(&MortimerFreezeBoss::AttackIceCreamUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackIceCreamStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("Split", std::bind(&MortimerFreezeBoss::AttackSplitUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackSplitStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("KnockOut", std::bind(&MortimerFreezeBoss::Phase3KnockOutUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase3KnockOutStart, this, std::placeholders::_1));

	StateManager3.ChangeState("MF3Intro");
}

void MortimerFreezeBoss::Phase3Update(float _DeltaTime, const StateInfo& _Info)
{
	StateManager3.Update(_DeltaTime);
}

void MortimerFreezeBoss::P3IntroStart(const StateInfo& _Info)
{
	int DirRandom = GameEngineRandom::MainRandom.RandomInt(0, 1);
	IsPh3DownMove = true;

	Renderer->ChangeFrameAnimation("MF3Intro");

	Renderer->AnimationBindFrame("MF3Intro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (20 == _Info.CurFrame)
			{
				IsPh3DownMove = false;
			}

			if (42 == _Info.CurFrame)
			{
				if (0 == DirRandom)
				{
					CurMFDir = MFBossDIR::LEFT;
					Renderer->GetTransform().PixLocalNegativeX();
					IsPh3XMove = true;
				}
				if (1 == DirRandom)
				{
					CurMFDir = MFBossDIR::RIGHT;
					Renderer->GetTransform().PixLocalPositiveX();
					IsPh3XMove = true;
				}
			}
		});

	Renderer->AnimationBindEnd("MF3Intro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("MF3IntroMove");
		});

	Renderer->AnimationBindEnd("MF3IntroMove", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager3.ChangeState("MF3Idle");
		});
}

void MortimerFreezeBoss::P3IntroUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsPh3DownMove)
	{
		GetTransform().SetWorldDownMove(80.0f, _DeltaTime);
	}

	if (true == IsPh3XMove)
	{
		if (MFBossDIR::LEFT == CurMFDir)
		{
			if (280 >= GetTransform().GetLocalPosition().x)
			{
				GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
				return;
			}
			
			GetTransform().SetWorldLeftMove(1000.0f, _DeltaTime);
		}
		else
		{
			if (1380 <= GetTransform().GetLocalPosition().x)
			{
				GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
				return;
			}

			GetTransform().SetWorldRightMove(1000.0f, _DeltaTime);
		}
	}
}

void MortimerFreezeBoss::P3IntroEnd(const StateInfo& _Info)
{
	if (MFBossDIR::LEFT == CurMFDir)
	{
		CurMFDir = MFBossDIR::RIGHT;
	}
	else
	{
		CurMFDir = MFBossDIR::LEFT;
	}

	{
		GameEngineActor* TmpActor = GetLevel()->CreateActor<GameEngineActor>();
		TmpActor->GetTransform().SetWorldScale({ 1,1,1 });
		TmpActor->GetTransform().SetWorldPosition({ 820, -680, 0 });
		Phase3BotCollision = TmpActor->CreateComponent<GameEngineCollision>();
		Phase3BotCollision->GetTransform().SetLocalScale({ 1300,50,1 });
		Phase3BotCollision->ChangeOrder(OBJECTORDER::Phase3Bot);
	}

	Collision->On();
}

void MortimerFreezeBoss::P3IdleStart(const StateInfo& _Info)
{
	if ("" == PrevState || "Swap" == PrevState)
	{
		Renderer->ChangeFrameAnimation("MF3Idle");
	}

	Renderer->ChangeFrameAnimation("Attack_After_MF3Idle");

	Renderer->AnimationBindEnd("Attack_After_MF3Idle", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("MF3Idle");
		});
}

void MortimerFreezeBoss::P3IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0 == HP)
	{
		StateManager3.ChangeState("KnockOut");
		return;
	}
	
	if ("IceCream" == PrevState && 0 <= IceCreamTime)
	{
		IceCreamTime -= _DeltaTime;
		if (0 >= IceCreamTime)
		{
			PrevState = "";
		}
		return;
	}

	if (0 == SwapCount)
	{
		SwapCount = GameEngineRandom::MainRandom.RandomInt(1, 2);
		StateManager3.ChangeState("Swap");
		return;
	}
	
	float EyeRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float IceCreamRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float SplitRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);

	{
		if (0.8f >= EyeRandomPer && 0 >= EyeTime)
		{
			if (PrevSkill == 1)
			{
				return;
			}
			EyeTime = GameEngineRandom::MainRandom.RandomFloat(0.2f, 1.0f);
			StateManager3.ChangeState("Eye");
			PrevSkill = 1;
			return;
		}

		if (0 >= EyeTime)
		{
			EyeTime = GameEngineRandom::MainRandom.RandomFloat(0.2f, 0.5f);
		}
	}

	{
		if (0.8f >= IceCreamRandomPer && 0 >= IceCreamTime)
		{
			if (PrevSkill == 2)
			{
				return;
			}
			IceCreamTime = 1.2f;
			StateManager3.ChangeState("IceCream");
			PrevSkill = 2;
			return;
		}

		if (0 >= IceCreamTime)
		{
			IceCreamTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 0.8f);
		}
	}

	{
		if (0.8f >= SplitRandomPer && 0 >= SplitTime)
		{
			if (PrevSkill == 3)
			{
				return;
			}
			SplitTime = GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f);
			StateManager3.ChangeState("Split");
			PrevSkill = 3;
			return;
		}

		if (0 >= SplitTime)
		{
			SplitTime = GameEngineRandom::MainRandom.RandomFloat(0.8f, 0.9f);
		}
	}

	EyeTime -= _DeltaTime;
	IceCreamTime -= _DeltaTime;
	SplitTime -= _DeltaTime;
}

void MortimerFreezeBoss::P3SwapStart(const StateInfo& _Info)
{
	Collision->Off();
	PrevState = "Swap";
	int RandomIntNum = GameEngineRandom::MainRandom.RandomInt(1, 3);

	if (1 == RandomIntNum)
	{
		IsSwapA = true;
		Renderer->ChangeFrameAnimation("SnowFlake_SwapA");
	}
	if (2 == RandomIntNum)
	{
		Renderer->ChangeFrameAnimation("SnowFlake_SwapB");
		IsReverse = !IsReverse;
	}
	if (3 == RandomIntNum)
	{
		Renderer->GetTransform().SetLocalPosition(float4{ 0.0f,0.0f,-1000.0f });
		Renderer->ChangeFrameAnimation("SnowFlake_SwapC");
	}
	
	Renderer->AnimationBindEnd("SnowFlake_SwapAR", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				CurMFDir = MFBossDIR::RIGHT;
			}
			else if (MFBossDIR::RIGHT == CurMFDir)
			{
				CurMFDir = MFBossDIR::LEFT;
			}
			
			StateManager3.ChangeState("MF3Idle");
		});

	Renderer->AnimationBindEnd("SnowFlake_SwapB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				Renderer->GetTransform().PixLocalNegativeX();
				CurMFDir = MFBossDIR::RIGHT;
			}
			else if (MFBossDIR::RIGHT == CurMFDir)
			{
				Renderer->GetTransform().PixLocalPositiveX();
				CurMFDir = MFBossDIR::LEFT;
			}
			
			if (true == IsReverse)
			{
				Renderer->GetTransform().PixLocalNegativeY();
			}
			else if(false == IsReverse)
			{
				Renderer->GetTransform().PixLocalPositiveY();
			}

			StateManager3.ChangeState("MF3Idle");
		});

	Renderer->AnimationBindEnd("SnowFlake_SwapC", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_SwapCLast");
				Renderer->GetTransform().PixLocalNegativeX();
			}
			else if (MFBossDIR::RIGHT == CurMFDir)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_SwapCLast");
				Renderer->GetTransform().PixLocalPositiveX();
			}
			Renderer->GetTransform().SetLocalPosition(float4{ 0.0f,0.0f,0.0f });
		});

	Renderer->AnimationBindEnd("SnowFlake_SwapCLast", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				CurMFDir = MFBossDIR::RIGHT;
			}
			else if (MFBossDIR::RIGHT == CurMFDir)
			{
				CurMFDir = MFBossDIR::LEFT;
			}
			
			StateManager3.ChangeState("MF3Idle");
		});
}

void MortimerFreezeBoss::P3SwapUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;
	
	if (MFBossDIR::LEFT == CurMFDir)
	{
		if (280 >= MFCurXPos)
		{
			GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
			return;
		}

		if (800 >= MFCurXPos)
		{
			if (true == IsSwapA)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_SwapAR");
				Renderer->GetTransform().PixLocalNegativeX();
				IsSwapA = false;
			}
		}

		GetTransform().SetWorldLeftMove(1000.0f, _DeltaTime);
	}
	else
	{
		if (1380 <= MFCurXPos)
		{
			GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
			return;
		}

		if (800 <= MFCurXPos)
		{
			if (true == IsSwapA)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_SwapAR");
				Renderer->GetTransform().PixLocalPositiveX();
				IsSwapA = false;
			}
		}

		GetTransform().SetWorldRightMove(1000.0f, _DeltaTime);
	}
	// 2 == b 일 때 IsReverse = !IsReverse;
	// 3 == c 일 때 일부 IsReverse = !IsReverse;
}

void MortimerFreezeBoss::P3SwapEnd(const StateInfo& _Info)
{
	Collision->On();
}

void MortimerFreezeBoss::AttackEyeStart(const StateInfo& _Info)
{
	--SwapCount;
	
	// 일부 애니메이션에서 Count 수치 조정 필요
	EyeRepeatCount = 4;

	Renderer->ChangeFrameAnimation("EyeBall_BodyBacker0");

	Renderer->AnimationBindEnd("EyeBall_BodyBacker0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("EyeBall_BodyBacker1");
		});

	Renderer->AnimationBindFrame("EyeBall_BodyBacker1", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == EyeRepeatCount)
			{
				if (1 == _Info.CurFrame)
				{
					Renderer->ChangeFrameAnimation("EyeBall_BodyBacker2");
				}
			}
		});

	Renderer->AnimationBindEnd("EyeBall_BodyBacker1", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			--EyeRepeatCount;
		});

	Renderer->AnimationBindFrame("EyeBall_BodyBacker2", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (1 == _Info.CurFrame)
			{
				MortimerFreezeEye* Ptr = GetLevel()->CreateActor<MortimerFreezeEye>(OBJECTORDER::Boss);

				if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::LeftTop);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -300,100,-680 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -300,100,-680 });
				}
				if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::LeftBot);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -300,-100,-680 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -300,-100,-680 });
				}

				if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::RightTop);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 300,100,-680 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 300,100,-680 });
				}
				if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::RightBot);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 300,-100,-680 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 300,-100,-680 });
				}
				
				// 임시 확인용으로 강제 Renderer 변경(일정 시간 이후 Renderer 바뀌게 해야함)
				Renderer->ChangeFrameAnimation("EyeBall_BodyBacker3");
			}
		});

	Renderer->AnimationBindEnd("EyeBall_BodyBacker3", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EyeRepeatCount = 2;
			Renderer->ChangeFrameAnimation("EyeBall_BodyBacker4");
		});

	Renderer->AnimationBindFrame("EyeBall_BodyBacker4", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == EyeRepeatCount)
			{
				if (6 == _Info.CurFrame)
				{
					Renderer->ChangeFrameAnimation("EyeBall_BodyBacker5");
				}
			}
		});

	Renderer->AnimationBindEnd("EyeBall_BodyBacker4", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			--EyeRepeatCount;
		});

	Renderer->AnimationBindEnd("EyeBall_BodyBacker5", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			// 6에서 7 전환 테스트용
			EyeRepeatCount = 4;
			
			Renderer->ChangeFrameAnimation("EyeBall_BodyBacker6");
		});

	// 6에서 7 전환 테스트용
	Renderer->AnimationBindEnd("EyeBall_BodyBacker6", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == EyeRepeatCount)
			{
				Renderer->ChangeFrameAnimation("EyeBall_BodyBacker7");
			}

			--EyeRepeatCount;
		});

	Renderer->AnimationBindEnd("EyeBall_BodyBacker7", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager3.ChangeState("MF3Idle");
		});
}

void MortimerFreezeBoss::AttackEyeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// EyeBall_BodyBacker6에서 Eye와 x축이 일치할 때 EyeBall_BodyBacker7
}

void MortimerFreezeBoss::AttackIceCreamStart(const StateInfo& _Info)
{
	--SwapCount;
	IceCreamAppearTime = 0.0f;
	IceCreamCount = 4;
	IsIceCreamPatternEnd = false;
	PrevState = "IceCream";

	IceCreamRandom = GameEngineRandom::MainRandom.RandomInt(0,2);

	Renderer->ChangeFrameAnimation("SnowFlake_IceCreamBacker0");

	Renderer->AnimationBindEnd("SnowFlake_IceCreamBacker0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
			{
				SubRenderer00->ChangeFrameAnimation("IceCream_Ghost", true);
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->GetTransform().PixLocalPositiveY(); 
				SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
				SubRenderer00->GetTransform().SetLocalPosition(float4{ -520.0f,-50.0f,-500.0f });
				SubRenderer00->On();
			}
			if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
			{
				SubRenderer00->ChangeFrameAnimation("IceCream_Ghost", true);
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->GetTransform().PixLocalNegativeY();
				SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
				SubRenderer00->GetTransform().SetLocalPosition(float4{ -520.0f,50.0f,-500.0f });
				SubRenderer00->On();
			}
			if (MFBossDIR::RIGHT== CurMFDir && false == IsReverse)
			{
				SubRenderer00->ChangeFrameAnimation("IceCream_Ghost", true);
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->GetTransform().PixLocalPositiveY();
				SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 520.0f,-50.0f,-500.0f });
				SubRenderer00->On();
			}
			if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse)
			{
				SubRenderer00->ChangeFrameAnimation("IceCream_Ghost", true);
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->GetTransform().PixLocalNegativeY();
				SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 520.0f,-50.0f,-500.0f });
				SubRenderer00->On();
			}
			Renderer->ChangeFrameAnimation("SnowFlake_IceCreamBacker1");
		});

	Renderer->AnimationBindEnd("SnowFlake_IceCreamBackerR0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager3.ChangeState("MF3Idle");
		});

	Renderer->AnimationBindEnd("SnowFlake_IceCreamBackerR1", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (true == IsIceCreamPatternEnd)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_IceCreamBackerR0");
			}
		});

	SubRenderer00->AnimationBindFrame("IceCream_Ghost", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (10 == _Info.CurFrame)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_IceCreamBackerR1");
			}

			if (19 == _Info.CurFrame)
			{
				Renderer->ChangeFrameAnimation("SnowFlake_IceCreamBacker1");
			}

			if (28 == _Info.CurFrame)
			{
				IsIceCreamPatternEnd = true;
				Renderer->ChangeFrameAnimation("SnowFlake_IceCreamBackerR1");
			}
		});

	SubRenderer00->AnimationBindEnd("IceCream_Ghost", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->Off();
		});
}

void MortimerFreezeBoss::AttackIceCreamUpdate(float _DeltaTime, const StateInfo& _Info)
{
	IceCreamAppearTime += _DeltaTime;

	if (0 >= IceCreamCount)
	{
		return;
	}

	if(0.5f <= IceCreamAppearTime)
	{
		if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
		{
			--IceCreamCount;

			MortimerFreezeIceCream* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
			if (3 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.8f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.5f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}

			IceCreamAppearTime = 0.0f;
		}
		if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
		{
			--IceCreamCount;

			MortimerFreezeIceCream* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
			if (3 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.8f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.5f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}

			IceCreamAppearTime = 0.0f;
		}
		
		if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
		{
			--IceCreamCount;

			MortimerFreezeIceCream* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
			if (3 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.8f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.5f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}

			IceCreamAppearTime = 0.0f;
		}
		if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse)
		{
			--IceCreamCount;

			MortimerFreezeIceCream* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
			if (3 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.8f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.5f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.3f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}

			IceCreamAppearTime = 0.0f;
		}
	}
}

void MortimerFreezeBoss::AttackSplitStart(const StateInfo& _Info)
{
	--SwapCount;
	BucketAppearTime = 0.0f;
	BucketCount = 3;
	IsBucketMove = false;

	Renderer->ChangeFrameAnimation("SplitShot_SnowFlakeBacker0");

	Renderer->AnimationBindFrame("SplitShot_SnowFlakeBacker0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (9 == _Info.CurFrame)
			{
				if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
				{
					SubRenderer00->ChangeFrameAnimation("SplitShot_Arms0", true);
					SubRenderer00->GetTransform().PixLocalPositiveX();
					SubRenderer00->GetTransform().PixLocalPositiveY();
					SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
					SubRenderer00->GetTransform().SetLocalPosition(float4{ -185,-150,-550 });
					SubRenderer00->On();
				}
				if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
				{
					SubRenderer00->ChangeFrameAnimation("SplitShot_Arms0", true);
					SubRenderer00->GetTransform().PixLocalPositiveX();
					SubRenderer00->GetTransform().PixLocalNegativeY();
					SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
					SubRenderer00->GetTransform().SetLocalPosition(float4{ -185,150,-550 });
					SubRenderer00->On();
				}
				if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
				{
					SubRenderer00->ChangeFrameAnimation("SplitShot_Arms0", true);
					SubRenderer00->GetTransform().PixLocalNegativeX();
					SubRenderer00->GetTransform().PixLocalPositiveY();
					SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
					SubRenderer00->GetTransform().SetLocalPosition(float4{ 185,-150,-550 });
					SubRenderer00->On();
				}
				if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse)
				{
					SubRenderer00->ChangeFrameAnimation("SplitShot_Arms0", true);
					SubRenderer00->GetTransform().PixLocalNegativeX();
					SubRenderer00->GetTransform().PixLocalNegativeY();
					SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
					SubRenderer00->GetTransform().SetLocalPosition(float4{ 185,150,-550 });
					SubRenderer00->On();
				}
			}
		});

	Renderer->AnimationBindEnd("SplitShot_SnowFlakeBacker0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SplitShot_SnowFlakeBacker1");
		});

	Renderer->AnimationBindTime("SplitShot_SnowFlakeBacker1", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (true == IsBucketMove)
			{
				IsBucketMove = false;
				Renderer->ChangeFrameAnimation("SplitShot_SnowFlakeBacker2"); // 양동이 떠나면 SplitShot_SnowFlakeBacker3
				SubRenderer00->ChangeFrameAnimation("SplitShot_Arms2");
			}
		});

	Renderer->AnimationBindEnd("SplitShot_SnowFlakeBacker2", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 > BucketCount)
			{
				Renderer->ChangeFrameAnimation("SplitShot_SnowFlakeBacker4");
				SubRenderer00->ChangeFrameAnimation("SplitShot_Arms4");
			}
			else
			{
				Renderer->ChangeFrameAnimation("SplitShot_SnowFlakeBacker1");
				SubRenderer00->ChangeFrameAnimation("SplitShot_Arms1");
			}
		});

	Renderer->AnimationBindEnd("SplitShot_SnowFlakeBacker4", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager3.ChangeState("MF3Idle");
		});

	SubRenderer00->AnimationBindEnd("SplitShot_Arms0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->ChangeFrameAnimation("SplitShot_Arms1");
		});

	SubRenderer00->AnimationBindEnd("SplitShot_Arms2", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->ChangeFrameAnimation("SplitShot_Arms3");
		});

	SubRenderer00->AnimationBindEnd("SplitShot_Arms4", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->Off();
		});
}

void MortimerFreezeBoss::AttackSplitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	BucketAppearTime += _DeltaTime;

	if (2.0f <= BucketAppearTime)
	{
		--BucketCount;
		BucketAppearTime = 0.0f;

		if (MFBossDIR::LEFT == CurMFDir && false == IsReverse && 0 <= BucketCount)
		{
			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -180,-130,-560 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -180,-130,-560 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -180,-130,-560 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -180,-130,-560 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -180,-130,-560 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -180,-130,-560 });
			}
		}
		if (MFBossDIR::LEFT == CurMFDir && true == IsReverse && 0 <= BucketCount)
		{
			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -180,130,-560 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -180,130,-560 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -180,130,-560 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -180,130,-560 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ -180,130,-560 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -180,130,-560 });
			}
		}

		if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse && 0 <= BucketCount)
		{
			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 180,-130,-560 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 180,-130,-560 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 180,-130,-560 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 180,-130,-560 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 180,-130,-560 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 180,-130,-560 });
			}
		}
		if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse && 0 <= BucketCount)
		{
			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 180,130,-560 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 180,130,-560 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 180,130,-560 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 180,130,-560 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 180,130,-560 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 180,130,-560 });
			}
		}
	}
}

void MortimerFreezeBoss::Phase3KnockOutStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Ph3Wizard_Death");
	
	if (false == IsReverse)
	{
		SubRenderer00->ChangeFrameAnimation("SnowFlake_Death0");
		SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
		SubRenderer00->On();
	}
	else
	{
		SubRenderer00->ChangeFrameAnimation("SnowFlake_Death_Alt");
		SubRenderer00->SetPivot(PIVOTMODE::CENTER);;
		SubRenderer00->On();
	}
	
	SubRenderer00->AnimationBindFrame("SnowFlake_Death0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (1 == _Info.CurFrame)
			{
				SubRenderer00->CurAnimationPauseOn();
				KnockOut* KO = GetLevel()->CreateActor<KnockOut>();
				KO->GetTransform().SetWorldPosition({ 830.0f,-610.0f,-15.0f });
				KO->GetRenderer()->AnimationBindEnd("KnockOut", [/*&*/=](const FrameAnimation_DESC& _Info)
					{
						SubRenderer00->CurAnimationPauseOff();
						KO->Death();
					});
			}
		});

	SubRenderer00->AnimationBindEnd("SnowFlake_Death0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->ChangeFrameAnimation("SnowFlake_Death1");
		});

	SubRenderer00->AnimationBindFrame("SnowFlake_Death_Alt", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (1 == _Info.CurFrame)
			{
				SubRenderer00->CurAnimationPauseOn();
				KnockOut* KO = GetLevel()->CreateActor<KnockOut>();
				KO->GetRenderer()->AnimationBindEnd("KnockOut", [/*&*/=](const FrameAnimation_DESC& _Info)
					{
						SubRenderer00->CurAnimationPauseOff();
					});
			}
		});

	SubRenderer00->AnimationBindEnd("SnowFlake_Death_Alt", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->ChangeFrameAnimation("SnowFlake_Death1");
		});

	SubRenderer00->AnimationBindFrame("SnowFlake_Death1", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (9 == _Info.CurFrame)
			{
				if (MFBossDIR::LEFT == CurMFDir)
				{
					SubRenderer01->ChangeFrameAnimation("SnowFlake_DeathBacker");
					SubRenderer01->GetTransform().PixLocalPositiveX();
					SubRenderer01->SetPivot(PIVOTMODE::CENTER);;
					SubRenderer01->GetTransform().SetLocalPosition(float4{ 0,0,-0.5f });
					SubRenderer01->On();
				}
				else
				{
					SubRenderer01->ChangeFrameAnimation("SnowFlake_DeathBacker");
					SubRenderer01->GetTransform().PixLocalNegativeX();
					SubRenderer01->SetPivot(PIVOTMODE::CENTER);;
					SubRenderer01->GetTransform().SetLocalPosition(float4{ 0,0,-0.5f });
					SubRenderer01->On();
				}
			}
		});
}

void MortimerFreezeBoss::Phase3KnockOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
}