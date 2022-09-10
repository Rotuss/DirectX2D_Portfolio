#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "GlobalContents.h"
#include "MortimerFreezeTable.h"
#include "MortimerFreezeCard.h"
#include "MortimerFreezeMinion.h"
#include "MortimerFreezeWhale.h"
#include <iostream>
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeBoss* MortimerFreezeBoss::MFBoss= nullptr;

MortimerFreezeBoss::MortimerFreezeBoss()
	: Renderer(nullptr)
	, AddRenderer(nullptr)
	, TableRenderer(nullptr)
	, Collision(nullptr)
	, WhaleCollision(nullptr)
	, CurMFDir(MFBossDIR::LEFT)
	, StartPos()
	, EndPos()
	, LerpPos()
	, Speed(200.0f)
	, YAdd(0.0f)
	, IdleLerpRatio(0.0f)
	, PeashotAttackMoveTime(0.0f)
	, HP(1)
	, Phase2TransitionMotionCount(2)
	, PeashotStateCount(GameEngineRandom::MainRandom.RandomInt(3, 5))
	, PeashotAttackCount(GameEngineRandom::MainRandom.RandomInt(1, 2))
	, QuadshotStateCount(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, WhaleStateCount(GameEngineRandom::MainRandom.RandomInt(3, 4))
	, IsP1IdleStart(true)
	, MFMoveReplay(false)
	, IsCurRStartPos(true)
	, IsCurPeashotLStartPos(true)
	, IsCurPeashotStartAttack(false)
	, IsCurPeashotEnd(false)
	, IsIdleTransState(false)
	, MinionPixCheck(false)
	, MinionPixRemove(false)
	, IsEndPhase1(false)
	, DashTime(GameEngineRandom::MainRandom.RandomFloat(0.2f, 1.0f))
	, FridgeTime(GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f))
	, SmashTime(GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f))
	, IceTime(0.0f)
	, BladeTime(1.0f)
	, PrevSkill(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, DashMove(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, IceCubeCount(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, IceBatCount(4)
	, BladeCount(-1)
	, IsJump(static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1)))

{
	MFBoss = this;
}

MortimerFreezeBoss::~MortimerFreezeBoss() 
{
}

bool MortimerFreezeBoss::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	_Other->GetActor()->Death();
	
	if ("Peashot" == StateManager.GetCurStateStateName()
		|| "Quadshot" == StateManager.GetCurStateStateName()
		|| "Whale" == StateManager.GetCurStateStateName())
	{
		return false;
	}

	HP -= 1;
	
	if (0 >= HP)
	{
		HP = 0;
		//_This->GetActor()->Death();
		//StateManager.ChangeState("Transition_Phase2");
	}

	return true;
}

void MortimerFreezeBoss::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("MFIdle", FrameAnimation_DESC("MFIdle", 0, 23, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("MFIdleTrans", FrameAnimation_DESC("MFIdle", 24, 32, 0.1f, false));
		
		Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("Peashot_Intro", 0.2f, false));
		Renderer->CreateFrameAnimationFolder("PeashotIdle", FrameAnimation_DESC("Peashot_Idle", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("PeashotShoot", FrameAnimation_DESC("Peashot_Shoot", 0.1f, false));	
		Renderer->CreateFrameAnimationFolder("PeashotOutro", FrameAnimation_DESC("Peashot_Outro", 0.1f, true));

		Renderer->CreateFrameAnimationFolder("QuadshotStart", FrameAnimation_DESC("MF_Attack_Quadshot", 0, 15, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("QuadshotMinionAppear", FrameAnimation_DESC("MF_Attack_Quadshot", 15, 18, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("QuadshotMinionAfter", FrameAnimation_DESC("MF_Attack_Quadshot", 19, 30, 0.1f, false));
		
		Renderer->CreateFrameAnimationFolder("WhaleDrop", FrameAnimation_DESC("Wizard_Whale_Drop", 0.1f, false));
		Renderer->CreateFrameAnimationFolder("WhaleDropAttackOutro", FrameAnimation_DESC("Wizard_Drop_Attack_Outro", 0.1f, false));
		
		Renderer->CreateFrameAnimationFolder("MFPhase2Transition0", FrameAnimation_DESC("MFPhase2_Transition", 0, 10, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("MFPhase2Transition1", FrameAnimation_DESC("MFPhase2_Transition", 11, 15, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("MFPhase2Transition2", FrameAnimation_DESC("MFPhase2_Transition", 16, 27, 0.1f, false));
		
		Renderer->ChangeFrameAnimation("MFIdle");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		GetTransform().SetLocalPosition({ 1350, -380, -1 });
		//GetTransform().SetLocalPosition({ 950, -360, -1 });
	}

	{
		// AddRenderer 을 Renderer의 자식으로?-?
		AddRenderer = CreateComponent<GameEngineTextureRenderer>();
		AddRenderer->CreateFrameAnimationFolder("MFPhase2Transition1_Arm", FrameAnimation_DESC("MFPhase2_Transition", 28, 35, 0.1f, true));

		AddRenderer->ChangeFrameAnimation("MFPhase2Transition1_Arm");
		AddRenderer->SetScaleModeImage();
		AddRenderer->ScaleToTexture();
		AddRenderer->SetPivot(PIVOTMODE::TOP);
		AddRenderer->Off();
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 200,300,1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
	}

	{
		StartPos.push_back({ 300,-380,-1 });
		StartPos.push_back({ 1350,-380,-1 });

		EndPos.push_back({ 1350,-380,-1 });
		EndPos.push_back({ 300,-380,-1 });
	}

	PhaseManager.CreateStateMember("MFPhase1", std::bind(&MortimerFreezeBoss::Phase1Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase1Start, this, std::placeholders::_1));
	PhaseManager.CreateStateMember("MFPhase2", std::bind(&MortimerFreezeBoss::Phase2Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase2Start, this, std::placeholders::_1));
	PhaseManager.ChangeState("MFPhase1");
}

void MortimerFreezeBoss::Update(float _DeltaTime)
{
	PhaseManager.Update(_DeltaTime);

	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Weapon, CollisionType::CT_OBB2D, std::bind(&MortimerFreezeBoss::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 1.0f, 1.0f, 0.5f });
}

void MortimerFreezeBoss::Phase1Start(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsKey("Num1_Peashot"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1_Peashot", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Num2_Quadshot", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Num3_Whale", VK_NUMPAD3);
	}
	
	StateManager.CreateStateMember("MF1Idle", std::bind(&MortimerFreezeBoss::P1IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P1IdleStart, this, std::placeholders::_1));

	StateManager.CreateStateMember("Peashot", std::bind(&MortimerFreezeBoss::AttackPeashotUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackPeashotStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Quadshot", std::bind(&MortimerFreezeBoss::AttackQuadshotUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackQuadshotStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Whale", std::bind(&MortimerFreezeBoss::AttackWhaleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackWhaleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Transition_Phase2", std::bind(&MortimerFreezeBoss::Phase1to2Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase1to2Start, this, std::placeholders::_1));

	StateManager.ChangeState("MF1Idle");
}

void MortimerFreezeBoss::Phase1Update(float _DeltaTime, const StateInfo& _Info)
{
	StateManager.Update(_DeltaTime);
}

void MortimerFreezeBoss::P1IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFIdle");

	Renderer->AnimationBindEnd("MFIdleTrans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsIdleTransState = false;
			Renderer->ChangeFrameAnimation("MFIdle");
			
			if (0 == Num)
			{
				Renderer->GetTransform().PixLocalNegativeX();
			}
			if (1 == Num)
			{
				Renderer->GetTransform().PixLocalPositiveX();
			}

			IdleLerpRatio = 0.0f;
		});
}

void MortimerFreezeBoss::P1IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;
	float PeashotRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float QuadshotRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float WhaleRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);

	if (true == GameEngineInput::GetInst()->IsDown("Num1_Peashot"))
	{
		PeashotRandomPer = 0.5f;
		PeashotStateCount = 0;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Num2_Quadshot"))
	{
		QuadshotRandomPer = 0.8f;
		QuadshotStateCount = 0;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Num3_Whale"))
	{
		WhaleRandomPer = 0.9f;
		WhaleStateCount = 0;
	}

	// 보스의 x값이 300 혹은 1350일 때 랜덤한 확률로 Peashot 상태
	if (300.0f >= MFCurXPos || 1350.0f <= MFCurXPos)
	{
		if (0.5f >= PeashotRandomPer && 0 == PeashotStateCount)
		{
			PeashotStateCount = GameEngineRandom::MainRandom.RandomInt(3, 5);
			StateManager.ChangeState("Peashot");
			return;
		}

		if (0 >= PeashotStateCount)
		{
			PeashotStateCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}
	}

	// x값이 650 ~ 950일 때 랜덤한 확률 Quadshot 상태
	if (650.0f <= MFCurXPos && 950.0f >= MFCurXPos)
	{
		if (0.8f >= QuadshotRandomPer && 0 == QuadshotStateCount)
		{
			QuadshotStateCount = GameEngineRandom::MainRandom.RandomInt(3, 5);
			StateManager.ChangeState("Quadshot");
			return;
		}

		if (0 >= QuadshotStateCount)
		{
			QuadshotStateCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}
	}

	// 보스와 플레이어의 x값이 일치할 때 랜덤한 확률로 Whale 상태
	if (MsChalice::Chalice->GetTransform().GetLocalPosition().x + 10.0f >= MFCurXPos
		&& MsChalice::Chalice->GetTransform().GetLocalPosition().x - 10.0f <= MFCurXPos)
	{
		if (0.9f >= WhaleRandomPer && 0 == WhaleStateCount)
		{
			WhaleStateCount = GameEngineRandom::MainRandom.RandomInt(3, 5);
			StateManager.ChangeState("Whale");
			return;
		}

		if (0 >= WhaleStateCount)
		{
			WhaleStateCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}
	}

	if (true == MFMoveReplay)
	{
		if (MFBossDIR::LEFT == CurMFDir)
		{
			MFMoveReplay = false;
			Num = 1;
		}
		if (MFBossDIR::RIGHT == CurMFDir)
		{
			MFMoveReplay = false;
			Num = 0;
		}
	}

	if (true == IsCurRStartPos)
	{
		if (StartPos[1].x <= MFCurXPos)
		{
			IsCurRStartPos = false;
			IsIdleTransState = true;
			CurMFDir = MFBossDIR::LEFT;
			Num = 1;

			if (false == IsP1IdleStart)
			{
				Renderer->ChangeFrameAnimation("MFIdleTrans");
			}
			if (true == IsP1IdleStart)
			{
				IsP1IdleStart = false;
				IsIdleTransState = false;
			}
			--PeashotStateCount;
			--QuadshotStateCount;
			--WhaleStateCount;

			if (0 == HP)
			{
				IsEndPhase1 = true;
				return;
			}
		}

		if (StartPos[0].x + 100 <= MFCurXPos && true == IsEndPhase1)
		{
			StateManager.ChangeState("Transition_Phase2");
			return;
		}
	}
	else
	{
		if (StartPos[0].x >= MFCurXPos)
		{
			IsCurRStartPos = true;
			IsIdleTransState = true;
			CurMFDir = MFBossDIR::RIGHT;
			Num = 0;

			if (false == IsP1IdleStart)
			{
				Renderer->ChangeFrameAnimation("MFIdleTrans");
			}
			if (true == IsP1IdleStart)
			{
				IsP1IdleStart = false;
				IsIdleTransState = false;
			}
			--PeashotStateCount;
			--QuadshotStateCount;
			--WhaleStateCount;

			if (0 == HP)
			{
				IsEndPhase1 = true;
				return;
			}
		}

		if (StartPos[1].x - 100 >= MFCurXPos && true == IsEndPhase1)
		{
			StateManager.ChangeState("Transition_Phase2");
			return;
		}
	}

	if (true == IsIdleTransState)
	{
		return;
	}

	IdleLerpRatio += _DeltaTime;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	LerpPos = float4::LerpLimit(StartPos[Num], EndPos[Num], IdleLerpRatio);
	float LerpY = GameEngineMath::LerpLimit(-200, 200, IdleLerpRatio) * _DeltaTime;

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

void MortimerFreezeBoss::AttackPeashotStart(const StateInfo& _Info)
{
	PeashotAttackMoveTime = 0.0f;
	PeashotAttackCount = GameEngineRandom::MainRandom.RandomInt(1, 2);
	IsCurPeashotStartAttack = false;
	IsCurPeashotEnd = false;

	if (true == IsCurRStartPos)
	{
		IsCurPeashotLStartPos = true;
	}
	else
	{
		IsCurPeashotLStartPos = false;
	}

	Renderer->ChangeFrameAnimation("PeashotIntro");
	MortimerFreezeTable* TableActor = GetLevel()->CreateActor<MortimerFreezeTable>(OBJECTORDER::Boss);

	Renderer->AnimationBindStart("PeashotIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::RIGHT == CurMFDir)
			{
				Renderer->GetTransform().PixLocalNegativeX();
			}
		});

	Renderer->AnimationBindEnd("PeashotIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("PeashotIdle");
		});

	Renderer->AnimationBindStart("PeashotShoot", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsCurPeashotStartAttack = true;
		});

	Renderer->AnimationBindEnd("PeashotShoot", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsCurPeashotStartAttack = false;
			Renderer->ChangeFrameAnimation("PeashotIdle");
		});

	Renderer->AnimationBindEnd("PeashotOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsP1IdleStart = true;
			IdleLerpRatio = 0.0f;
			StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackPeashotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;
	
	PeashotAttackMoveTime += _DeltaTime;

	if (1.0f >= PeashotAttackMoveTime)
	{
		return;
	}

	if (true == IsCurPeashotStartAttack)
	{
		return;
	}

	if (false == IsCurPeashotLStartPos)
	{
		if (StartPos[1].x <= MFCurXPos)
		{
			IsCurPeashotLStartPos = true;
			CurMFDir = MFBossDIR::LEFT;

			if (0 == PeashotAttackCount)
			{
				Renderer->ChangeFrameAnimation("PeashotOutro");
				Renderer->GetTransform().PixLocalPositiveX();
				IsCurRStartPos = true;
				IsCurPeashotEnd = true;
				return;
			}

			Renderer->ChangeFrameAnimation("PeashotShoot");
			Renderer->GetTransform().PixLocalPositiveX();
			Num = 1;
			--PeashotAttackCount;
			IdleLerpRatio = 0.0f;

			MortimerFreezeCard* Ptr = GetLevel()->CreateActor<MortimerFreezeCard>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
		}
	}
	else
	{
		if (StartPos[0].x >= MFCurXPos)
		{
			IsCurPeashotLStartPos = false;
			CurMFDir = MFBossDIR::RIGHT;

			if (0 == PeashotAttackCount)
			{
				Renderer->ChangeFrameAnimation("PeashotOutro");
				Renderer->GetTransform().PixLocalNegativeX();
				IsCurRStartPos = false;
				IsCurPeashotEnd = true;
				return;
			}

			Renderer->ChangeFrameAnimation("PeashotShoot");
			Renderer->GetTransform().PixLocalNegativeX();
			Num = 0;
			--PeashotAttackCount;
			IdleLerpRatio = 0.0f;

			MortimerFreezeCard* Ptr = GetLevel()->CreateActor<MortimerFreezeCard>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
		}
	}

	IdleLerpRatio += _DeltaTime;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	LerpPos = float4::LerpLimit(StartPos[Num], EndPos[Num], IdleLerpRatio);
	float LerpY = GameEngineMath::LerpLimit(-200, 200, IdleLerpRatio) * _DeltaTime;

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

void MortimerFreezeBoss::AttackQuadshotStart(const StateInfo& _Info)
{
	int RandomItemNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
	
	Renderer->ChangeFrameAnimation("QuadshotStart");
	Renderer->AnimationBindFrame("QuadshotStart", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (15 == _Info.CurFrame)
			{
				Renderer->ChangeFrameAnimation("QuadshotMinionAppear");
				
				Minion0 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion0->SetDir(DIR::LEFT);
				Minion0->SetMoveDir(RandomItemNum);
				Minion0->SetGender(GENDER::BOY);
				Minion0->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(-340.0f, 20.0f));
				Minion0->SetColMap(MsChalice::Chalice->GetColMap());

				Minion1 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion1->SetDir(DIR::LEFT);
				Minion1->SetMoveDir(RandomItemNum);
				Minion1->SetGender(GENDER::GIRL);
				Minion1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(-110.0f, -30.0f));
				Minion1->SetColMap(MsChalice::Chalice->GetColMap());

				Minion2 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion2->SetDir(DIR::RIGHT);
				Minion2->SetMoveDir(RandomItemNum);
				Minion2->SetGender(GENDER::BOY);
				Minion2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(110.0f, -40.0f));
				Minion2->SetColMap(MsChalice::Chalice->GetColMap());

				Minion3 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion3->SetDir(DIR::RIGHT);
				Minion3->SetMoveDir(RandomItemNum);
				Minion3->SetGender(GENDER::GIRL);
				Minion3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(340.0f, 30.0f));
				Minion3->SetColMap(MsChalice::Chalice->GetColMap());
			}
		});

	Renderer->AnimationBindFrame("QuadshotMinionAfter", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (3 == _Info.CurFrame)
			{
				MinionPixRemove = true;
			}
		});

	Renderer->AnimationBindEnd("QuadshotMinionAfter", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			MFMoveReplay = true;
			StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackQuadshotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == MinionPixCheck)
	{
		MinionPixCheck = false;

		Renderer->ChangeFrameAnimation("QuadshotMinionAfter");
	}
}

void MortimerFreezeBoss::AttackWhaleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("WhaleDrop");
	Renderer->SetPivot(PIVOTMODE::TOP);
	Renderer->SetPivotToVector(float4{ 0, 250.0f });

	{
		WhaleCollision = CreateComponent<GameEngineCollision>();
		WhaleCollision->GetTransform().SetLocalScale({ 700,800,1 });
		WhaleCollision->GetTransform().SetLocalPosition(float4{ 0.0f,-200.0f });
		WhaleCollision->ChangeOrder(OBJECTORDER::BossWhale);
		WhaleCollision->Off();
	}

	Renderer->AnimationBindFrame("WhaleDrop", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (29 == _Info.CurFrame)
			{
				WhaleCollision->On();
			}
		});

	Renderer->AnimationBindEnd("WhaleDrop", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("WhaleDropAttackOutro");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			Renderer->SetPivotToVector(float4{ 0, -20.0f });

			WhaleCollision->Death();
			// Whale 생성
			MortimerFreezeWhale* Whale = GetLevel()->CreateActor<MortimerFreezeWhale>(OBJECTORDER::Boss);
			Whale->GetTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y * 3 + 90.0f, GetTransform().GetLocalPosition().z });
		});
	Renderer->AnimationBindEnd("WhaleDropAttackOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackWhaleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase1to2Start(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFPhase2Transition0");
	
	Renderer->AnimationBindEnd("MFPhase2Transition0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("MFPhase2Transition1");
			
			if (MFBossDIR::LEFT == CurMFDir)
			{
				AddRenderer->GetTransform().PixLocalPositiveX();
				AddRenderer->GetTransform().SetLocalPosition(float4{ -100, 100, 0.5 });
				AddRenderer->On();
			}
			if (MFBossDIR::RIGHT== CurMFDir)
			{
				AddRenderer->GetTransform().PixLocalNegativeX();
				AddRenderer->GetTransform().SetLocalPosition(float4{ 100, 100, 0.5 });
				AddRenderer->On();
			}
		});

	AddRenderer->AnimationBindEnd("MFPhase2Transition1_Arm", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == Phase2TransitionMotionCount)
			{
				AddRenderer->Off();
				Renderer->ChangeFrameAnimation("MFPhase2Transition2");
				
				// 페이즈2 전환 확인용
				PhaseManager.ChangeState("MFPhase2");
			}

			Phase2TransitionMotionCount -= 1;
		});
}

void MortimerFreezeBoss::Phase1to2Update(float _DeltaTime, const StateInfo& _Info)
{

}

