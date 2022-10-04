#include "PreCompile.h"
#include "MsChalice.h"
#include "Weapon.h"
#include "UIHealth.h"
#include "GlobalContents.h"
#include "MortimerFreezeLevel.h"
#include "MortimerFreezeSnowPlatform.h"
#include <iostream>

MsChalice* MsChalice::Chalice = nullptr;

MsChalice::MsChalice()
	: Renderer(nullptr)
	, ChaliceDir("Right")
	, ChalicePrevDir("")
	, MoveDir(float4::ZERO)
	, AddDir(float4::ZERO)
	, Speed(500.0f)
	, WeaponTime(0.0f)
	, NoDamageTime(0.0f)
	, ChaliceHP(4)
	, PlatformCount(-1)
	, IsNoDamageState(false)
	, IsAimState(false)
	, IsDoubleJump(false)
{
	Chalice = this;
}

MsChalice::~MsChalice()
{
}

CollisionReturn MsChalice::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == IsNoDamageState)
	{
		return CollisionReturn::Break;
	}

	if (0 < NoDamageTime)
	{
		return CollisionReturn::Break;
	}
	
	//_Other->GetActor()->Death();
	if (0 < ChaliceHP)
	{
		ChaliceHP += -1;
	}
	Health->SetHealthCount(ChaliceHP);
	StateManager.ChangeState("ChaliceHit");
	return CollisionReturn::ContinueCheck;
}

CollisionReturn MsChalice::CollisionCheckParry(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if ("ChaliceDash" != StateManager.GetCurStateStateName())
	{
		if (true == IsNoDamageState)
		{
			return CollisionReturn::Break;
		}

		if (0 < NoDamageTime)
		{
			return CollisionReturn::Break;
		}

		if (0 < ChaliceHP)
		{
			ChaliceHP += -1;
		}
		Health->SetHealthCount(ChaliceHP);
		StateManager.ChangeState("ChaliceHit");
		return CollisionReturn::ContinueCheck;
	}
	else
	{
		// Dash Pasrry
		MoveDir = GetTransform().GetUpVector() * 1000.0f;

		return CollisionReturn::ContinueCheck;
	}
}

CollisionReturn MsChalice::CollisionCheckMinion(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == IsNoDamageState)
	{
		return CollisionReturn::Break;
	}
	
	if (0 < NoDamageTime)
	{
		return CollisionReturn::Break;
	}

	if (0 < ChaliceHP)
	{
		ChaliceHP += -1;
	}
	Health->SetHealthCount(ChaliceHP);
	StateManager.ChangeState("ChaliceHit");
	return CollisionReturn::ContinueCheck;
}

CollisionReturn MsChalice::CollisionCheckWhale(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == IsNoDamageState)
	{
		return CollisionReturn::Break;
	}
	
	if (0 < NoDamageTime)
	{
		return CollisionReturn::Break;
	}

	if (0 < ChaliceHP)
	{
		ChaliceHP += -1;
	}
	Health->SetHealthCount(ChaliceHP);
	StateManager.ChangeState("ChaliceHit");
	return CollisionReturn::ContinueCheck;
}

// 발판 테스트
CollisionReturn MsChalice::CollisionCheckPlatform(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	AddDir.x = _Other->GetActor<MortimerFreezeSnowPlatform>()->GetMovePos().x/* * 1.8f*/;
	PlatformCount = _Other->GetActor<MortimerFreezeSnowPlatform>()->Index;

	return CollisionReturn::Break;
}

CollisionReturn MsChalice::CollisionCheckPhase3Bot(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MoveDir = GetTransform().GetUpVector() * 1500.0f;
	if (0 < NoDamageTime)
	{
		return CollisionReturn::Break;
	}

	if (0 < ChaliceHP)
	{
		ChaliceHP += -1;
	}
	Health->SetHealthCount(ChaliceHP);
	StateManager.ChangeState("ChaliceHit");
	return CollisionReturn::ContinueCheck;
}

void MsChalice::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("ChaliceLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("ChaliceLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ChaliceRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("ChaliceUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("ChaliceDown", VK_DOWN);

		GameEngineInput::GetInst()->CreateKey("ChaliceJump", 'Z');
		GameEngineInput::GetInst()->CreateKey("ChaliceShoot", 'X');
		GameEngineInput::GetInst()->CreateKey("ChaliceAim", 'C');
		GameEngineInput::GetInst()->CreateKey("ChaliceDash", VK_SHIFT);

		GameEngineInput::GetInst()->CreateKey("ChaliceNoDamage", 'M');
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Chalice_Intro", FrameAnimation_DESC("Intros_Regular", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle", FrameAnimation_DESC("Idle", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle_Shoot", FrameAnimation_DESC("Shoot_Straight_Shoot", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle_Up", FrameAnimation_DESC("Aim_Up", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle_Up_Shoot", FrameAnimation_DESC("Shoot_Up_Shoot", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Duck_Start", FrameAnimation_DESC("Duck_Duck", 0.05f, false));
		Renderer->CreateFrameAnimationFolder("Chalice_Duck_Idle", FrameAnimation_DESC("Duck_Idle", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Duck_Idle_Shoot", FrameAnimation_DESC("Duck_Shoot_Shoot", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Duck_StandUp", FrameAnimation_DESC("Duck_StandUp", 0.1f, false));
		Renderer->CreateFrameAnimationFolder("Chalice_Aim", FrameAnimation_DESC("Aim_Straight", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Aim_Shoot", FrameAnimation_DESC("Shoot_Straight_Shoot", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Aim_Up", FrameAnimation_DESC("Aim_Up", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Aim_Up_Shoot", FrameAnimation_DESC("Shoot_Up_Shoot", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Aim_Diagonal", FrameAnimation_DESC("Aim_Diagonal_Up", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Aim_Diagonal_Shoot", FrameAnimation_DESC("Shoot_Diagonal_Up_Shoot", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Run", FrameAnimation_DESC("Run_Regular_Regular", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Run_Shoot", FrameAnimation_DESC("Run_Shoot_Straight_Straight", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Run_Diagonal_Shoot", FrameAnimation_DESC("Run_Shoot_DiagonalUp_DiagonalUp", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Jump_Regular", FrameAnimation_DESC("Jump_Regular_Jump", 0.05f, false));
		Renderer->CreateFrameAnimationFolder("Chalice_Jump_Double", FrameAnimation_DESC("Jump_DoubleJump_Jump", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Dash", FrameAnimation_DESC("Dash_Air", 0.05f, false));
		Renderer->CreateFrameAnimationFolder("Chalice_Hit", FrameAnimation_DESC("Hit_Ground", 0.05f, true));
		Renderer->ChangeFrameAnimation("Chalice_Intro");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);

		GetTransform().SetLocalPosition({ 550, -850 , -3 });

		Renderer->AnimationBindEnd("Chalice_Intro", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				StateManager.ChangeState("ChaliceIdle");
			});
		
		Renderer->AnimationBindEnd("Chalice_Idle_Shoot", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				StateManager.ChangeState("ChaliceIdle");
			});

		Renderer->AnimationBindEnd("Chalice_Hit", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				StateManager.ChangeState("ChaliceIdle");
			});

		Collision = CreateComponent<GameEngineCollision>();
		// Collision3D
		//Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 10000.0f });

		// Collision2D
		Collision->SetCollisionMode(CollisionMode::Ex);
		Collision->GetTransform().SetLocalScale({ 50.0f, 80.0f, 1.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f,50.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
	}

	StateManager.CreateStateMember("ChaliceIntro", std::bind(&MsChalice::IntroUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::IntroStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceIdle", std::bind(&MsChalice::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::IdleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceDuck", std::bind(&MsChalice::DuckUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::DuckStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceAim", std::bind(&MsChalice::AimUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::AimStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceRun", std::bind(&MsChalice::RunUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::RunStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceJump", std::bind(&MsChalice::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::JumpStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceDash", std::bind(&MsChalice::DashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::DashStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceHit", std::bind(&MsChalice::HitUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::HitStart, this, std::placeholders::_1));
	StateManager.ChangeState("ChaliceIntro");

	Health = GetLevel()->CreateActor<UIHealth>(OBJECTORDER::UI);
}

void MsChalice::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);

	if (true == GameEngineInput::GetInst()->IsDown("ChaliceNoDamage"))
	{
		NoDamageStateSwitch();
	}

	if (true == GetLevel<MortimerFreezeLevel>()->GetIsMove())
	{
		Renderer->GetTransform().SetLocalPosition(float4{ 0.0f,0.0f,-700.0f });
	}

	float4 Gravity = GetTransform().GetDownVector() * _DeltaTime * 2500.0f * 2.0f;

	ColorCheck = ColRenderer->GetCurTexture();
	if (nullptr == ColorCheck)
	{
		return;
	}
	while (true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-GetTransform().GetLocalPosition().y)).CompareInt4D(float4::BLACK))
	{
		GetTransform().SetLocalMove(GetTransform().GetUpVector());
	}
	if (true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-(GetTransform().GetLocalPosition().y + Gravity.y))).CompareInt4D(float4::BLACK))
	{
		Gravity = float4::ZERO;
	}

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	if (250.0f > GetTransform().GetLocalPosition().x)
	{
		GetTransform().SetLocalPosition(float4(250.0f, GetTransform().GetLocalPosition().y, GetTransform().GetLocalPosition().z));
		return;
	}
	if (1400.0f < GetTransform().GetLocalPosition().x)
	{
		GetTransform().SetLocalPosition(float4(1400.0f, GetTransform().GetLocalPosition().y, GetTransform().GetLocalPosition().z));
		return;
	}

	NoDamageTime -= _DeltaTime;

	MoveDir += Gravity;
	GetTransform().SetLocalMove(MoveDir * _DeltaTime + AddDir);

	// 발판 테스트
	bool IsCollision_ = false;
	if (0.0f >= MoveDir.y)
	{
		while (true == Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::SnowPlatform, CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheckPlatform, this, std::placeholders::_1, std::placeholders::_2)))
		{
			GetTransform().SetLocalMove(GetTransform().GetUpVector());
			IsCollision_ = true;
		}
	}

	if (true == IsCollision_)
	{
		if (0 >= MoveDir.y)
		{
			MoveDir.y = 0.0f;

			if ("ChaliceJump" == StateManager.GetCurStateStateName())
			{
				StateManager.ChangeState("ChaliceIdle");
			}
		}

		GetTransform().SetLocalMove(GetTransform().GetDownVector() * 2.0f);
	}
	else
	{
		AddDir = float4::ZERO;
	}

	// Collision3D
	/*Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		[](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			_Other->GetActor()->Death();
			return true;
		});*/

		// Collision2D
	Collision->IsCollisionEnterBase(CollisionType::CT_OBB2D, static_cast<int>(OBJECTORDER::Boss), CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollisionEnterBase(CollisionType::CT_OBB2D, static_cast<int>(OBJECTORDER::Parry), CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheckParry, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollisionEnterBase(CollisionType::CT_OBB2D, static_cast<int>(OBJECTORDER::BossMinion), CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheckMinion, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollisionEnterBase(CollisionType::CT_OBB2D, static_cast<int>(OBJECTORDER::BossWhale), CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheckWhale, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollisionEnterBase(CollisionType::CT_OBB2D, static_cast<int>(OBJECTORDER::Phase3Bot), CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheckPhase3Bot, this, std::placeholders::_1, std::placeholders::_2));

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceAim"))
	{
		if (false == IsAimState)
		{
			IsAimState = true;
			StateManager.ChangeState("ChaliceAim");
		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceShoot")
		&& "ChaliceJump" != StateManager.GetCurStateStateName()
		&& "ChaliceHit" != StateManager.GetCurStateStateName())
	{
		CurShootName = "_Shoot";

		WeaponTime -= _DeltaTime;

		if (0.0f > WeaponTime)
		{
			WeaponPtr = GetLevel()->CreateActor<Weapon>(OBJECTORDER::Weapon);
			WeaponPtr->SetWeaponDir(ChaliceDir);
			if ("Right" == ChaliceDir)
			{
				WeaponPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 100.0f,50.0f });
			}
			if ("Left" == ChaliceDir)
			{
				WeaponPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -100.0f,50.0f });
			}
			if ("Right" == ChalicePrevDir && "Up" == ChaliceDir)
			{
				WeaponPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 20.0f,200.0f });
			}
			if ("Left" == ChalicePrevDir && "Up" == ChaliceDir)
			{
				WeaponPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -20.0f,200.0f });
			}
			if ("RightUp" == ChaliceDir)
			{
				if ("ChaliceAim" == StateManager.GetCurStateStateName())
				{
					CurStateName = "Chalice_Aim_Diagonal";
				}
				if ("ChaliceRun" == StateManager.GetCurStateStateName())
				{
					CurStateName = "Chalice_Run_Diagonal";
				}
				WeaponPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 100.0f,200.0f });
			}
			if ("LeftUp" == ChaliceDir)
			{
				if ("ChaliceAim" == StateManager.GetCurStateStateName())
				{
					CurStateName = "Chalice_Aim_Diagonal";
				}
				if ("ChaliceRun" == StateManager.GetCurStateStateName())
				{
					CurStateName = "Chalice_Run_Diagonal";
				}
				WeaponPtr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ -100.0f,200.0f });
			}

			WeaponTime = 0.2f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsUp("ChaliceShoot"))
	{
		if ("RightUp" == ChaliceDir || "LeftUp" == ChaliceDir)
		{
			if ("ChaliceAim" == StateManager.GetCurStateStateName())
			{
				CurStateName = "Chalice_Aim";
			}
			if ("ChaliceRun" == StateManager.GetCurStateStateName())
			{
				CurStateName = "Chalice_Run";
			}
		}
		CurShootName = "";
		WeaponTime = 0.0f;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		if ("ChaliceJump" != StateManager.GetCurStateStateName())
		{
			StateManager.ChangeState("ChaliceDuck");
		}
	}

	Renderer->ChangeFrameAnimation(CurStateName + CurShootName);
}

void MsChalice::IntroStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Intro";
	MoveDir = float4::ZERO;
}

void MsChalice::IntroUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MsChalice::IdleStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Idle";
	MoveDir = float4::ZERO;
}

void MsChalice::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		StateManager.ChangeState("ChaliceRun");
		return;
	}

	if ("LeftUp" == ChalicePrevDir)
	{
		ChalicePrevDir = "Left";
	}
	if ("RightUp" == ChalicePrevDir)
	{
		ChalicePrevDir = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp"))
	{
		CurStateName = "Chalice_Idle_Up";
		if ("Up" != ChaliceDir)
		{
			ChalicePrevDir = ChaliceDir;
			ChaliceDir = "Up";
		}
	}

	if (true == GameEngineInput::GetInst()->IsUp("ChaliceUp"))
	{
		CurStateName = "Chalice_Idle";
		ChaliceDir = ChalicePrevDir;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceJump"))
	{
		StateManager.ChangeState("ChaliceJump");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceDash"))
	{
		StateManager.ChangeState("ChaliceDash");
		return;
	}
}

void MsChalice::DuckStart(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("ChaliceShoot"))
	{
		CurStateName = "Chalice_Duck_Start";
	}

	CurStateName = "Chalice_Duck_Idle";

	// duck_duck 애니메이션이 끝나면 duck_idle 애니메이션으로 전환
	Renderer->AnimationBindEnd("Chalice_Duck_Start", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			CurStateName = "Chalice_Duck_Idle";
		});
	// duck_stand 애니메이션이 끝나면 idle 상태로 전환
	Renderer->AnimationBindEnd("Chalice_Duck_StandUp", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager.ChangeState("ChaliceIdle");
			return;
		});

	MoveDir = float4::ZERO;
}

void MsChalice::DuckUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("ChaliceDown"))
	{
		if (false == GameEngineInput::GetInst()->IsPress("ChaliceShoot"))
		{
			CurStateName = "Chalice_Duck_StandUp";
			return;
		}

		StateManager.ChangeState("ChaliceIdle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		Renderer->GetTransform().PixLocalNegativeX();
		ChaliceDir = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		Renderer->GetTransform().PixLocalPositiveX();
		ChaliceDir = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceJump"))
	{
		StateManager.ChangeState("ChaliceJump");
		return;
	}
}

void MsChalice::AimStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Aim";
	MoveDir = float4::ZERO;
}

void MsChalice::AimUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("ChaliceAim"))
	{
		IsAimState = false;
		StateManager.ChangeState("ChaliceIdle");
		return;
	}
	
	if (false == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		|| false == GameEngineInput::GetInst()->IsPress("ChaliceRight")
		|| false == GameEngineInput::GetInst()->IsPress("ChaliceUp"))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		Renderer->GetTransform().PixLocalNegativeX();
		ChaliceDir = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		Renderer->GetTransform().PixLocalPositiveX();
		ChaliceDir = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp"))
	{
		CurStateName = "Chalice_Aim_Up";
		if ("Up" != ChaliceDir)
		{
			ChalicePrevDir = ChaliceDir;
			ChaliceDir = "Up";
		}
	}

	if (true == GameEngineInput::GetInst()->IsUp("ChaliceUp"))
	{
		CurStateName = "Chalice_Aim";
		ChaliceDir = ChalicePrevDir;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		ChaliceDir = "LeftUp";
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		ChaliceDir = "RightUp";
		return;
	}
}

void MsChalice::RunStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Run";
	MoveDir = float4::ZERO;
}

void MsChalice::RunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		&& false == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("ChaliceJump"))
	{
		StateManager.ChangeState("ChaliceJump");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceDash"))
	{
		StateManager.ChangeState("ChaliceDash");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		MoveDir.x = -Speed/*GetTransform().GetLeftVector() * Speed*/;
		Renderer->GetTransform().PixLocalNegativeX();
		ChaliceDir = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		MoveDir.x = Speed/*GetTransform().GetRightVector() * Speed*/;
		Renderer->GetTransform().PixLocalPositiveX();
		ChaliceDir = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsUp("ChaliceUp"))
	{
		CurStateName = "Chalice_Run";
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		ChaliceDir = "LeftUp";
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		ChaliceDir = "RightUp";
		return;
	}
}

void MsChalice::JumpStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Jump_Regular";
	IsDoubleJump = false;

	MoveDir = GetTransform().GetUpVector() * 1500.0f;
}

void MsChalice::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsDown("ChaliceJump") && false == IsDoubleJump)
	{
		CurStateName = "Chalice_Jump_Double";
		IsDoubleJump = true;

		MoveDir = GetTransform().GetUpVector() * 1500.0f;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		MoveDir = float4{ -Speed,MoveDir.y };
		Renderer->GetTransform().PixLocalNegativeX();
		ChaliceDir = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		MoveDir = float4{ Speed,MoveDir.y };
		Renderer->GetTransform().PixLocalPositiveX();
		ChaliceDir = "Right";
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceDash"))
	{
		StateManager.ChangeState("ChaliceDash");
		return;
	}

	if (true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-GetTransform().GetLocalPosition().y)).CompareInt4D(float4::BLACK))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}
}

void MsChalice::DashStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Dash";

	Renderer->AnimationBindEnd("Chalice_Dash", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager.ChangeState("ChaliceIdle");
		});
}

void MsChalice::DashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if ("Left" == ChaliceDir)
	{
		MoveDir = GetTransform().GetLeftVector() * (Speed * 1.2f);
	}
	if ("Right" == ChaliceDir)
	{
		MoveDir = GetTransform().GetRightVector() * (Speed * 1.2f);
	}
}

void MsChalice::HitStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Hit";
	NoDamageTime = 1.5f;
}

void MsChalice::HitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 이동??
}
