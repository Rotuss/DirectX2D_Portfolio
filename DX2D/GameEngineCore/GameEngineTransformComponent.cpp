#include "PreCompile.h"
#include "GameEngineTransformComponent.h"

GameEngineTransformComponent::GameEngineTransformComponent() 
{
}

GameEngineTransformComponent::~GameEngineTransformComponent() 
{
}

void GameEngineTransformComponent::DetachObject()
{
	GetTransform().DetachTransform();
}

void GameEngineTransformComponent::SetParent(GameEngineUpdateObject* _Object)
{
	GameEngineComponent::SetParent(_Object);

	{
		GameEngineTransformBase* Actor = nullptr;
		if (Actor = dynamic_cast<GameEngineTransformBase*>(_Object))
		{
			GetTransform().SetParentTransform(Actor->GetTransform());
			return;
		}
	}
}

