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

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	inline void MinionPixStateSwitch(bool _Value)
	{
		MinionPixCheck = _Value;
	}

	inline void MinionPixRemoveSetting(bool _Value)
	{
		MinionPixRemove = _Value;
	}

	inline void SetBucketMove(bool _Value)
	{
		IsBucketMove = _Value;
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
	GameEngineTextureRenderer*	AddRenderer;
	GameEngineTextureRenderer*	AddRenderer01;
	GameEngineTextureRenderer*	SubRenderer00;
	GameEngineTextureRenderer*	SubRenderer01;
	GameEngineTextureRenderer*	SubRenderer02;
	GameEngineTextureRenderer*	SubRenderer03;
	GameEngineCollision*		Collision;
	GameEngineCollision*		WhaleCollision;
	MortimerFreezeMinion*		Minion0;
	MortimerFreezeMinion*		Minion1;
	MortimerFreezeMinion*		Minion2;
	MortimerFreezeMinion*		Minion3;

	// Phase1
	void Phase1Start(const StateInfo& _Info);
	void Phase1Update(float _DeltaTime, const StateInfo& _Info);

	void P1IntroStart(const StateInfo& _Info);
	void P1IntroUpdate(float _DeltaTime, const StateInfo& _Info);

	void P1IdleStart(const StateInfo& _Info);
	void P1IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackPeashotStart(const StateInfo& _Info);
	void AttackPeashotUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackQuadshotStart(const StateInfo& _Info);
	void AttackQuadshotUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackWhaleStart(const StateInfo& _Info);
	void AttackWhaleUpdate(float _DeltaTime, const StateInfo& _Info);

	void Phase1to2Start(const StateInfo& _Info);
	void Phase1to2Update(float _DeltaTime, const StateInfo& _Info);

	// Phase2
	void Phase2Start(const StateInfo& _Info);
	void Phase2Update(float _DeltaTime, const StateInfo& _Info);

	void P2IdleStart(const StateInfo& _Info);
	void P2IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackDashStart(const StateInfo& _Info);
	void AttackDashUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackFridgeStart(const StateInfo& _Info);
	void AttackFridgeUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackSmashStart(const StateInfo& _Info);
	void AttackSmashUpdate(float _DeltaTime, const StateInfo& _Info);

	void Phase2to3Start(const StateInfo& _Info);
	void Phase2to3Update(float _DeltaTime, const StateInfo& _Info);

	// Phase3
	void Phase3Start(const StateInfo& _Info);
	void Phase3Update(float _DeltaTime, const StateInfo& _Info);

	void P3IntroStart(const StateInfo& _Info);
	void P3IntroUpdate(float _DeltaTime, const StateInfo& _Info);
	void P3IntroEnd(const StateInfo& _Info);

	void P3IdleStart(const StateInfo& _Info);
	void P3IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void P3SwapStart(const StateInfo& _Info);
	void P3SwapUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackEyeStart(const StateInfo& _Info);
	void AttackEyeUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackIceCreamStart(const StateInfo& _Info);
	void AttackIceCreamUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackSplitStart(const StateInfo& _Info);
	void AttackSplitUpdate(float _DeltaTime, const StateInfo& _Info);

	void Phase3KnockOutStart(const StateInfo& _Info);
	void Phase3KnockOutUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager PhaseManager;
	GameEngineStateManager StateManager;
	GameEngineStateManager StateManager2;
	GameEngineStateManager StateManager3;

	MFBossDIR CurMFDir;
	MFBossDIR CurMeltingDir;

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
	int		WhaleStateCount;
	int		Phase2TransitionMotionCount;
	int		SnowBeastIntroCount;
	bool	IsP1IdleStart;
	bool	MFMoveReplay;
	bool	IsCurRStartPos;
	bool	IsCurPeashotLStartPos;
	bool	IsCurPeashotStartAttack;
	bool	IsCurPeashotEnd;
	bool	IsIdleTransState;
	bool	MinionPixCheck;
	bool	MinionPixRemove;
	bool	IsEndPhase1;
	bool	IsSnowBeastIntroStartEnd;
	bool	IsSnowBeastIntroMoveDown;

	// Phase2
	float	DashTime;
	float	FridgeTime;
	float	SmashTime;
	float	IceTime;
	float	BladeTime;
	float	PlatformTime;
	int		PrevSkill;
	int		DashMove;
	int		IceCubeCount;
	int		IceBatCount;
	int		BladeCount;
	int		Phase3TransitionMotionCount;
	int		PlatformCount;
	int		LegCount;
	bool	IsDashPatternBegin;
	bool	IsPreparing;
	bool	IsPrevDash;
	bool	IsPrevJump;
	bool	IsJump;
	bool	IsShoot;
	bool	IsBatOpen;
	bool	IsPlatformOn;
	bool	IsLegMove;

	// Phase3
	float	EyeTime;
	float	IceCreamTime;
	float	SplitTime;
	float	IceCreamAppearTime;
	float	BucketAppearTime;
	int		SwapCount;
	int		EyeRepeatCount;
	int		IceCreamRandom;
	int		IceCreamCount;
	int		BucketCount;
	bool	IsPh3DownMove;
	bool	IsPh3XMove;
	bool	IsReverse;
	bool	IsSwapA;
	bool	IsIceCreamPatternEnd;
	bool	IsBucketMove;
	std::string PrevState;
};

