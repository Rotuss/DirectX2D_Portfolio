#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class ReadyWALLOP : public GameEngineActor
{
public:
	// constrcuter destructer
	ReadyWALLOP();
	~ReadyWALLOP();

	// delete Function
	ReadyWALLOP(const ReadyWALLOP& _Other) = delete;
	ReadyWALLOP(ReadyWALLOP&& _Other) noexcept = delete;
	ReadyWALLOP& operator=(const ReadyWALLOP& _Other) = delete;
	ReadyWALLOP& operator=(ReadyWALLOP&& _Other) noexcept = delete;

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

