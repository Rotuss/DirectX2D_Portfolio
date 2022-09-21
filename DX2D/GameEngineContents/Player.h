#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "Weapon.h"

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	static Player* MainPlayer;

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

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

	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* ColRenderer;
	GameEngineTexture* ColorCheck;
	GameEngineCollision* Collision;
	Weapon* TestPtr;

	float4 Color;

	void TestFunction(const FrameAnimation_DESC& _Info);

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void MoveStart(const StateInfo& _Info);
	void MoveUpdate(float _DeltaTime, const StateInfo& _Info);

	void AttackStart(const StateInfo& _Info);
	void AttackUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager StateManager;
	
	std::string PlayerDir;
	float Speed;
	bool LRCheck;
};

