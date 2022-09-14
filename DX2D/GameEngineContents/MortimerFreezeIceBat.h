#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class ColorType
{
	Green,
	Pink,
	Yellow,
};

enum class BatDIR
{
	LEFT,
	RIGHT,
};

// Ό³Έν :
class MortimerFreezeIceBat : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeIceBat();
	~MortimerFreezeIceBat();

	// delete Function
	MortimerFreezeIceBat(const MortimerFreezeIceBat& _Other) = delete;
	MortimerFreezeIceBat(MortimerFreezeIceBat&& _Other) noexcept = delete;
	MortimerFreezeIceBat& operator=(const MortimerFreezeIceBat& _Other) = delete;
	MortimerFreezeIceBat& operator=(MortimerFreezeIceBat&& _Other) noexcept = delete;

	inline void SetMovePos(float4 _Start, float4 _End)
	{
		StartPosition = _Start;
		EndPosition = _End;

		if (StartPosition.x < EndPosition.x)
		{
			CurBatDir = BatDIR::RIGHT;
		}
		else
		{
			CurBatDir = BatDIR::LEFT;
		}
	}

	inline void SetReAppearTime(float _Value)
	{
		ReAppearTime = _Value;
	}

	void SetColorType(ColorType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;

private:
	ColorType BatColor;
	BatDIR CurBatDir;
	
	float4 StartPosition;
	float4 EndPosition;
	float4 LerpPos;
	float BatLerpRatio;
	float YValue;
	float YAdd;
	float ReAppearTime;
	bool IsYOut;
};

