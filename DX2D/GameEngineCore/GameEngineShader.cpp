#include "PreCompile.h"
#include "GameEngineShader.h"

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineConstantBuffer.h"

void GameEngineShader::AutoCompile(const std::string& _Path)
{
	GameEngineFile File = GameEngineFile(_Path);
	File.Open(OpenMode::Read, FileMode::Text);

	std::string AllHlslCode = File.GetString();
	AllHlslCode.resize(File.GetFileSize());

	File.Read(&AllHlslCode[0], AllHlslCode.size(), AllHlslCode.size());

	size_t VSEntryIndex = AllHlslCode.find("_VS(");
	
	if (std::string::npos != VSEntryIndex)
	{
		size_t FirstIndex = AllHlslCode.find_last_of(" ", VSEntryIndex);
		
		std::string EntryName = AllHlslCode.substr(FirstIndex + 1, VSEntryIndex - FirstIndex - 1);
		EntryName += "_VS";
		GameEngineVertexShader::Load(_Path, EntryName);
	}

	size_t PSEntryIndex = AllHlslCode.find("_PS(");
	if (std::string::npos != PSEntryIndex)
	{
		size_t FirstIndex = AllHlslCode.find_last_of(" ", PSEntryIndex);

		std::string EntryName = AllHlslCode.substr(FirstIndex + 1, PSEntryIndex - FirstIndex - 1);
		EntryName += "_PS";
		GameEnginePixelShader::Load(_Path, EntryName);
	}
}

GameEngineShader::GameEngineShader()
	: BinaryPtr(nullptr)
	, Version("")
{
}

GameEngineShader::~GameEngineShader() 
{
	if (nullptr != BinaryPtr)
	{
		BinaryPtr->Release();
		BinaryPtr = nullptr;
	}
}

void GameEngineShader::CreateVersion(const std::string& _ShaderType, UINT _VersionHigh, UINT _VersionLow)
{
	Version = "";
	Version += _ShaderType + "_";				// vs_
	Version += std::to_string(_VersionHigh);	// vs_5
	Version += "_";								// vs_5_
	Version += std::to_string(_VersionLow);		// vs_5_0
}

void GameEngineShader::ShaderResCheck()
{
	if (nullptr == BinaryPtr)
	{
		MsgBoxAssert("쉐이더 리소스가 만들어지지 않았는데 리소스(상수버퍼 and 텍스처) 체크를 하려고 했습니다.");
		return;
	}

	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(
		BinaryPtr->GetBufferPointer(),
		BinaryPtr->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("쉐이더 리플렉션이 잘못 되었습니다.");
		return;
	}

	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);
	D3D11_SHADER_INPUT_BIND_DESC ResInfo;

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResInfo);
		std::string Name = GameEngineString::ToUpperReturn(ResInfo.Name);

		D3D_SHADER_INPUT_TYPE Type = ResInfo.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResInfo.Name);

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			CBufferPtr->GetDesc(&BufferDesc);

			GameEngineConstantShaderResSetter NewSetter;
			NewSetter.Buffer = GameEngineConstantBuffer::Create(Name, BufferDesc, CBufferPtr);
			NewSetter.BindPoint = ResInfo.BindPoint;

			ResSetterMap.insert(std::make_pair(Name, NewSetter));
			break;
		}
		default:
			MsgBoxAssert("아직 처리하지 않은 쉐이더 리소스입니다.");
			break;
		}

		int a = 0;
	}
}

