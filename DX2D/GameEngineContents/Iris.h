#pragma once
#include <GameEngineCore/CoreMinimal.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer* Renderer;
};

