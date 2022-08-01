#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class TutorialBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TutorialBackGround();
	~TutorialBackGround();

	// delete Function
	TutorialBackGround(const TutorialBackGround& _Other) = delete;
	TutorialBackGround(TutorialBackGround&& _Other) noexcept = delete;
	TutorialBackGround& operator=(const TutorialBackGround& _Other) = delete;
	TutorialBackGround& operator=(TutorialBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

