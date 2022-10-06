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

	inline void SetColMap(GameEngineTextureRenderer* _Collision)
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

	GameEngineTexture*			ColorCheck;
	GameEngineTextureRenderer*	ColRenderer;
	GameEngineTextureRenderer*	Renderer;
	GameEngineTextureRenderer*	RendererEffect;
	GameEngineCollision*		Collision;
	GameEngineCollision*		CollisionParry;

private:
	GameEngineSoundPlayer RepeatSound;
	
	float4 CurPosition;
	float4 PlayerPosition;
	float Speed;
	float SoundRepeatTime;
	bool IsRanding;
};

