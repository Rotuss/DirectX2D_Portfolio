#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MortimerFreezeTable : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeTable();
	~MortimerFreezeTable();

	// delete Function
	MortimerFreezeTable(const MortimerFreezeTable& _Other) = delete;
	MortimerFreezeTable(MortimerFreezeTable&& _Other) noexcept = delete;
	MortimerFreezeTable& operator=(const MortimerFreezeTable& _Other) = delete;
	MortimerFreezeTable& operator=(MortimerFreezeTable&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* RendererEffect;

private:
	bool IsShoot;
};

