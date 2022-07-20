#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineTransformComponent.h"

// Ό³Έν :
class GameEngineLevel;
class GameEngineCamera;
class GameEngineCamera : public GameEngineTransformComponent
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

protected:
	void Start();

private:
	float4x4 View;
	float4x4 Projection;

	std::map<int, std::list<class GameEngineRenderer*>> AllRenderer_;

	void Render(float _DeltaTime);
	void PushRenderer(GameEngineRenderer* _Renderer);
};

