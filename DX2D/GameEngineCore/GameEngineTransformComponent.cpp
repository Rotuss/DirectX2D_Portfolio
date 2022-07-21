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
	GameEngineUpdateObject::DetachObject();
	GetTransform().DetachTransform();
}

void GameEngineTransformComponent::SetParent(GameEngineUpdateObject* _Object)
{
	GameEngineUpdateObject::SetParent(_Object);
	{
		GameEngineTransformBase* Actor = nullptr;
		if (Actor = dynamic_cast<GameEngineTransformBase*>(_Object))
		{
			GetTransform().SetParentTransform(Actor->GetTransform());
			return;
		}
	}

	MsgBoxAssert("트랜스폼이 있는 컴포넌트에 트랜스폼이 없는 부모를 붙이려고 했습니다.");
}

