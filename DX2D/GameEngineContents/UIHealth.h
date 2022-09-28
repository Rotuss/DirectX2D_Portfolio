#pragma once
#include "UIMaster.h"

// Ό³Έν :
class UIHealth : public UIMaster
{
public:
	// constrcuter destructer
	UIHealth();
	~UIHealth();

	// delete Function
	UIHealth(const UIHealth& _Other) = delete;
	UIHealth(UIHealth&& _Other) noexcept = delete;
	UIHealth& operator=(const UIHealth& _Other) = delete;
	UIHealth& operator=(UIHealth&& _Other) noexcept = delete;

	inline void SetHealthCount(int _Value)
	{
		HealthCount = _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() {}

private:
	GameEngineUIRenderer* Renderer;

	int HealthCount;
};

