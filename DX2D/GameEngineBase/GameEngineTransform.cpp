#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform() 
	: Parent(nullptr)
	, LocalScale(float4::ONE)
	, LocalPosition(float4::ZERO)
	, LocalRotation(float4::ZERO)
{
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

void GameEngineTransform::PushChild(GameEngineTransform* _Child)
{
	_Child->Parent = this;
	Childs.push_back(_Child);
}

