#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class BucketDirType
{
	Left,
	Right,
};

enum class BucketMoveType
{
	TOP,
	MID,
	BOT,
};

// Ό³Έν :
class MortimerFreezeBucket : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeBucket();
	~MortimerFreezeBucket();

	// delete Function
	MortimerFreezeBucket(const MortimerFreezeBucket& _Other) = delete;
	MortimerFreezeBucket(MortimerFreezeBucket&& _Other) noexcept = delete;
	MortimerFreezeBucket& operator=(const MortimerFreezeBucket& _Other) = delete;
	MortimerFreezeBucket& operator=(MortimerFreezeBucket&& _Other) noexcept = delete;

	void BucketSetting(BucketDirType _DirType, BucketMoveType _MoveType);

	inline void SetStartPosition(float4 _Value)
	{
		StartPosition = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer*	Renderer;
	GameEngineCollision*		Collision;
	GameEngineCollision*		CollisionParry;

private:
	BucketDirType BucketDir;
	BucketMoveType BucketMove;

	float4 LerpPos;
	float4 StartPosition;
	float4 EndPosition;

	float BucketLerpRatio;
	bool IsBucketMove;
};

