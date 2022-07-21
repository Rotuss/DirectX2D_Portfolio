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

	MsgBoxAssert("Ʈ�������� �ִ� ������Ʈ�� Ʈ�������� ���� �θ� ���̷��� �߽��ϴ�.");
}

