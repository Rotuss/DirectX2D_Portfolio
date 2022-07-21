#pragma once
#include <GameEngineBase/GameEngineTransform.h>

// Ό³Έν :
class GameEngineTransformBase
{
public:
	// constrcuter destructer
	GameEngineTransformBase();
	virtual ~GameEngineTransformBase();

	// delete Function
	GameEngineTransformBase(const GameEngineTransformBase& _Other) = delete;
	GameEngineTransformBase(GameEngineTransformBase&& _Other) noexcept = delete;
	GameEngineTransformBase& operator=(const GameEngineTransformBase& _Other) = delete;
	GameEngineTransformBase& operator=(GameEngineTransformBase&& _Other) noexcept = delete;

	GameEngineTransform& GetTransform()
	{
		return Transform;
	}

protected:

private:
	GameEngineTransform Transform;
};

