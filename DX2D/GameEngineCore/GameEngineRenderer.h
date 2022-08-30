#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

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

	inline int GetRenderingOrder()
	{
		return RenderingOrder;
	}

	void SetRenderingOrder(int _Order);

	void ChangeCamera(CAMERAORDER _Order);

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

	void PushRendererToMainCamera();
	void PushRendererToUICamera();

	class GameEngineCamera* Camera;
	CAMERAORDER CameraOrder;
	int RenderingOrder;

private:
	virtual void Render(float _DeltaTime) = 0;
};

