#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineIndexBuffer* GameEngineIndexBuffer::Create(const std::string& _Name, const void* _Data, UINT _IndexSize, UINT _IndexCount)
{
	GameEngineIndexBuffer* NewRes = CreateResName(_Name);
	NewRes->BufferCreate(_Data, _IndexSize, _IndexCount);

	return NewRes;
}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("인덱스버퍼에 문제가 있습니다.");
	}

	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, Offset);
}

void GameEngineIndexBuffer::BufferCreate(const void* _Data, UINT _IndexSize, UINT _IndexCount)
{
	IndexSize = _IndexSize;
	IndexCount = _IndexCount;
	
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.ByteWidth = _IndexSize * _IndexCount;
	BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, &Data, &Buffer))
	{
		MsgBoxAssert("인덱스 버퍼 생성에 실패했습니다.");
	}
}

GameEngineIndexBuffer::GameEngineIndexBuffer()
	: Buffer(nullptr)
	, Offset(0)
{
}

GameEngineIndexBuffer::~GameEngineIndexBuffer() 
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}


