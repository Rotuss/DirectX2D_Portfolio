#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class HourGlass : public GameEngineActor
{
public:
	// constrcuter destructer
	HourGlass();
	~HourGlass();

	// delete Function
	HourGlass(const HourGlass& _Other) = delete;
	HourGlass(HourGlass&& _Other) noexcept = delete;
	HourGlass& operator=(const HourGlass& _Other) = delete;
	HourGlass& operator=(HourGlass&& _Other) noexcept = delete;

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer* Renderer;
};

