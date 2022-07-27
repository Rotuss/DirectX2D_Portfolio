#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleScreenChalice : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleScreenChalice();
	~TitleScreenChalice();

	// delete Function
	TitleScreenChalice(const TitleScreenChalice& _Other) = delete;
	TitleScreenChalice(TitleScreenChalice&& _Other) noexcept = delete;
	TitleScreenChalice& operator=(const TitleScreenChalice& _Other) = delete;
	TitleScreenChalice& operator=(TitleScreenChalice&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer*	Renderer;
	bool						ReverseEvent;

	void EndFunction(const FrameAnimation_DESC& _Info);
};

