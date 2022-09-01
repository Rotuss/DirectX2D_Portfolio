#include "PreCompile.h"
#include "MsChalice.h"
#include "Weapon.h"
#include "GlobalContents.h"
#include <iostream>

MsChalice* MsChalice::Chalice = nullptr;

MsChalice::MsChalice() 
	: Renderer(nullptr)
	, Speed(1000.0f)
	, ChaliceDir("Right")
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

		Renderer->CreateFrameAnimationFolder("Chalice_Idle", FrameAnimation_DESC("Chalice_Idle", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Run", FrameAnimation_DESC("Chalice_Run_Regular_Regular", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Chalice_Jump_Regular", FrameAnimation_DESC("Chalice_Jump_Regular_Jump", 0.1f, false));
		Renderer->CreateFrameAnimationFolder("Chalice_Shoot_Straight", FrameAnimation_DESC("Chalice_Shoot_Straight_Shoot", 0.1f, false));
		Renderer->ChangeFrameAnimation("Chalice_Idle");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);

		GetTransform().SetLocalPosition({ 550, -850 , -1 });
		
		Renderer->AnimationBindEnd("Chalice_Shoot_Straight", [/*&*/=](const FrameAnimation_DESC& _Info)
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
	StateManager.CreateStateMember("ChaliceShoot", std::bind(&MsChalice::ShootUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MsChalice::ShootStart, this, std::placeholders::_1));
	StateManager.ChangeState("ChaliceIdle");
}

void MsChalice::Update(float _DeltaTime)
{
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

	StateManager.Update(_DeltaTime);

	GetTransform().SetLocalMove(GetTransform().GetDownVector() * _DeltaTime * 200.0f);

	// Collision3D
	/*Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		[](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			_Other->GetActor()->Death();
			return true;
		});*/

	// Collision2D
	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D, std::bind(&MsChalice::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}

void MsChalice::IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Chalice_Idle");
}

void MsChalice::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceRight")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceUp")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		StateManager.ChangeState("ChaliceRun");
	}

	/*if (true == GameEngineInput::GetInst()->IsDown("ChaliceJump"))
	{
		StateManager.ChangeState("ChaliceJump");
	}*/

	if (true == GameEngineInput::GetInst()->IsDown("ChaliceShoot"))
	{
		StateManager.ChangeState("ChaliceShoot");
	}
}

void MsChalice::RunStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Chalice_Run");
}

void MsChalice::RunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		&& false == GameEngineInput::GetInst()->IsPress("ChaliceRight")
		&& false == GameEngineInput::GetInst()->IsPress("ChaliceUp")
		&& false == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}

	/*if (true == GameEngineInput::GetInst()->IsDown("ChaliceJump"))
	{
		StateManager.ChangeState("ChaliceJump");
	}*/

	/*if (true == GameEngineInput::GetInst()->IsDown("ChaliceShoot"))
	{
		StateManager.ChangeState("ChaliceShoot");
	}*/

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

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
		Renderer->GetTransform().PixLocalNegativeX();
		ChaliceDir = "Left";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
		Renderer->GetTransform().PixLocalPositiveX();
		ChaliceDir = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp"))
	{
		//GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
		ChaliceDir = "Up";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceLeft"))
	{
		//GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
		ChaliceDir = "LeftUp";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceUp") && true == GameEngineInput::GetInst()->IsPress("ChaliceRight"))
	{
		//GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
		ChaliceDir = "RightUp";
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		//GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}
}

void MsChalice::JumpStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Chalice_Jump_Regular");

	GetTransform().SetLocalMove(GetTransform().GetUpVector() * 200.0f * GameEngineTime::GetDeltaTime());
}

void MsChalice::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if(true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-(GetTransform().GetLocalPosition().y + 50.0f))).CompareInt4D(float4::BLACK))
	{
		StateManager.ChangeState("ChaliceIdle");
	}
}

void MsChalice::ShootStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Chalice_Shoot_Straight");
	
	WeaponPtr = GetLevel()->CreateActor<Weapon>(OBJECTORDER::Weapon);
	WeaponPtr->GetTransform().SetLocalPosition(float4(GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y + 50.0f, GetTransform().GetLocalPosition().z));
	WeaponPtr->SetWeaponDir(ChaliceDir);
}

void MsChalice::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{
	/*if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft")
		&& false == GameEngineInput::GetInst()->IsPress("PlayerRight")
		&& false == GameEngineInput::GetInst()->IsPress("PlayerUp")
		&& false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("ChaliceIdle");
		return;
	}*/

	if (true == GameEngineInput::GetInst()->IsPress("ChaliceLeft")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceRight")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceUp")
		|| true == GameEngineInput::GetInst()->IsPress("ChaliceDown"))
	{
		//StateManager.ChangeState("ChaliceMove");
	}
}
