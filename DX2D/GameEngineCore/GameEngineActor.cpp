#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"

GameEngineActor::GameEngineActor() 
	: ParentLevel(nullptr)
	, IsLevelOver(false)
{
}

GameEngineActor::~GameEngineActor() 
{
}

void GameEngineActor::DetachObject()
{
	GameEngineUpdateObject::DetachObject();

	GetTransform().DetachTransform();
}

void GameEngineActor::SetParent(GameEngineUpdateObject* _Object)
{
	if (nullptr == GetParent())
	{
		GetLevel()->RemoveActor(this);
	}
	
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

void GameEngineActor::ActorUpdate(float _DeltaTime)
{
}

void GameEngineActor::Start()
{
}

void GameEngineActor::Update(float _DeltaTime)
{
}

void GameEngineActor::End()
{
}


