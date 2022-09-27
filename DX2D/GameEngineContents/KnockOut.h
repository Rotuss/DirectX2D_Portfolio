#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class KnockOut : public GameEngineActor
{
public:
	// constrcuter destructer
	KnockOut();
	~KnockOut();

	// delete Function
	KnockOut(const KnockOut& _Other) = delete;
	KnockOut(KnockOut&& _Other) noexcept = delete;
	KnockOut& operator=(const KnockOut& _Other) = delete;
	KnockOut& operator=(KnockOut&& _Other) noexcept = delete;

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

