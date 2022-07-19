#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>

// Ό³Έν :
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void UserStart() = 0;
	virtual void UserUpdate() = 0;
	virtual void UserEnd() = 0;

private:

};

