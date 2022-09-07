#include "PreCompile.h"
#include "Weapon.h"
#include "Player.h"

Weapon::Weapon() 
	: WeaponDir("Right")
{
}

Weapon::~Weapon() 
{
}

void Weapon::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Peashooter_Loop", FrameAnimation_DESC("Peashooter_Loop", 0.03f, false));
		Renderer->ChangeFrameAnimation("Peashooter_Loop");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::RIGHT);
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Weapon);
	}
}

void Weapon::Update(float _DeltaTime)
{
	if (-10.0f > GetTransform().GetLocalPosition().x)
	{
		Renderer->GetActor()->Death();
		return;
	}
	if (1650.0f < GetTransform().GetLocalPosition().x)
	{
		Renderer->GetActor()->Death();
		return;
	}
	
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

