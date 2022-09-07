#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "Weapon.h"

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

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	void SetColMap(GameEngineTextureRenderer* _Collision)
	{
		ColRenderer = _Collision;
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

	float4 Color;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void DuckStart(const StateInfo& _Info);
	void DuckUpdate(float _DeltaTime, const StateInfo& _Info);

	void RunStart(const StateInfo& _Info);
	void RunUpdate(float _DeltaTime, const StateInfo& _Info);

	void JumpStart(const StateInfo& _Info);
	void JumpUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager	StateManager;

	std::string				ChaliceDir;
	std::string				ChalicePrevDir;
	std::string				CurStateName;
	std::string				CurShootName;

	float4					MoveDir;
	float					Speed;
	float					WeaponTime;
};

