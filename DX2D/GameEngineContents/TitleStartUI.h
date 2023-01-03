#pragma once
#include "UIMaster.h"
#include "TitleMainLevel.h"

// Ό³Έν :
class TitleStartUI : public UIMaster
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
	
	TitleMainLevel*			TMLevel;
	
	GameEngineUIRenderer*	Renderer0;
	GameEngineUIRenderer*	Renderer1;
	GameEngineUIRenderer*	Renderer2;
	GameEngineUIRenderer*	NewGameRenderer0;
	GameEngineUIRenderer*	NewGameRenderer1;
	GameEngineUIRenderer*	NewGameRenderer2;

	GameEngineUIRenderer*	SelectOnBackground;
	GameEngineUIRenderer*	SelectSlotColor;
	GameEngineUIRenderer*	SelectSlotText;

	std::vector<float4>		SelectPosition;
	int						CurrentIndex;
};

