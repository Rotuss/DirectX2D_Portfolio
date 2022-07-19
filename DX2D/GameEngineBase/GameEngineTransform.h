#pragma once
#include "GameEngineMath.h"

// Ό³Έν :
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

protected:

private:
	float4 Scale;
	float4 Rotation;
	float4 Position;

public:
	inline void SetScale(const float4& _Value)
	{
		Scale = _Value;
	}
	inline void SetRotation(const float4& _Value)
	{
		Rotation = _Value;
	}
	inline void SetPosition(const float4& _Value)
	{
		Position = _Value;
	}
	inline void SetMove(const float4& _Value)
	{
		Position += _Value;
	}

	inline float4 GetScale() const
	{
		return Scale;
	}
	inline float4 GetRotation() const
	{
		return Rotation;
	}
	inline float4 GetPosition() const
	{
		return Position;
	}
};

