#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

std::map<std::string, std::map<int, GameEngineConstantBuffer*>> GameEngineConstantBuffer::NamedRes;

GameEngineConstantBuffer::GameEngineConstantBuffer() 
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer() 
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}

void GameEngineConstantBuffer::ChangeData(const void* _Data, size_t _Size) const
{
	if (_Data == nullptr)
	{
		MsgBoxAssertString(GetNameCopy() + " 데이터를 세팅해주지 않았습니다.");
	}
	
	if (BufferDesc.ByteWidth != _Size)
	{
		MsgBoxAssertString(GetNameCopy() + " 상수버퍼의 바이트 크기가 서로 맞지 않습니다.");
	}

	static D3D11_MAPPED_SUBRESOURCE SettingResources = {};
	memset(&SettingResources, 0, sizeof(SettingResources));

	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);

	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("그래픽카드 버퍼에 접근하지 못 했습니다.");
	}

	memcpy_s(SettingResources.pData, BufferDesc.ByteWidth, _Data, BufferDesc.ByteWidth);

	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
}

void GameEngineConstantBuffer::VSSetting()
{
	GameEngineDevice::GetContext()->VSSetConstantBuffers(0, 1, &Buffer);
}

void GameEngineConstantBuffer::PSSetting()
{
	GameEngineDevice::GetContext()->PSSetConstantBuffers(0, 1, &Buffer);
}

void GameEngineConstantBuffer::Create(const D3D11_SHADER_BUFFER_DESC& _Desc, ID3D11ShaderReflectionConstantBuffer* _CBufferPtr)
{
	ShaderDesc = _Desc;

	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.ByteWidth = ShaderDesc.Size;
	BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, nullptr, &Buffer))
	{
		MsgBoxAssert("상수버퍼 생성에 실패했습니다.");
	}
}