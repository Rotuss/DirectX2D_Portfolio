#include "PreCompile.h"
#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent(nullptr)
	, LocalScale(float4::ONE)
	, LocalRotation(float4::ZERO)
	, LocalPosition(float4::ZERO)
	, WorldScale(float4::ONE)
	, WorldRotation(float4::ZERO)
	, WorldPosition(float4::ZERO)
	, CollisionDataObject()
{
	CollisionDataSetting();
}

GameEngineTransform::~GameEngineTransform() 
{
}

void GameEngineTransform::CalculateWorld()
{
	LocalWorldMat = LocalScaleMat * LocalRotateMat * LocalPositionMat;

	if (nullptr != Parent)
	{
		WorldWorldMat = LocalWorldMat * Parent->GetWorldWorld();
	}
	else
	{
		WorldWorldMat = LocalWorldMat;
	}

	for (GameEngineTransform* Child : Childs)
	{
		Child->CalculateWorld();
	}
}

void GameEngineTransform::CalculateWorldViewProjection()
{
	WorldViewMat = WorldWorldMat * View;
	WorldViewProjectMat = WorldViewMat * Projection;
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

	SetLocalScale(LocalScale);
	SetLocalRotation(LocalRotation);
	SetLocalPosition(LocalPosition);
}

