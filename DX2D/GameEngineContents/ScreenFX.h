#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class ScreenFX : public GameEngineActor
{
public:
	// constrcuter destructer
	ScreenFX();
	~ScreenFX();

	// delete Function
	ScreenFX(const ScreenFX& _Other) = delete;
	ScreenFX(ScreenFX&& _Other) noexcept = delete;
	ScreenFX& operator=(const ScreenFX& _Other) = delete;
	ScreenFX& operator=(ScreenFX&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

