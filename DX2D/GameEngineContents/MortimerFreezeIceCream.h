#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class NumType
{
	Num0,
	Num1,
	Num2,
	Num3,
};

enum class PosType
{
	Pos0,
	Pos1,
	Pos2,
};

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

	void SetNumType(NumType _Type);

	inline void SetPosType(PosType _Type)
	{
		CurPosType = _Type;
	}

	inline void SetIceCreamMoveTime(float _Value)
	{
		IceCreamMoveTime = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* EffectRenderer;
	//GameEngineCollision* Collision;

private:
	NumType CurNumType;
	PosType CurPosType;

	float4 LerpPos;
	float4 StartPosition;
	float4 EndPosition;

	float IceCreamLerpRatio;
	float IceCreamMoveTime;
};

