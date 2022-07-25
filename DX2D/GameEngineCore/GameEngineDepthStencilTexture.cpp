#include "PreCompile.h"
#include "GameEngineDepthStencilTexture.h"

GameEngineDepthStencilTexture* GameEngineDepthStencilTexture::Create(const float4 _Scale)
{
	GameEngineDepthStencilTexture* Res = CreateResUnName();
	Res->CreateDepthTexture(_Scale);

	return Res;
}

GameEngineDepthStencilTexture::GameEngineDepthStencilTexture()
{
}

GameEngineDepthStencilTexture::~GameEngineDepthStencilTexture() 
{
}

ID3D11DepthStencilView* GameEngineDepthStencilTexture::CreateDepthStencilView()
{
	return Buffer->CreateDepthStencilView();
}

void GameEngineDepthStencilTexture::CreateDepthTexture(const float4 _Scale)
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };

	Desc.ArraySize = 1;
	Desc.Width = _Scale.uix();
	Desc.Height = _Scale.uiy();
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.MipLevels = 1;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	Buffer = GameEngineTexture::Create(Desc);
}

