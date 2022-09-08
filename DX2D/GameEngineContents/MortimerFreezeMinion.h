#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class GENDER
{
	BOY,
	GIRL,
};

enum class DIR
{
	LEFT,
	RIGHT,
};

// Ό³Έν :
class MortimerFreezeMinion : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeMinion();
	~MortimerFreezeMinion();

	// delete Function
	MortimerFreezeMinion(const MortimerFreezeMinion& _Other) = delete;
	MortimerFreezeMinion(MortimerFreezeMinion&& _Other) noexcept = delete;
	MortimerFreezeMinion& operator=(const MortimerFreezeMinion& _Other) = delete;
	MortimerFreezeMinion& operator=(MortimerFreezeMinion&& _Other) noexcept = delete;

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool CollisionCheckWhale(GameEngineCollision* _This, GameEngineCollision* _Other);

	inline void SetGender(GENDER _Type)
	{
		GenderType = _Type;

		if (GenderType == GENDER::BOY && DirType == DIR::LEFT)
		{
			Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		}
		if (GenderType == GENDER::BOY && DirType == DIR::RIGHT)
		{
			Renderer->ChangeFrameAnimation("SpawnBoyAppear");
			Renderer->GetTransform().PixLocalNegativeX();
		}
		if (GenderType == GENDER::GIRL && DirType == DIR::LEFT)
		{
			Renderer->ChangeFrameAnimation("SpawnGirlAppear");
		}
		if (GenderType == GENDER::GIRL && DirType == DIR::RIGHT)
		{
			Renderer->ChangeFrameAnimation("SpawnGirlAppear");
			Renderer->GetTransform().PixLocalNegativeX();
		}

		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	inline void SetDir(DIR _Type)
	{
		DirType = _Type;
	}

	inline void SetMoveDir(int _Value)
	{
		MoveDir = _Value;
	}

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
	GameEngineTextureRenderer*	EffectRenderer;
	GameEngineCollision*		Collision;

private:
	GENDER	GenderType;
	DIR		DirType;

	float	Speed;
	bool	MinionMoveStart;
	bool	MinionFollowStart;
	bool	IsRanding;
	int		MoveDir;
};

