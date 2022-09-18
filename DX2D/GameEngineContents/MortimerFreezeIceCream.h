#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MortimerFreezeIceCream : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeIceCream();
	~MortimerFreezeIceCream();

	// delete Function
	MortimerFreezeIceCream(const MortimerFreezeIceCream& _Other) = delete;
	MortimerFreezeIceCream(MortimerFreezeIceCream&& _Other) noexcept = delete;
	MortimerFreezeIceCream& operator=(const MortimerFreezeIceCream& _Other) = delete;
	MortimerFreezeIceCream& operator=(MortimerFreezeIceCream&& _Other) noexcept = delete;

	inline void SetStartPosition(float4 _Value)
	{
		StartPosition = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;
	//GameEngineCollision* Collision;

private:
	float4 LerpPos;
	float4 StartPosition;
	float4 EndPosition;

	float IceCreamLerpRatio;
};

