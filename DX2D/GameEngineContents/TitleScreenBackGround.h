#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleScreenBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleScreenBackGround();
	~TitleScreenBackGround();

	// delete Function
	TitleScreenBackGround(const TitleScreenBackGround& _Other) = delete;
	TitleScreenBackGround(TitleScreenBackGround&& _Other) noexcept = delete;
	TitleScreenBackGround& operator=(const TitleScreenBackGround& _Other) = delete;
	TitleScreenBackGround& operator=(TitleScreenBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer*	Renderer;
};

