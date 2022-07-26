#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent(nullptr)
	, CollisionDataObject()
{
	CollisionDataSetting();
}

GameEngineTransform::~GameEngineTransform() 
{
}

void GameEngineTransform::CalculateWorld()
{
	Data.LocalWorldMatrix = Data.LocalScalingMatrix * Data.LocalRotationMatrix * Data.LocalPositionMatrix;

	if (nullptr != Parent)
	{
		Data.WorldWorldMatrix = Data.LocalWorldMatrix * Parent->GetWorldWorld();
	}
	else
	{
		Data.WorldWorldMatrix = Data.LocalWorldMatrix;
	}

	for (GameEngineTransform* Child : Childs)
	{
		Child->CalculateWorld();
	}
}

void GameEngineTransform::CalculateWorldViewProjection()
{
	Data.WorldViewMatrix = Data.WorldWorldMatrix * Data.ViewMatrix;
	Data.WorldViewProjectionMatrix = Data.WorldViewMatrix * Data.ProjectionMatrix;
}

void GameEngineTransform::DetachTransform()
{
	if (nullptr == Parent)
	{
		return;
	}

	Parent->Childs.remove(this);
	Parent = nullptr;
}

void GameEngineTransform::SetParentTransform(GameEngineTransform& _Parent)
{
	if (nullptr != Parent)
	{
		Parent->Childs.remove(this);
		Parent = nullptr;
	}

	Parent = &_Parent;
	_Parent.Childs.push_back(this);

	SetLocalScale(Data.LocalScaling);
	SetLocalRotation(Data.LocalRotation);
	SetLocalPosition(Data.LocalPosition);
}

void GameEngineTransform::PixLocalNegativeX()
{
	if (0.0f > Data.LocalScaling.x)
	{
		return;
	}

	Data.LocalScaling.x = -Data.LocalScaling.x;

	SetLocalScale(Data.LocalScaling);
}

void GameEngineTransform::PixLocalPositiveX()
{
	if (0.0f < Data.LocalScaling.x)
	{
		return;
	}

	Data.LocalScaling.x = abs(Data.LocalScaling.x);

	SetLocalScale(Data.LocalScaling);
}

void GameEngineTransform::Copy(GameEngineTransform& _Trans)
{
	Data = _Trans.Data;
	CollisionDataObject = _Trans.CollisionDataObject;
	Parent = _Trans.Parent;
	Childs = _Trans.Childs;

	CalculateWorldRotation(Data.LocalRotation);
	CalculateWorldScale(Data.LocalScaling);
	CalculateWorldPosition(Data.LocalPosition);
	CalculateWorld();
}

