#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "MortimerFreezeEye.h"
#include "MortimerFreezeIceCream.h"
#include "MortimerFreezeBucket.h"
#include <GameEngineBase/GameEngineRandom.h>

void MortimerFreezeBoss::Phase3Start(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsKey("Num1_Peashot"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1_Eye", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Num2_IceCream", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Num3_Split", VK_NUMPAD3);
	}

	// 수치 조정 필요
	GetTransform().SetLocalPosition(float4{ 800.0f, -300.0f, -1.0f });

	StateManager3.CreateStateMember("MF3Intro", std::bind(&MortimerFreezeBoss::P3IntroUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3IntroStart, this, std::placeholders::_1), std::bind(&MortimerFreezeBoss::P3IntroEnd, this, std::placeholders::_1));

	StateManager3.CreateStateMember("MF3Idle", std::bind(&MortimerFreezeBoss::P3IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3IdleStart, this, std::placeholders::_1));

	StateManager3.CreateStateMember("Swap", std::bind(&MortimerFreezeBoss::P3SwapUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3SwapStart, this, std::placeholders::_1));
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
		GetTransform().SetWorldDownMove(150.0f, _DeltaTime);
	}

	if (true == IsPh3XMove)
	{
		if (MFBossDIR::LEFT == CurMFDir)
		{
			if (300 >= GetTransform().GetLocalPosition().x)
			{
				GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
				return;
			}
			
			GetTransform().SetWorldLeftMove(500.0f, _DeltaTime);
		}
		else
		{
			if (1300 <= GetTransform().GetLocalPosition().x)
			{
				GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
				return;
			}

			GetTransform().SetWorldRightMove(500.0f, _DeltaTime);
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
			IceCreamTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f);
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
	StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::P3SwapUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 2 == b 일 때 IsReverse = !IsReverse;
	// 3 == c 일 때 일부 IsReverse = !IsReverse;
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
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				}
				if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::LeftBot);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				}

				if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::RightTop);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				}
				if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse)
				{
					Ptr->SetEyePosition(EyePos::RightBot);
					Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
					Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				}

				// 임시 확인용으로 강제 Renderer 변경(일정 시간 이후 Renderer 바뀌게 해야함)
				Renderer->ChangeFrameAnimation("EyeBall_BodyBacker3");
			}
		});

	Renderer->AnimationBindEnd("EyeBall_BodyBacker3", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EyeRepeatCount = 4;
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

	IceCreamRandom = GameEngineRandom::MainRandom.RandomInt(0,2);

	//StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::AttackIceCreamUpdate(float _DeltaTime, const StateInfo& _Info)
{
	IceCreamAppearTime += _DeltaTime;

	if (0 >= IceCreamCount)
	{
		return;
	}

	if(0.8f <= IceCreamAppearTime)
	{
		if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
		{
			--IceCreamCount;

			MortimerFreezeIceCream* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
			if (3 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(3.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(2.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.2f);
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
				Ptr->SetIceCreamMoveTime(3.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(2.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.2f);
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
				Ptr->SetIceCreamMoveTime(3.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num0);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(2.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.2f);
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
				Ptr->SetIceCreamMoveTime(3.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num3);
			}
			if (2 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(2.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num2);
			}
			if (1 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(1.0f);
				Ptr->SetPosType(static_cast<PosType>(IceCreamRandom));
				Ptr->SetNumType(NumType::Num1);
			}
			if (0 == IceCreamCount)
			{
				Ptr->SetIceCreamMoveTime(0.2f);
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

	//StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::AttackSplitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	BucketAppearTime += _DeltaTime;

	/*if (0 >= BucketCount)
	{
		StateManager3.ChangeState("MF3Idle");
	}*/

	if (2.0f <= BucketAppearTime)
	{
		if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
		{
			--BucketCount;

			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
			}

			BucketAppearTime = 0.0f;
		}
		if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
		{
			--BucketCount;

			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				Ptr->BucketSetting(BucketDirType::Left, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			}

			BucketAppearTime = 0.0f;
		}

		if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
		{
			--BucketCount;

			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
			}

			BucketAppearTime = 0.0f;
		}
		if (MFBossDIR::RIGHT == CurMFDir && true == IsReverse)
		{
			--BucketCount;

			MortimerFreezeBucket* Ptr = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
			if (2 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::BOT);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			}
			if (1 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::MID);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			}
			if (0 == BucketCount)
			{
				Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
				Ptr->BucketSetting(BucketDirType::Right, BucketMoveType::TOP);
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
			}

			BucketAppearTime = 0.0f;
		}
	}
}

void MortimerFreezeBoss::Phase3KnockOutStart(const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase3KnockOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
}