#pragma once
#include <GameEngineBase/GameEngineTransform.h>
#include <GameEngineCore/GameEngineActor.h>
#include "GameEngineTransformBase.h"
#include "GameEngineComponent.h"

// 설명 : 기능. 기하정보까지 가지야하는 컴포넌트들은 이걸 상속
class GameEngineTransformComponent 
	: public GameEngineComponent
	, public GameEngineTransformBase
{
public:
	// constrcuter destructer
	GameEngineTransformComponent();
	~GameEngineTransformComponent();

	// delete Function
	GameEngineTransformComponent(const GameEngineTransformComponent& _Other) = delete;
	GameEngineTransformComponent(GameEngineTransformComponent&& _Other) noexcept = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _Other) = delete;
	GameEngineTransformComponent& operator=(GameEngineTransformComponent&& _Other) noexcept = delete;

	GameEngineActor* GetActor()
	{
		return GetParent<GameEngineActor>();
	}

	template<typename ParentType>
	ParentType* GetActor()
	{
		return GetParent<ParentType>();
	}

	void DetachObject() override;
	void SetParent(GameEngineUpdateObject* _Object) override;

protected:

private:
	
};

