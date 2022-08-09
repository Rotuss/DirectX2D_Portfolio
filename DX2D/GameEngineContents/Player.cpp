#include "PreCompile.h"
#include "Player.h"
#include "GlobalContents.h"
#include <iostream>

Player::Player() 
	: Renderer(nullptr)
	, Speed(1000.0f)
	, LRCheck(true)
{
}

Player::~Player() 
{
}

bool Player::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	_Other->GetActor()->Death();
	return true;
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_NUMPAD4);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_NUMPAD6);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_NUMPAD8);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_NUMPAD5);
		GameEngineInput::GetInst()->CreateKey("PlayerForward", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_NUMPAD2);
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		//Renderer->GetTransform().SetLocalScale({ 100, 100, 1 });
		Renderer->SetTexture("Cuphead_test.png");
		
		Renderer->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Chalice", 0, 0, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Chalice", 0.1f, true));
		Renderer->ChangeFrameAnimation("Idle");
		//Renderer->AnimationBindEnd("Move", &Player::TestFunction, this);
		//Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		Renderer->GetTransform().SetLocalScale({ 100, 100, 0 });
		//Renderer->GetTransform().SetLocalPosition({ 300, -1430 });

		Collision = CreateComponent<GameEngineCollision>();
		// Collision3D
		//Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 10000.0f });
		// Collision2D
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
	}

	GameEngineFontRenderer* Font = CreateComponent<GameEngineFontRenderer>();
	Font->SetText("Test", "µ¸¿ò");
	Font->SetColor({ 1.0f, 0.0f, 0.0f });
	Font->SetScreenPostion({ 100.0f, 100.0f });

	StateManager.CreateStateMember("Idle", std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Player::IdleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Move", std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, [/*&*/=](const StateInfo& _Info)
		{
			Renderer->ChangeFrameAnimation("Move");
		});
	StateManager.ChangeState("Idle");
}

void Player::Update(float _DeltaTime)
{
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f, 0.0f, 0.5f });
	
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
	
	StateManager.Update(_DeltaTime);

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);

	// Collision3D
	/*Collision->IsCollision(CollisionType::CT_OBB, OBJECTORDER::Monster, CollisionType::CT_OBB,
		[](GameEngineCollision* _This, GameEngineCollision* _Other)
		{
			_Other->GetActor()->Death();
			return true;
		});*/

	// Collision2D
	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Monster, CollisionType::CT_OBB2D, std::bind(&Player::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}

void Player::TestFunction(const FrameAnimation_DESC& _Info)
{
	if (true == LRCheck)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		//Renderer->GetTransform().PixLocalPositiveX();
		LRCheck = false;
	}
	else if (false == LRCheck)
	{
		//Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().PixLocalPositiveX();
		LRCheck = true;
	}
}

void Player::IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Idle");
}

void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft")
		|| true == GameEngineInput::GetInst()->IsPress("PlayerRight")
		|| true == GameEngineInput::GetInst()->IsPress("PlayerUp")
		|| true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Move");
	}
}

void Player::MoveStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("Move");
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsPress("PlayerLeft")
		&& false == GameEngineInput::GetInst()->IsPress("PlayerRight")
		&& false == GameEngineInput::GetInst()->IsPress("PlayerUp")
		&& false == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
		Renderer->GetTransform().PixLocalNegativeX();
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
		Renderer->GetTransform().PixLocalPositiveX();
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}
}

