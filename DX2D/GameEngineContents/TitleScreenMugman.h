#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleScreenMugman : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleScreenMugman();
	~TitleScreenMugman();

	// delete Function
	TitleScreenMugman(const TitleScreenMugman& _Other) = delete;
	TitleScreenMugman(TitleScreenMugman&& _Other) noexcept = delete;
	TitleScreenMugman& operator=(const TitleScreenMugman& _Other) = delete;
	TitleScreenMugman& operator=(TitleScreenMugman&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer*	Renderer;
};

