#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class WorldMapBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	WorldMapBackGround();
	~WorldMapBackGround();

	// delete Function
	WorldMapBackGround(const WorldMapBackGround& _Other) = delete;
	WorldMapBackGround(WorldMapBackGround&& _Other) noexcept = delete;
	WorldMapBackGround& operator=(const WorldMapBackGround& _Other) = delete;
	WorldMapBackGround& operator=(WorldMapBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

