#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class SizeType
{
	Large,
	Medium,
	Small,
};

enum class CubeDIR
{
	LEFT,
	RIGHT,
};

// Ό³Έν :
class MortimerFreezeIceCube : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeIceCube();
	~MortimerFreezeIceCube();

	// delete Function
	MortimerFreezeIceCube(const MortimerFreezeIceCube& _Other) = delete;
	MortimerFreezeIceCube(MortimerFreezeIceCube&& _Other) noexcept = delete;
	MortimerFreezeIceCube& operator=(const MortimerFreezeIceCube& _Other) = delete;
	MortimerFreezeIceCube& operator=(MortimerFreezeIceCube&& _Other) noexcept = delete;

	inline void SetColMap(GameEngineTextureRenderer* _Collision)
	{
		ColRenderer = _Collision;
	}

	inline void SetMovePos(float4 _Start, float4 _End)
	{
		StartPosition = _Start;
		EndPosition = _End;

		if (StartPosition.x < EndPosition.x)
		{
			DirType = CubeDIR::RIGHT;
		}
		else
		{
			DirType = CubeDIR::LEFT;
		}
	}

	void SetSizeType(SizeType _Type);

	GameEngineTextureRenderer* GetColMap()
	{
		return ColRenderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTexture* ColorCheck;
	GameEngineTextureRenderer* ColRenderer;
	GameEngineTextureRenderer* Renderer;

private:
	SizeType CubeSize;
	CubeDIR	DirType;

	float4 StartPosition;
	float4 EndPosition;
	float4 LerpPos;
	float CubeLerpRatio;
	float YAdd;
};

