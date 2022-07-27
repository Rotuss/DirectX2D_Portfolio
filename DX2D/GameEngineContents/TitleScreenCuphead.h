#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class TitleScreenCuphead : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleScreenCuphead();
	~TitleScreenCuphead();

	// delete Function
	TitleScreenCuphead(const TitleScreenCuphead& _Other) = delete;
	TitleScreenCuphead(TitleScreenCuphead&& _Other) noexcept = delete;
	TitleScreenCuphead& operator=(const TitleScreenCuphead& _Other) = delete;
	TitleScreenCuphead& operator=(TitleScreenCuphead&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer*	Renderer;
	bool						ReverseEvent;

	void EndFunction(const FrameAnimation_DESC& _Info);
};

