#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class PlatformType
{
	Intro,
	TypeA,
	TypeB,
	TypeC,
	TypeD,
	TypeE,
};

// Ό³Έν :
class MortimerFreezeSnowPlatform : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeSnowPlatform();
	~MortimerFreezeSnowPlatform();

	// delete Function
	MortimerFreezeSnowPlatform(const MortimerFreezeSnowPlatform& _Other) = delete;
	MortimerFreezeSnowPlatform(MortimerFreezeSnowPlatform&& _Other) noexcept = delete;
	MortimerFreezeSnowPlatform& operator=(const MortimerFreezeSnowPlatform& _Other) = delete;
	MortimerFreezeSnowPlatform& operator=(MortimerFreezeSnowPlatform&& _Other) noexcept = delete;

	void SetPlatformType(PlatformType _Type);
	inline void SetFollowObj(GameEngineTransform* _Obj)
	{
		FollowObj = _Obj;
	}

	float4 GetMovePos();

	int Index;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;
	GameEngineCollision* Collision;

private:
	PlatformType CurPlatformType;
	GameEngineTransform* FollowObj;

	float4 PrevPosition;
	float4 CurPosition;
};

