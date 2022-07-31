#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class TItleMainBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TItleMainBackGround();
	~TItleMainBackGround();

	// delete Function
	TItleMainBackGround(const TItleMainBackGround& _Other) = delete;
	TItleMainBackGround(TItleMainBackGround&& _Other) noexcept = delete;
	TItleMainBackGround& operator=(const TItleMainBackGround& _Other) = delete;
	TItleMainBackGround& operator=(TItleMainBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

