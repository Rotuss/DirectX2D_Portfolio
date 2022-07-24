#include "PreCompile.h"
#include "GameEngineRenderingPipeLine.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineBlend.h"

GameEngineRenderingPipeLine* GameEngineRenderingPipeLine::Create(const std::string& _Name)
{
	return CreateResName(_Name);
}

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine()
	: InputLayOut(nullptr)
	, VertexBuffer(nullptr)
	, VertexShader(nullptr)
	, IndexBuffer(nullptr)
	, Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, Rasterizer(nullptr)
	, PixelShader(nullptr)
	, DepthStencil(nullptr)
	, Blend(nullptr)
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() 
{
	if (nullptr != InputLayOut)
	{
		delete InputLayOut;
		InputLayOut = nullptr;
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler1VertexBuffer(const std::string& _Name)
{
	VertexBuffer = GameEngineVertexBuffer::Find(_Name);

	if (nullptr == VertexBuffer)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ����۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (nullptr == InputLayOut && nullptr != VertexShader)
	{
		InputLayOut = new GameEngineInputLayOut();
		InputLayOut->Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string& _Name)
{
	VertexShader = GameEngineVertexShader::Find(_Name);

	if (nullptr == VertexShader)
	{
		MsgBoxAssert("�������� �ʴ� ���ؽ����̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (nullptr == InputLayOut && nullptr != VertexBuffer)
	{
		InputLayOut = new GameEngineInputLayOut();
		InputLayOut->Create(*VertexBuffer->GetLayOutDesc(), VertexShader);
	}
}

void GameEngineRenderingPipeLine::SetInputAssembler2IndexBuffer(const std::string& _Name)
{
	IndexBuffer = GameEngineIndexBuffer::Find(_Name);

	if (nullptr == IndexBuffer)
	{
		MsgBoxAssert("�������� �ʴ� �ε������۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string& _Name)
{
	Rasterizer = GameEngineRasterizer::Find(_Name);

	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("�������� �ʴ� �����Ͷ������� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetPixelShader(const std::string& _Name)
{
	PixelShader = GameEnginePixelShader::Find(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("�������� �ʴ� �ȼ����̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetOutputMergerDepthStencil(const std::string& _Name)
{
	DepthStencil = GameEngineDepthStencil::Find(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("�������� �ʴ� ���̽��ٽ��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetOutputMergerBlend(const std::string& _Name)
{
	Blend = GameEngineBlend::Find(_Name);

	if (nullptr == Blend)
	{
		MsgBoxAssert("�������� �ʴ� ������ �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::Rendering()
{
	InputAssembler1VertexBufferSetting();
	VertexShaderSetting();
	InputAssembler2IndexBufferSetting();
	RasterizerSetting();
	PixelShaderSetting();
	OutputMergerBlendSetting();
	OutputMergerDepthStencilSetting();
	Draw();
}

void GameEngineRenderingPipeLine::InputAssembler1VertexBufferSetting()
{
	InputLayOut->Setting();
	VertexBuffer->Setting();
}

void GameEngineRenderingPipeLine::VertexShaderSetting()
{
	VertexShader->Setting();
}

void GameEngineRenderingPipeLine::InputAssembler2IndexBufferSetting()
{
	GameEngineDevice::GetContext()->IASetPrimitiveTopology(Topology);
	IndexBuffer->Setting();
}

void GameEngineRenderingPipeLine::RasterizerSetting()
{
	Rasterizer->Setting();
}

void GameEngineRenderingPipeLine::PixelShaderSetting()
{
	PixelShader->Setting();
}

void GameEngineRenderingPipeLine::OutputMergerBlendSetting()
{
}

void GameEngineRenderingPipeLine::OutputMergerDepthStencilSetting()
{
}

void GameEngineRenderingPipeLine::Draw()
{
	GameEngineDevice::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
}
