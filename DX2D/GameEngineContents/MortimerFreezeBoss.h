#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class MFBossDIR
{
	LEFT,
	RIGHT,
};

// Ό³Έν :
//class GameEngineCollision;
class MortimerFreezeMinion;
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

	inline void MinionPixStateSwitch(bool _Value)
	{
		MinionPixCheck = _Value;
	}

	inline void MinionPixRemoveSetting(bool _Value)
	{
		MinionPixRemove = _Value;
	}

	inline bool MinionPixRemoveReturn()
	{
		return MinionPixRemove;
	}

	inline bool GetIsCurPeashotEnd()
	{
		return IsCurPeashotEnd;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer*	Renderer;
	GameEngineTextureRenderer*	TableRenderer;
	GameEngineCollision*		Collision;
	MortimerFreezeMinion*		Minion0;
	MortimerFreezeMinion*		Minion1;
	MortimerFreezeMinion*		Minion2;
	MortimerFreezeMinion*		Minion3;

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

	MFBossDIR CurMFDir;

	std::vector<float4> StartPos;
	std::vector<float4> EndPos;
	float4 LerpPos;
	float	Speed;
	float	YAdd;
	float	IdleLerpRatio;
	float	PeashotAttackMoveTime;
	int		Num;
	int		HP;
	int		PeashotStateCount;
	int		PeashotAttackCount;
	int		QuadshotStateCount;
	bool	IsP1IdleStart;
	bool	MFMoveReplay;
	bool	IsCurRStartPos;
	bool	IsCurPeashotLStartPos;
	bool	IsCurPeashotStartAttack;
	bool	IsCurPeashotEnd;
	bool	IsIdleTransState;
	bool	MinionPixCheck;
	bool	MinionPixRemove;
};

