#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class MFDir
{
	LEFT,
	RIGHT,
};

// Ό³Έν :
//class GameEngineCollision;
class GameEngineTextureRenderer;
class MortimerFreezeBoss : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeBoss();
	~MortimerFreezeBoss();

	// delete Function
	MortimerFreezeBoss(const MortimerFreezeBoss& _Other) = delete;
	MortimerFreezeBoss(MortimerFreezeBoss&& _Other) noexcept = delete;
	MortimerFreezeBoss& operator=(const MortimerFreezeBoss& _Other) = delete;
	MortimerFreezeBoss& operator=(MortimerFreezeBoss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager StateManager;

	MFDir	CurrentDir;
	float4	Dir;
	float	Speed;
};

