#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexBuffer* GameEngineVertexBuffer::Create(const std::string& _Name, const void* _Data, size_t _Size)
{
	GameEngineVertexBuffer* NewRes = CreateResName(_Name);

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	NewRes->BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	NewRes->BufferDesc.ByteWidth = static_cast<UINT>(_Size);
	NewRes->BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	NewRes->BufferDesc.CPUAccessFlags = 0;
	
	NewRes->BufferDesc.MiscFlags = 0;
	NewRes->BufferDesc.StructureByteStride = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&NewRes->BufferDesc, &Data, &NewRes->Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
	}

	return NewRes;
}

GameEngineVertexBuffer::GameEngineVertexBuffer()
	: BufferDesc{}
	, Buffer(nullptr)
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() 
{
}

