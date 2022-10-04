#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class MoonDirType
{
	Left,
	Right,
};

enum class MoonMoveType
{
	TOP,
	MID,
	BOT,
};

// Ό³Έν :
class MortimerFreezeMoon : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeMoon();
	~MortimerFreezeMoon();

	// delete Function
	MortimerFreezeMoon(const MortimerFreezeMoon& _Other) = delete;
	MortimerFreezeMoon(MortimerFreezeMoon&& _Other) noexcept = delete;
	MortimerFreezeMoon& operator=(const MortimerFreezeMoon& _Other) = delete;
	MortimerFreezeMoon& operator=(MortimerFreezeMoon&& _Other) noexcept = delete;

	void MoonSetting(MoonDirType _DirType, MoonMoveType _MoveType);
	
	inline void SetStartPosition(float4 _Value)
	{
		StartPosition = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;

private:
	MoonDirType		MoonDir;
	MoonMoveType	MoonMove;

	float4			LerpPos;
	float4			StartPosition;
	float4			EndPosition;

	float			MoonLerpRatio;
};

