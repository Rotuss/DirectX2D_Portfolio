#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class EyePos
{
	LeftTop,
	LeftBot,
	RightTop,
	RightBot,
};

// ���� :
class MortimerFreezeEye : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeEye();
	~MortimerFreezeEye();

	// delete Function
	MortimerFreezeEye(const MortimerFreezeEye& _Other) = delete;
	MortimerFreezeEye(MortimerFreezeEye&& _Other) noexcept = delete;
	MortimerFreezeEye& operator=(const MortimerFreezeEye& _Other) = delete;
	MortimerFreezeEye& operator=(MortimerFreezeEye&& _Other) noexcept = delete;

	inline void SetEyePosition(EyePos _Pos)
	{
		EyePosition = _Pos;
	}

	inline void SetStartPosition(float4 _Value)
	{
		StartPosition = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* EffectRenderer00;
	GameEngineTextureRenderer* EffectRenderer01;
	GameEngineCollision* Collision;
	GameEngineCollision* LineCollision;

private:
	EyePos EyePosition;

	float4 LerpPos;
	float4 StartPosition;
	float4 EndPosition;
	float EyeLerpRatio;
	float XValue;
	float XAdd;
	float LineTime;
	int EyeMoveCount;
};

