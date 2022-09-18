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
	StateManager3.CreateStateMember("IceCream", std::bind(&MortimerFreezeBoss::AttackCreamUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackIceCreamStart, this, std::placeholders::_1));
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
	// 2 == b 일 때 IsReverse = !IsReverse;
	// 3 == c 일 때 일부 IsReverse = !IsReverse;
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
		Ptr->SetEyePosition(EyePos::LeftTop);
		Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
	}

	if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
	{
		Ptr->SetEyePosition(EyePos::LeftTop);
		Ptr->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
	}
	if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
	{
		Ptr->SetEyePosition(EyePos::LeftTop);
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
	
	{
		MortimerFreezeIceCream* Ptr1 = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
		MortimerFreezeIceCream* Ptr2 = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
		MortimerFreezeIceCream* Ptr3 = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);
		MortimerFreezeIceCream* Ptr4 = GetLevel()->CreateActor<MortimerFreezeIceCream>(OBJECTORDER::Boss);

		// Ptr1~4 모두 위치 재조정 필요
		Ptr1->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr2->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr3->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr4->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr4->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
	}

	//StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::AttackCreamUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MortimerFreezeBoss::AttackSplitStart(const StateInfo& _Info)
{
	--SwapCount;
	
	MortimerFreezeBucket* Ptr1 = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
	MortimerFreezeBucket* Ptr2 = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);
	MortimerFreezeBucket* Ptr3 = GetLevel()->CreateActor<MortimerFreezeBucket>(OBJECTORDER::Boss);

	if (MFBossDIR::LEFT == CurMFDir && false == IsReverse)
	{
		Ptr1->BucketSetting(BucketDirType::Left, BucketMoveType::TOP);
		Ptr1->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr2->BucketSetting(BucketDirType::Left, BucketMoveType::MID);
		Ptr2->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr3->BucketSetting(BucketDirType::Left, BucketMoveType::BOT);
		Ptr3->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
	}
	if (MFBossDIR::LEFT == CurMFDir && true == IsReverse)
	{
		Ptr1->BucketSetting(BucketDirType::Left, BucketMoveType::TOP);
		Ptr1->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });

		Ptr2->BucketSetting(BucketDirType::Left, BucketMoveType::MID);
		Ptr2->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });

		Ptr3->BucketSetting(BucketDirType::Left, BucketMoveType::BOT);
		Ptr3->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
	}

	if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
	{
		Ptr1->BucketSetting(BucketDirType::Right, BucketMoveType::TOP);
		Ptr1->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr2->BucketSetting(BucketDirType::Right, BucketMoveType::MID);
		Ptr2->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });

		Ptr3->BucketSetting(BucketDirType::Right, BucketMoveType::BOT);
		Ptr3->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
		Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,100,0 });
	}
	if (MFBossDIR::RIGHT == CurMFDir && false == IsReverse)
	{
		Ptr1->BucketSetting(BucketDirType::Right, BucketMoveType::TOP);
		Ptr1->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });

		Ptr2->BucketSetting(BucketDirType::Right, BucketMoveType::MID);
		Ptr2->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });

		Ptr3->BucketSetting(BucketDirType::Right, BucketMoveType::BOT);
		Ptr3->SetStartPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
		Ptr3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0,-100,0 });
	}

	//StateManager3.ChangeState("MF3Idle");
}

void MortimerFreezeBoss::AttackSplitUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase3KnockOutStart(const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase3KnockOutUpdate(float _DeltaTime, const StateInfo& _Info)
{
}