#pragma once
#include <GameEngineBase/GameEngineTransform.h>
#include "GameEngineComponent.h"

// 설명 : 기능. 기하정보까지 가지야하는 컴포넌트들은 이걸 상속
class GameEngineTransformComponent : public GameEngineComponent
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

	GameEngineTransform& GetTransform()
	{
		return Transform;
	}

protected:

private:
	GameEngineTransform Transform;
};

