#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(const std::string& _Name, const void* _Data, UINT _VertexSize, UINT _VertexCount, const GameEngineLayOutDesc& _LayOut)
{
	GameEngineVertexBuffer* NewRes = CreateResName(_Name);
	NewRes->LayOutDesc = &_LayOut;
	NewRes->BufferCreate(_Data, _VertexSize, _VertexCount);

	return NewRes;
}

void GameEngineVertexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgBoxAssert("버텍스버퍼에 문제가 있습니다.");
	}

	GameEngineDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &OffSet);
}

void GameEngineVertexBuffer::BufferCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	VertexSize = _VertexSize;
	VertexCount = _VertexCount;
	
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.ByteWidth = _VertexSize * _VertexCount;
	BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferDesc, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}

GameEngineVertexBuffer::GameEngineVertexBuffer()
	: BufferDesc{}
	, Buffer(nullptr)
	, OffSet(0)
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() 
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
	}
}

