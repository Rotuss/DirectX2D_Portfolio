#pragma once
#include <map>
#include <string>
#include <functional>
#include <GameEngineBase/GameEngineNameObject.h>

enum class ShaderType
{
	Vertex,
	Pixel,
	
	Max,
};

class GameEngineShader;
class ShaderResSetter : public GameEngineNameObject
{
public:
	GameEngineShader* ParentShader;
	ShaderType ShaderType;
	int BindPoint;
	std::function<void()> SettingFunction;

public:
	ShaderResSetter()
		: ParentShader(nullptr)
		, ShaderType(ShaderType::Max)
		, BindPoint(-1)
	{
	}
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
	friend GameEngineShader;

public:
	GameEngineConstantBuffer* Res;
	const void* SetData;
	UINT Size;

	std::vector<char> OriginalData;

	void Setting() const;

public:
	GameEngineConstantBufferSetter()
		: Res(nullptr)
		, SetData(nullptr)
		, Size(-1)
	{
	}
};

class GameEngineTexture;
class GameEngineTextureSetter : public ShaderResSetter
{
	friend GameEngineShader;

public:
	GameEngineTexture* Res;
	void Setting() const;
};

class GameEngineSampler;
class GameEngineSamplerSetter : public ShaderResSetter
{
public:
	GameEngineSampler* Res;
	void Setting() const;
};

class GameEngineStructuredBuffer;
class GameEngineStructuredBufferSetter : public ShaderResSetter
{
public:
	GameEngineStructuredBuffer* Res;
	void Setting() const;
};

// Ό³Έν :
class GameEngineShaderResourcesHelper;
class GameEngineShader
{
	friend GameEngineShaderResourcesHelper;

public:
	static void AutoCompile(const std::string& _Path);

public:
	// constrcuter destructer
	GameEngineShader();
	~GameEngineShader();

	// delete Function
	GameEngineShader(const GameEngineShader& _Other) = delete;
	GameEngineShader(GameEngineShader&& _Other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;

	GameEngineConstantBufferSetter& GetConstantBufferSetter(std::string _Name);

protected:
	void CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow);
	void SetEntryPoint(const std::string& _EntryPoint)
	{
		EntryPoint = _EntryPoint;
	}

	ID3DBlob* BinaryPtr;
	std::string Version;

	void ShaderResCheck();

	ShaderType ShaderSettingType;

private:
	std::map<std::string, GameEngineConstantBufferSetter> ConstantBufferMap;
	std::map<std::string, GameEngineTextureSetter> TextureMap;
	std::map<std::string, GameEngineSamplerSetter> SamplerMap;
	std::map<std::string, GameEngineStructuredBufferSetter> StructuredBufferMap;
	std::string EntryPoint;
};

