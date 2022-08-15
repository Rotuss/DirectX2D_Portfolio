#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MortimerFreezeCard : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeCard();
	~MortimerFreezeCard();

	// delete Function
	MortimerFreezeCard(const MortimerFreezeCard& _Other) = delete;
	MortimerFreezeCard(MortimerFreezeCard&& _Other) noexcept = delete;
	MortimerFreezeCard& operator=(const MortimerFreezeCard& _Other) = delete;
	MortimerFreezeCard& operator=(MortimerFreezeCard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer*	Renderer;
	GameEngineCollision*		Collision;

private:
	float4 CurPosition;
	float4 PlayerPosition;
	float Speed;
};

