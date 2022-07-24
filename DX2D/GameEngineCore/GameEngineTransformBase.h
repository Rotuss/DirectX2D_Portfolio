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

	const TransformData& GetTransformData()
	{
		return Transform.GetTransformData();
	}

protected:

private:
	GameEngineTransform Transform;
};

