#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

// Ό³Έν :
class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static GameEngineTexture* Create(const std::string& _Name, ID3D11Texture2D* _Texture);

protected:

private:
	ID3D11Texture2D* Texture;
};

