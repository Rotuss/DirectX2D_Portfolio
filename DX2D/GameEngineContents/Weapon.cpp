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
		Renderer->GetTransform().SetLocalScale({ 50, 50, 1 });
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Weapon);
	}
}

void Weapon::Update(float _DeltaTime)
{
	if ("Right" == WeaponDir)
	{
		GetTransform().SetWorldRightMove(200.0f, _DeltaTime);
	}
	if ("Left" == WeaponDir)
	{
		GetTransform().SetWorldLeftMove(200.0f, _DeltaTime);
	}
	if ("Up" == WeaponDir)
	{
		GetTransform().SetWorldUpMove(200.0f, _DeltaTime);
	}
	if ("RightUp" == WeaponDir)
	{
		GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + ((GetTransform().GetRightVector() + GetTransform().GetUpVector()) * 200 * _DeltaTime));
	}
	if ("LeftUp" == WeaponDir)
	{
		GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + ((GetTransform().GetLeftVector() + GetTransform().GetUpVector()) * 200 * _DeltaTime));
	}

	//GetTransform().SetWorldRightMove(200.0f, _DeltaTime);
	//GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + ((GetTransform().GetRightVector()+ GetTransform().GetUpVector()) * 200 * _DeltaTime));
}

