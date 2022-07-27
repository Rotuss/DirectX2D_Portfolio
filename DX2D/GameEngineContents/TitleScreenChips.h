#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleScreenChips : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleScreenChips();
	~TitleScreenChips();

	// delete Function
	TitleScreenChips(const TitleScreenChips& _Other) = delete;
	TitleScreenChips(TitleScreenChips&& _Other) noexcept = delete;
	TitleScreenChips& operator=(const TitleScreenChips& _Other) = delete;
	TitleScreenChips& operator=(TitleScreenChips&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer*	Renderer;
};

