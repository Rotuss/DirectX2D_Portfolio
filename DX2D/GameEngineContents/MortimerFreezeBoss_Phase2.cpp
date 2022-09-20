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
	Renderer->ChangeFrameAnimation("SnowBeast_DashPreAttack");

	Renderer->AnimationBindEnd("SnowBeast_Jump_Attack", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsPreparing = false;
			Renderer->ChangeFrameAnimation("SnowBeast_DashSnowBeastBall");
			// Boss�� �پ� �ִ� ���� �ƴ� �ٴڿ� ���� �и��Ǿ� �����̹Ƿ� CreateActor �������� ���� ��ȯ �ʿ�
			/*if (MFBossDIR::LEFT == CurMFDir)
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA");
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 0,-500.0f,0 });
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB");
				SubRenderer01->GetTransform().PixLocalPositiveX();
				SubRenderer01->GetTransform().SetLocalPosition(float4{ -50.0f,-450.0f,0 });
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA");
				SubRenderer02->GetTransform().PixLocalNegativeX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB");
				SubRenderer03->GetTransform().PixLocalNegativeX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
			else
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA");
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 0,-500.0f,0 });
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB");
				SubRenderer01->GetTransform().PixLocalNegativeX();
				SubRenderer01->GetTransform().SetLocalPosition(float4{ 50.0f,-450.0f,0 });
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA");
				SubRenderer02->GetTransform().PixLocalPositiveX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB");
				SubRenderer03->GetTransform().PixLocalPositiveX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}*/
		});
	
	Renderer->AnimationBindEnd("SnowBeast_Dash_Attack", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsPreparing = false;
			Renderer->ChangeFrameAnimation("SnowBeast_DashSnowBeastBall");
			/*if (MFBossDIR::LEFT == CurMFDir)
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA");
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 0,-500.0f,0 });
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB");
				SubRenderer01->GetTransform().PixLocalPositiveX();
				SubRenderer01->GetTransform().SetLocalPosition(float4{ -50.0f,-450.0f,0 });
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA");
				SubRenderer02->GetTransform().PixLocalNegativeX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB");
				SubRenderer03->GetTransform().PixLocalNegativeX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}
			else
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeast_Limbs_MeltingA");
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 0,-500.0f,0 });
				SubRenderer00->SetPivot(PIVOTMODE::BOT);;
				SubRenderer00->On();

				SubRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_MeltingB");
				SubRenderer01->GetTransform().PixLocalNegativeX();
				SubRenderer01->GetTransform().SetLocalPosition(float4{ 50.0f,-450.0f,0 });
				SubRenderer01->SetPivot(PIVOTMODE::BOT);;
				SubRenderer01->On();

				SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA");
				SubRenderer02->GetTransform().PixLocalPositiveX();
				SubRenderer02->SetPivot(PIVOTMODE::BOT);;
				SubRenderer02->On();

				SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB");
				SubRenderer03->GetTransform().PixLocalPositiveX();
				SubRenderer03->SetPivot(PIVOTMODE::BOT);;
				SubRenderer03->On();
			}*/
		});

	Renderer->AnimationBindEnd("SnowBeast_JumptoJump_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_Jump_Attack");
		});

	Renderer->AnimationBindEnd("SnowBeast_DashtoJump_Trans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SnowBeast_Jump_Attack");
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

	SubRenderer00->AnimationBindEnd("SnowBeast_Limbs_MeltingA", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->CurAnimationReset();
			SubRenderer00->Off();
		});

	SubRenderer01->AnimationBindEnd("SnowBeast_Limbs_MeltingB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer01->CurAnimationReset();
			SubRenderer01->Off();
		});
	
	SubRenderer02->AnimationBindEnd("SnowBeast_Limbs_RMeltingA", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer02->CurAnimationReset();
			SubRenderer02->Off();
		});

	SubRenderer03->AnimationBindEnd("SnowBeast_Limbs_RMeltingB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer03->CurAnimationReset();
			SubRenderer03->Off();
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
		
		// ���� �������� ���ٰ� �б��� �������� ��, ������ �������� �̵��� �� �ְ� ��ȯ
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
	
	IdleLerpRatio += _DeltaTime;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	if (true == IsJump)
	{
		float LerpY = GameEngineMath::LerpLimit(1300, -1300, IdleLerpRatio) * _DeltaTime;

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
	// Fridge �ִϸ��̼� ������ �� ���� ��ȯ(���ε忣��)
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
			// ��Ʈ ����
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
				// Fridge �ִϸ��̼� ����
				Renderer->ChangeFrameAnimation("SnowBeastFridge_Freezer_Outro");
			}
			return;
		}

		if (true == IsShoot)
		{
			IceTime = 1.0f;
			//--IceCubeCount;
			// ť�� ����
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

	// ���Ž� �ִϸ��̼ǹ��ε忣�忡 BladeTime �ð����� + BladeCount 4 ����, StateManager2.ChangeState("MF2Idle");
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

		// Blade ����(�¿� ���� CurMFDir Ȯ�� �� ���� ����-ī��Ʈ�� ����-)
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
