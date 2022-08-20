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

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer*	Renderer;
	GameEngineCollision*		Collision;

private:
	GENDER	GenderType;
	DIR		DirType;
};

