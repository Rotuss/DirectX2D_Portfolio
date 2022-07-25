#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"

// Ό³Έν :
class GameEnginePixelShader
	: public GameEngineRes<GameEnginePixelShader>
	, public GameEngineShader
{
	friend GameEngineShader;
	friend GameEngineRes<GameEnginePixelShader>;

public:
	static GameEnginePixelShader* Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
	static GameEnginePixelShader* Load(const std::string& _Path, const std::string& _Name, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

	void Setting();

protected:
	void ShaderCompile(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

private:
	// constrcuter destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();

	// delete Function
	GameEnginePixelShader(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Other) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;

	ID3D11PixelShader* ShaderPtr;
};

