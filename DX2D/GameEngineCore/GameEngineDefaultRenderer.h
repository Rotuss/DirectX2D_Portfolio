#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineShaderResourcesHelper.h"

// ���� :
class GameEngineRenderingPipeLine;
class GameEngineDefaultRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineDefaultRenderer();
	~GameEngineDefaultRenderer();

	// delete Function
	GameEngineDefaultRenderer(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer(GameEngineDefaultRenderer&& _Other) noexcept = delete;
	GameEngineDefaultRenderer& operator=(const GameEngineDefaultRenderer& _Other) = delete;
	GameEngineDefaultRenderer& operator=(GameEngineDefaultRenderer&& _Other) noexcept = delete;

	GameEngineRenderingPipeLine* GetPipeLine()
	{
		return PipeLine;
	}

	GameEngineShaderResourcesHelper ShaderResources;

	virtual void Render(float _DeltaTime);

	void SetPipeLine(const std::string& _Name);

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

private:
	GameEngineRenderingPipeLine* PipeLine;
};

