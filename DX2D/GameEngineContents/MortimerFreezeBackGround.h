#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MortimerFreezeBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	MortimerFreezeBackGround();
	~MortimerFreezeBackGround();

	// delete Function
	MortimerFreezeBackGround(const MortimerFreezeBackGround& _Other) = delete;
	MortimerFreezeBackGround(MortimerFreezeBackGround&& _Other) noexcept = delete;
	MortimerFreezeBackGround& operator=(const MortimerFreezeBackGround& _Other) = delete;
	MortimerFreezeBackGround& operator=(MortimerFreezeBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

