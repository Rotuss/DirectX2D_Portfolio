#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "Weapon.h"
#include "UIHealth.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class MsChalice : public GameEngineActor
{
public:
	// constrcuter destructer
	MsChalice();
	~MsChalice();

	// delete Function
	MsChalice(const MsChalice& _Other) = delete;
	MsChalice(MsChalice&& _Other) noexcept = delete;
	MsChalice& operator=(const MsChalice& _Other) = delete;
	MsChalice& operator=(MsChalice&& _Other) noexcept = delete;

	static MsChalice* Chalice;

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionCheckParry(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionCheckMinion(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionCheckWhale(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionCheckPlatform(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionCheckPhase3Bot(GameEngineCollision* _This, GameEngineCollision* _Other);

	void SetColMap(GameEngineTextureRenderer* _Collision)
	{
		ColRenderer = _Collision;
	}

	inline void SetPlatformCount(int _Value)
	{
		PlatformCount = _Value;
	}

	inline int GetPlatformCount()
	{
		return PlatformCount;
	}

	GameEngineTextureRenderer* GetColMap()
	{
		return ColRenderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer*	Renderer;
	GameEngineTextureRenderer*	ColRenderer;
	GameEngineTexture*			ColorCheck;
	GameEngineCollision*		Collision;
	Weapon*						WeaponPtr;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void DuckStart(const StateInfo& _Info);
	void DuckUpdate(float _DeltaTime, const StateInfo& _Info);

	void RunStart(const StateInfo& _Info);
	void RunUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

	void DashStart(const StateInfo& _Info);
	void DashUpdate(float _DeltaTime, const StateInfo& _Info);

	void HitStart(const StateInfo& _Info);
	void HitUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager	StateManager;
	UIHealth* Health;
	std::string				ChaliceDir;
	std::string				ChalicePrevDir;
	std::string				CurStateName;
	std::string				CurShootName;

	float4					MoveDir;
	float4					AddDir;
	float					Speed;
	float					WeaponTime;
	float					NoDamageTime;
	int						ChaliceHP;
	int						PlatformCount;
};

