#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MortimerFreezeBlade : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeBlade();
	~MortimerFreezeBlade();

	// delete Function
	MortimerFreezeBlade(const MortimerFreezeBlade& _Other) = delete;
	MortimerFreezeBlade(MortimerFreezeBlade&& _Other) noexcept = delete;
	MortimerFreezeBlade& operator=(const MortimerFreezeBlade& _Other) = delete;
	MortimerFreezeBlade& operator=(MortimerFreezeBlade&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* BubbleRenderer;
};

