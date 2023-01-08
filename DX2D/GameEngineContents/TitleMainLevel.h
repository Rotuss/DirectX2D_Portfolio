#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class TitleMainLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleMainLevel();
	~TitleMainLevel();

	// delete Function
	TitleMainLevel(const TitleMainLevel& _Other) = delete;
	TitleMainLevel(TitleMainLevel&& _Other) noexcept = delete;
	TitleMainLevel& operator=(const TitleMainLevel& _Other) = delete;
	TitleMainLevel& operator=(TitleMainLevel&& _Other) noexcept = delete;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	inline void SetSelectUICheck(bool _Value)
	{
		SelectUICheck = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void SelectIndex();

	GameEngineTextureRenderer*	Renderer;
	GameEngineTextureRenderer*	SelectRenderer;
	std::vector<float4>			SelectPosition;
	int							CurrentIndex;
	bool						SelectUICheck;
};

