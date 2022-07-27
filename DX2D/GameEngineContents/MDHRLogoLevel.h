#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MDHRLogoLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MDHRLogoLevel();
	~MDHRLogoLevel();

	// delete Function
	MDHRLogoLevel(const MDHRLogoLevel& _Other) = delete;
	MDHRLogoLevel(MDHRLogoLevel&& _Other) noexcept = delete;
	MDHRLogoLevel& operator=(const MDHRLogoLevel& _Other) = delete;
	MDHRLogoLevel& operator=(MDHRLogoLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

