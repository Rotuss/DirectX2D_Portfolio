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
	, TableRenderer(nullptr)
	, Collision(nullptr)
	, StartPos()
	, EndPos()
	, LerpPos()
	, Speed(200.0f)
	, YAdd(0.0f)
	, HP(10)
	, MinionPixCheck(false)
	, MinionPixRemove(false)
{
	MFBoss = this;
}

MortimerFreezeBoss::~MortimerFreezeBoss() 
{
}

bool MortimerFreezeBoss::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	HP -= 1;

	_Other->GetActor()->Death();
	
	if (0 == HP)
	{
		_This->GetActor()->Death();
	}

	return true;
}

void MortimerFreezeBoss::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("MFIdle", FrameAnimation_DESC("MFIdle", 0, 23, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("MFIdleTrans", FrameAnimation_DESC("MFIdle", 24, 32, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("Peashot_Intro", 0.1f, false));
		Renderer->CreateFrameAnimationFolder("PeashotIdle", FrameAnimation_DESC("Peashot_Idle", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("PeashotShoot", FrameAnimation_DESC("Peashot_Shoot", 0.1f, true));	
		Renderer->CreateFrameAnimationFolder("QuadshotStart", FrameAnimation_DESC("MF_Attack_Quadshot", 0, 15, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("QuadshotMinionAppear", FrameAnimation_DESC("MF_Attack_Quadshot", 15, 18, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("QuadshotMinionAfter", FrameAnimation_DESC("MF_Attack_Quadshot", 19, 30, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("WhaleDrop", FrameAnimation_DESC("Wizard_Whale_Drop", 0.1f, false));
		Renderer->CreateFrameAnimationFolder("WhaleDropAttackOutro", FrameAnimation_DESC("Wizard_Drop_Attack_Outro", 0.1f, false));
		Renderer->ChangeFrameAnimation("MFIdle");
		//Renderer->AnimationBindEnd("Move", &Player::TestFunction, this);
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		GetTransform().SetLocalPosition({ 1350, -380, -1 });
		//GetTransform().SetLocalPosition({ 640, -360, -1 });
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
	StateManager.CreateStateMember("MF1Idle", std::bind(&MortimerFreezeBoss::P1IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P1IdleStart, this, std::placeholders::_1));

	StateManager.CreateStateMember("Peashot", std::bind(&MortimerFreezeBoss::AttackPeashotUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackPeashotStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Quadshot", std::bind(&MortimerFreezeBoss::AttackQuadshotUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackQuadshotStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Whale", std::bind(&MortimerFreezeBoss::AttackWhaleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackWhaleStart, this, std::placeholders::_1));

	StateManager.ChangeState("Quadshot");
}

void MortimerFreezeBoss::Phase1Update(float _DeltaTime, const StateInfo& _Info)
{
	StateManager.Update(_DeltaTime);
}

void MortimerFreezeBoss::P1IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFIdle");
}

void MortimerFreezeBoss::P1IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float AccTime = GetAccTime();
	float AccDeltaTime = AccTime / 1.0f;

	/*if (StartPos[0].x == GetTransform().GetLocalPosition().x)
	{
		LerpPos = float4::LerpLimit(StartPos[0], EndPos[0], AccDeltaTime);
	}
	if (StartPos[1].x == GetTransform().GetLocalPosition().x)
	{
		LerpPos = float4::LerpLimit(StartPos[1], EndPos[1], AccDeltaTime);
	}*/
	LerpPos = float4::LerpLimit(StartPos[1], EndPos[1], AccDeltaTime);
	float LerpY = GameEngineMath::LerpLimit(-500, 500, AccDeltaTime) * _DeltaTime;

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 Test = LerpPos + float4(0, YAdd, -30);
	GetTransform().SetLocalPosition(Test);
}

void MortimerFreezeBoss::AttackPeashotStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->AnimationBindEnd("PeashotIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("PeashotIdle");
		});

	//MortimerFreezeCard* Ptr = GetLevel()->CreateActor<MortimerFreezeCard>(OBJECTORDER::Boss);
	//Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());

	MortimerFreezeTable* TableActor = GetLevel()->CreateActor<MortimerFreezeTable>(OBJECTORDER::Boss);
}

void MortimerFreezeBoss::AttackPeashotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	/*float AccTime = GetAccTime();
	float AccDeltaTime = AccTime / 1.0f;
	
	LerpPos = float4::LerpLimit(StartPos[1], EndPos[1], AccDeltaTime);
	float LerpY = GameEngineMath::LerpLimit(-500, 500, AccDeltaTime) * _DeltaTime;

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 Test = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(Test);*/
	
	if (300.0f >= GetTransform().GetLocalPosition().x || 1350.0f <= GetTransform().GetLocalPosition().x)
	{
		//Renderer->ChangeFrameAnimation("PeashotShoot");
	}
}

void MortimerFreezeBoss::AttackQuadshotStart(const StateInfo& _Info)
{
	GameEngineRandom RandomValue_;
	int RandomItemNum = RandomValue_.RandomInt(0, 1);
	
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
				Minion0->SetColMap(Player::MainPlayer->GetColMap());

				Minion1 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion1->SetDir(DIR::LEFT);
				Minion1->SetMoveDir(RandomItemNum);
				Minion1->SetGender(GENDER::GIRL);
				Minion1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(-110.0f, -30.0f));
				Minion1->SetColMap(Player::MainPlayer->GetColMap());

				Minion2 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion2->SetDir(DIR::RIGHT);
				Minion2->SetMoveDir(RandomItemNum);
				Minion2->SetGender(GENDER::BOY);
				Minion2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(110.0f, -40.0f));
				Minion2->SetColMap(Player::MainPlayer->GetColMap());

				Minion3 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion3->SetDir(DIR::RIGHT);
				Minion3->SetMoveDir(RandomItemNum);
				Minion3->SetGender(GENDER::GIRL);
				Minion3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(340.0f, 30.0f));
				Minion3->SetColMap(Player::MainPlayer->GetColMap());
			}
		});

	Renderer->AnimationBindFrame("QuadshotMinionAfter", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (3 == _Info.CurFrame)
			{
				MinionPixRemove = true;
			}
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
	Renderer->AnimationBindEnd("WhaleDrop", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("WhaleDropAttackOutro");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			
			// Whale »ý¼º
			MortimerFreezeWhale* Whale = GetLevel()->CreateActor<MortimerFreezeWhale>(OBJECTORDER::Boss);
			Whale->GetTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y * 3 + 90.0f, GetTransform().GetLocalPosition().z });
		});
	Renderer->AnimationBindEnd("WhaleDropAttackOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			//StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackWhaleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
