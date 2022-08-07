#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MortimerFreezeLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MortimerFreezeLevel();
	~MortimerFreezeLevel();

	// delete Function
	MortimerFreezeLevel(const MortimerFreezeLevel& _Other) = delete;
	MortimerFreezeLevel(MortimerFreezeLevel&& _Other) noexcept = delete;
	MortimerFreezeLevel& operator=(const MortimerFreezeLevel& _Other) = delete;
	MortimerFreezeLevel& operator=(MortimerFreezeLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
};

