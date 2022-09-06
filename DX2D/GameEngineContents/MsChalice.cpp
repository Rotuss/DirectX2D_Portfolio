#include "PreCompile.h"
#include "MsChalice.h"
#include "Weapon.h"
#include "GlobalContents.h"
#include <iostream>

MsChalice* MsChalice::Chalice = nullptr;

MsChalice::MsChalice()
	: Renderer(nullptr)
	, ChaliceDir("Right")
	, ChalicePrevDir("")
	, MoveDir(float4::ZERO)
	, Speed(1000.0f)
	, WeaponTime(0.0f)
{
	Chalice = this;
}

MsChalice::~MsChalice()
{
}

bool MsChalice::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	_Other->GetActor()->Death();
	return true;
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
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Chalice_Idle", FrameAnimation_DESC("Idle", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle_Shoot", FrameAnimation_DESC("Shoot_Straight_Shoot", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle_Up", FrameAnimation_DESC("Aim_Up", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Idle_Up_Shoot", FrameAnimation_DESC("Shoot_Up_Shoot", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Run", FrameAnimation_DESC("Run_Regular_Regular", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Run_Shoot", FrameAnimation_DESC("Run_Shoot_Straight_Straight", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Jump_Regular", FrameAnimation_DESC("Jump_Regular_Jump", 0.08f, false));
		Renderer->ChangeFrameAnimation("Chalice_Idle");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);

		GetTransform().SetLocalPosition({ 550, -900 , -1 });

		Renderer->AnimationBindEnd("Chalice_Idle_Shoot", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				StateManager.ChangeState("ChaliceIdle");
			});

		Collision = CreateComponent<GameEngineCollision>();
		// Collision3D
		//Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 10000.0f });

		// Collision2D
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
	}

	StateManager.CreateStateMember("ChaliceIdle", std::bind(&MsChalice::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::IdleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceRun", std::bind(&MsChalice::RunUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::RunStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("ChaliceJump", std::bind(&MsChalice::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::JumpStart, this, std::placeholders::_1));
	StateManager.ChangeState("ChaliceIdle");
}

void MsChalice::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);

	ColorCheck = ColRenderer->GetCurTexture();
	if (nullptr == ColorCheck)
	{
		return;
	}
	while (true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-GetTransform().GetLocalPosition().y)).CompareInt4D(float4::BLACK))
	{
		GetTransform().SetLocalMove(GetTransform().GetUpVector());
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

	MoveDir += GetTransform().GetDownVector() * _DeltaTime * 800.0f;
	GetTransform().SetLocalMove(MoveDir * _DeltaTime);

	// Collision3D
	/*Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		[](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			_Other->GetActor()->Death();
			return true;
		});*/

		// Collision2D
	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceShoot"))
	{
		CurShootName = "_Shoot";

		WeaponTime -= _DeltaTime;

		if (0.0f > WeaponTime)
		{
			WeaponPtr = GetLevel()->CreateActor<Weapon>(OBJECTORDER::Weapon);
			WeaponPtr->GetTransform().SetLocalPosition(float4(GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y + 50.0f, GetTransform().GetLocalPosition().z));
			WeaponPtr->SetWeaponDir(ChaliceDir);

			WeaponTime = 0.3f;
		}
	}

	if (true == GameEngineInput::GetInst()->IsUp("ChaliceShoot"))
	{
		CurShootName = "";
		WeaponTime = 0.0f;
	}

	Renderer->ChangeFrameAnimation(CurStateName + CurShootName);
}

void MsChalice::IdleStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Idle";
}

void MsChalice::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MoveDir = float4::ZERO;
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceRight")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		StateManager.ChangeState("ChaliceRun");
		return;
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
}

void MsChalice::RunStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Run";
}

void MsChalice::RunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MoveDir = float4::ZERO;
	if (false == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		&& false == GameEngineInput::GetInst()->IsPress("ChaliceRight")
		&& false == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("ChaliceJump"))
	{
		StateManager.ChangeState("ChaliceJump");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		MoveDir = GetTransform().GetLeftVector() * Speed;
		Renderer->GetTransform().PixLocalNegativeX();
		ChaliceDir = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		MoveDir = GetTransform().GetRightVector() * Speed;
		Renderer->GetTransform().PixLocalPositiveX();
		ChaliceDir = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		ChaliceDir = "LeftUp";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		ChaliceDir = "RightUp";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		//GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}
}

void MsChalice::JumpStart(const StateInfo& _Info)
{
	CurStateName = "Chalice_Jump_Regular";

	MoveDir = GetTransform().GetUpVector() * 600.0f;
}

void MsChalice::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		MoveDir = float4{ -Speed / 5.0f,MoveDir.y };
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		MoveDir = float4{ Speed / 5.0f,MoveDir.y };
	}

	if(true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-GetTransform().GetLocalPosition().y)).CompareInt4D(float4::BLACK))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}
}
