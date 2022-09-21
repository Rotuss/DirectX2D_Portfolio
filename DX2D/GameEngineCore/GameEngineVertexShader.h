#pragma once
#include "GameEngineRes.h"
#include "GameEngineShader.h"

// Ό³Έν :
class GameEngineInputLayOut;
class GameEngineVertexShader
	: public GameEngineRes<GameEngineVertexShader>
	, public GameEngineShader
{
	friend GameEngineInputLayOut;
	friend GameEngineShader;
	friend GameEngineRes<GameEngineVertexShader>;

public:
	void Setting();

	bool IsInstancing()
	{
		return InstancingShaderPtr != nullptr;
	}

protected:
	void ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);
	void InstancingShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

private:
	// constrcuter destructer
	GameEngineVertexShader();
	~GameEngineVertexShader();

	// delete Function
	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

	static GameEngineVertexShader* Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
	static GameEngineVertexShader* Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow);

	ID3D11VertexShader* ShaderPtr;
	ID3D11VertexShader* InstancingShaderPtr;
	ID3DBlob*			InstancingBinaryPtr;
};

