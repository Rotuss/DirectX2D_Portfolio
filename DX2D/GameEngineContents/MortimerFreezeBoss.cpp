#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "GlobalContents.h"
#include "MortimerFreezeTable.h"
#include "MortimerFreezeCard.h"
#include <iostream>

MortimerFreezeBoss* MortimerFreezeBoss::MFBoss= nullptr;

MortimerFreezeBoss::MortimerFreezeBoss() 
	: Renderer(nullptr)
	, TableRenderer(nullptr)
	, StartPos()
	, EndPos()
	, LerpPos()
	, Speed(200.0f)
	, YAdd(0.0f)
	, HP(10)
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
		Renderer->ChangeFrameAnimation("MFIdle");
		//Renderer->AnimationBindEnd("Move", &Player::TestFunction, this);
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

	StateManager.ChangeState("Peashot");
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
}

void MortimerFreezeBoss::AttackQuadshotUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MortimerFreezeBoss::AttackWhaleStart(const StateInfo& _Info)
{
}

void MortimerFreezeBoss::AttackWhaleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
