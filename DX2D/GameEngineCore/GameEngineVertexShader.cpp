#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include <GameEngineBase/GameEngineString.h>

void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgBoxAssert("버텍스쉐이더 세팅 오류가 발생했습니다.");
	}

	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}

void GameEngineVertexShader::ShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UnicodePath = GameEngineString::AnsiToUnicodeReturn(_Path);

	if (S_OK != D3DCompileFromFile(
		UnicodePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_EntryPoint.c_str(),
		Version.c_str(),
		Flag,
		0,
		&BinaryPtr,
		&Error))
	{
		std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssertString(ErrorText);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(
		BinaryPtr->GetBufferPointer(),
		BinaryPtr->GetBufferSize(),
		nullptr,
		&ShaderPtr))
	{
		MsgBoxAssert("버텍스쉐이더 핸들 생성에 실패했습니다.");
	}

	ShaderResCheck();
}

void GameEngineVertexShader::InstancingShaderCompile(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UnicodePath = GameEngineString::AnsiToUnicodeReturn(_Path);

	if (D3DCompileFromFile(
		UnicodePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_EntryPoint.c_str(),
		Version.c_str(),
		Flag,
		0,
		&InstancingBinaryPtr,
		&Error)
		)
	{
		std::string ErrorText = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssertString(ErrorText);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(
		InstancingBinaryPtr->GetBufferPointer(),
		InstancingBinaryPtr->GetBufferSize(),
		nullptr,
		&InstancingShaderPtr))
	{
		MsgBoxAssert("버텍스쉐이더 핸들 생성에 실패했습니다.");
	}

	ShaderResCheck();
}

GameEngineVertexShader::GameEngineVertexShader() 
	: ShaderPtr(nullptr)
	, InstancingShaderPtr(nullptr)
{
	ShaderSettingType = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader() 
{
	if (nullptr != InstancingShaderPtr)
	{
		InstancingShaderPtr->Release();
		InstancingShaderPtr = nullptr;
	}
	if (nullptr != InstancingShaderPtr)
	{
		InstancingBinaryPtr->Release();
		InstancingBinaryPtr = nullptr;
	}
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

GameEngineVertexShader* GameEngineVertexShader::Load(std::string _Path, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path), _EntryPoint, _VersionHigh, _VersionLow);
}

GameEngineVertexShader* GameEngineVertexShader::Load(std::string _Path, std::string _Name, std::string _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	GameEngineVertexShader* NewRes = CreateResName(_Name);
	NewRes->ShaderCompile(_Path, _EntryPoint, _VersionHigh, _VersionLow);
	
	return NewRes;
}

