#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class AnimType
{
	Front,
	Back,
};

// Ό³Έν :
class GameEngineTextureRenderer;
class Iris : public GameEngineActor
{
public:
	// constrcuter destructer
	Iris();
	~Iris();

	// delete Function
	Iris(const Iris& _Other) = delete;
	Iris(Iris&& _Other) noexcept = delete;
	Iris& operator=(const Iris& _Other) = delete;
	Iris& operator=(Iris&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}

	inline void SetAnimType(AnimType _Type)
	{
		CurAnimationType = _Type;

		switch (CurAnimationType)
		{
		case AnimType::Front:
			Renderer->ChangeFrameAnimation("IrisFX");
			break;
		case AnimType::Back:
			Renderer->ChangeFrameAnimation("IrisFXRev");
			break;
		default:
			break;
		}
		Renderer->GetTransform().SetLocalScale({ 1280, 720, -300 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
		Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);

	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer* Renderer;
	AnimType CurAnimationType;
};

