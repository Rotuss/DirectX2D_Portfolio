#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineTransformComponent.h"

enum class CAMERAPROJECTIONMODE
{
	PersPective,
	Orthographic,
};

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

	CAMERAPROJECTIONMODE GetProjectionMode()
	{
		return Mode;
	}

	void SetProjectionMode(CAMERAPROJECTIONMODE _Mode)
	{
		Mode = _Mode;
	}

	float4 GetScreenPosition();
	float4 GetMouseWorldPosition();
	float4 GetMouseWorldPositionToActor();

	inline float4 GetMouseWorldDir()
	{
		return MouseDir;
	}

protected:
	void Start();

private:
	float4x4 View;
	float4x4 ViewPort;
	float4x4 Projection;
	CAMERAPROJECTIONMODE Mode;

	float4 PrevMouse;
	float4 MouseDir;

	D3D11_VIEWPORT ViewPortDesc;

	float4 Size;
	float Near;
	float Far;

	float Fov;

	std::map<int, std::list<class GameEngineRenderer*>> AllRenderer_;

	void Render(float _DeltaTime);
	void PushRenderer(GameEngineRenderer* _Renderer);
	void Release(float _DelataTime);
	void Update(float _DeltaTime) override;
};

