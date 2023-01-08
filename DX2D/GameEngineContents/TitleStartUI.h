#pragma once
#include "UIMaster.h"

// Ό³Έν :
class TitleStartUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleStartUI();
	~TitleStartUI();

	// delete Function
	TitleStartUI(const TitleStartUI& _Other) = delete;
	TitleStartUI(TitleStartUI&& _Other) noexcept = delete;
	TitleStartUI& operator=(const TitleStartUI& _Other) = delete;
	TitleStartUI& operator=(TitleStartUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() {}

private:
	void SelectIndex();
	void AnimPlayerIndex();

	GameEngineTextureRenderer* MainRenderer;
	
	GameEngineTextureRenderer* Renderer0;
	GameEngineTextureRenderer* Renderer1;
	GameEngineTextureRenderer* Renderer2;
	GameEngineTextureRenderer* NewGameRenderer0;
	GameEngineTextureRenderer* NewGameRenderer1;
	GameEngineTextureRenderer* NewGameRenderer2;
	GameEngineTextureRenderer* NewGameText;

	GameEngineTextureRenderer* SelectOnBackground;
	GameEngineTextureRenderer* SelectSlotColor;
	GameEngineTextureRenderer* SelectSlotText;
	GameEngineTextureRenderer* SelectCuphead;
	GameEngineTextureRenderer* SelectMugman;

	std::vector<float4>		SelectPosition;
	int						CurrentIndex;
	int						PlayerIndex;
	bool					FirstCheck;
	bool					SelectCheck;
	bool					AnimCheck;
};

