#pragma once
#include <GameEngineBase/GameEngineTransform.h>
#include "GameEngineComponent.h"

// ���� : ���. ������������ �������ϴ� ������Ʈ���� �̰� ���
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

