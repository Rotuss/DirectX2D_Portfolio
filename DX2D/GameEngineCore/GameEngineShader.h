#pragma once
#include <map>
#include <string>

enum class ShaderType
{
	Vertex,
	Pixel,
};

class ShaderResSetter
{
public:
	ShaderType ShaderType;
	int BindPoint;
	std::string* Name;
};

class GameEngineConstantBuffer;
class GameEngineConstantBufferSetter : public ShaderResSetter
{
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

class GameEngineConstantBuffer;
class GameEngineTextureSetter : public ShaderResSetter
{
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
	std::map<std::string, GameEngineTextureSetter> TextureSetterMap;
	std::string EntryPoint;
};

