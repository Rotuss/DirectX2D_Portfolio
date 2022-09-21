#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

struct RenderOption
{
	float	DeltaTime;
	float	SumDeltaTime = 0.0f;
	int		IsMask;
	int		IsJump;
	int		Option00;
	int		Option01;
};

// Ό³Έν :
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	GameEngineRenderingPipeLine* GetClonePipeLine(GameEngineRenderingPipeLine* _Rendering);
	RenderOption RenderOption;

	inline int GetRenderingOrder()
	{
		return RenderingOrder;
	}

	void SetRenderingOrder(int _Order);

	void ChangeCamera(CAMERAORDER _Order);

	virtual void InstancingOn()
	{
		IsInstancing = true;
	};

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

	void PushRendererToMainCamera();
	void PushRendererToUICamera();

	class GameEngineCamera* Camera;
	CAMERAORDER CameraOrder;
	int RenderingOrder;
	bool IsInstancing;

private:
	virtual void Render(float _DeltaTime) = 0;
};

