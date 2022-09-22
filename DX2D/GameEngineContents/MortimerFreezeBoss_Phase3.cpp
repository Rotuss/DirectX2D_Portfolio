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

	StateManager3.CreateStateMember("MF3Idle", std::bind(&MortimerFreezeBoss::P3IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3IdleStart, this, std::placeholders::_1));

	StateManager3.CreateStateMember("Swap", std::bind(&MortimerFreezeBoss::P3SwapUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P3SwapStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("Eye", std::bind(&MortimerFreezeBoss::AttackEyeUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackEyeStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("IceCream", std::bind(&MortimerFreezeBoss::AttackIceCreamUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackIceCreamStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("Split", std::bind(&MortimerFreezeBoss::AttackSplitUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackSplitStart, this, std::placeholders::_1));
	StateManager3.CreateStateMember("KnockOut", std::bind(&MortimerFreezeBoss::Phase3KnockOutUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase3KnockOutStart, this, std::placeholders::_1));

	StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::Phase3Update(float _DeltaTime, const StateInfo& _Info)
{
	StateManager3.Update(_DeltaTime);
}

void MortimerFreezeBoss::P3IdleStart(const StateInfo& _Info)
{
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
	// 2 == b 老 锭 IsReverse = !IsReverse;
	// 3 == c 老 锭 老何 IsReverse = !IsReverse;
}

void MortimerFreezeBoss::AttackEyeStart(const StateInfo& _Info)
{
	--SwapCount;
	
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

	//StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::AttackEyeUpdate(float _DeltaTime, const StateInfo& _Info)
{
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