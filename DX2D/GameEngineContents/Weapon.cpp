#include "PreCompile.h"
#include "Weapon.h"
#include "Player.h"

Weapon::Weapon() 
	: StartRenderer(nullptr)
	, Renderer(nullptr)
	, Collision(nullptr)
	, WeaponDir("Right")
	, StartPos(float4::ZERO)
{
}

Weapon::~Weapon() 
{
}

CollisionReturn Weapon::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Attacked();
	return CollisionReturn::ContinueCheck;
}

void Weapon::Attacked()
{
	Collision->Off();
	Renderer->ChangeFrameAnimation("Peashooter_Death");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Weapon::Start()
{
	{
		StartRenderer = CreateComponent<GameEngineTextureRenderer>();
		StartRenderer->CreateFrameAnimationFolder("Peashooter_Spark", FrameAnimation_DESC("Peashooter_Spark", 0.05f, false));
		StartRenderer->ChangeFrameAnimation("Peashooter_Spark");
		StartRenderer->SetScaleModeImage();
		StartRenderer->ScaleToTexture();
		StartRenderer->SetPivot(PIVOTMODE::CENTER);
	}
	
	StartRenderer->AnimationBindEnd("Peashooter_Spark", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StartRenderer->Off();
		});

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Peashooter_Loop", FrameAnimation_DESC("Peashooter_Loop", 0.03f, false));
		Renderer->CreateFrameAnimationFolder("Peashooter_Death", FrameAnimation_DESC("Peashooter_Death", 0.05f, false));
		Renderer->ChangeFrameAnimation("Peashooter_Loop");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::RIGHT);
	}

	Renderer->AnimationBindEnd("Peashooter_Death", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Weapon);
	}
}

void Weapon::Update(float _DeltaTime)
{
	if (true == StartRenderer->IsUpdate())
	{
		StartRenderer->GetTransform().SetWorldPosition(StartPos);
	}

	if (-10.0f > GetTransform().GetLocalPosition().x)
	{
		Death();
		return;
	}
	if (1650.0f < GetTransform().GetLocalPosition().x)
	{
		Death();
		return;
	}

	if (false == Collision->IsUpdate())
	{
		return;
	}

	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::BossWhale, CollisionType::CT_OBB2D, std::bind(&Weapon::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

	if ("Right" == WeaponDir)
	{
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetWorldRightMove(2000.0f, _DeltaTime);
	}
	if ("Left" == WeaponDir)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetWorldLeftMove(2000.0f, _DeltaTime);
	}
	if ("Up" == WeaponDir)
	{
		Renderer->GetTransform().SetLocalRotation(float4{ 0,0,90 });
		GetTransform().SetWorldUpMove(2000.0f, _DeltaTime);
	}
	if ("RightUp" == WeaponDir)
	{
		Renderer->GetTransform().SetLocalRotation(float4{ 0,0,45 });
		GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + ((GetTransform().GetRightVector() + GetTransform().GetUpVector()) * 1000.0f * _DeltaTime));
	}
	if ("LeftUp" == WeaponDir)
	{
		Renderer->GetTransform().SetLocalRotation(float4{ 0,0,135 });
		GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + ((GetTransform().GetLeftVector() + GetTransform().GetUpVector()) * 1000.0f * _DeltaTime));
	}

	//GetTransform().SetWorldRightMove(200.0f, _DeltaTime);
	//GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + ((GetTransform().GetRightVector()+ GetTransform().GetUpVector()) * 200 * _DeltaTime));
}

