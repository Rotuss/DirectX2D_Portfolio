#pragma once
#include <GameEngineCore/CoreMinimal.h>

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

	static MortimerFreezeBoss* MFBoss;

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer*	Renderer;
	GameEngineTextureRenderer*	TableRenderer;
	GameEngineCollision*		Collision;

	void Phase1Start(const StateInfo& _Info);
	void Phase1Update(float _DeltaTime, const StateInfo& _Info);

	void P1IdleStart(const StateInfo& _Info);
	void P1IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackPeashotStart(const StateInfo& _Info);
	void AttackPeashotUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackQuadshotStart(const StateInfo& _Info);
	void AttackQuadshotUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackWhaleStart(const StateInfo& _Info);
	void AttackWhaleUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager PhaseManager;
	GameEngineStateManager StateManager;

	std::vector<float4> StartPos;
	std::vector<float4> EndPos;
	float4 LerpPos;
	float	Speed;
	float	YAdd;
	int		HP;
};

