#pragma once

// Ό³Έν :
class StoryLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	StoryLevel();
	~StoryLevel();

	// delete Function
	StoryLevel(const StoryLevel& _Other) = delete;
	StoryLevel(StoryLevel&& _Other) noexcept = delete;
	StoryLevel& operator=(const StoryLevel& _Other) = delete;
	StoryLevel& operator=(StoryLevel&& _Other) noexcept = delete;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineSoundPlayer StorySound;

};

