#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MortimerFreezeWhale : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeWhale();
	~MortimerFreezeWhale();

	// delete Function
	MortimerFreezeWhale(const MortimerFreezeWhale& _Other) = delete;
	MortimerFreezeWhale(MortimerFreezeWhale&& _Other) noexcept = delete;
	MortimerFreezeWhale& operator=(const MortimerFreezeWhale& _Other) = delete;
	MortimerFreezeWhale& operator=(MortimerFreezeWhale&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;

private:

};

