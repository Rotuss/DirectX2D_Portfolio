#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

#include "../GameEngineCore/ThirdParty/inc/DirectXTex.h"

#pragma comment(lib, "DirectXTex.lib")

// 설명 :
class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static GameEngineTexture* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineTexture* Load(const std::string& _Path, const std::string& _Name);
	static GameEngineTexture* Create(const std::string& _Name, ID3D11Texture2D* _Texture);
	static GameEngineTexture* Create(const D3D11_TEXTURE2D_DESC& _Desc);
	static GameEngineTexture* Create(ID3D11Texture2D* _Texture);

	static void Cut(const std::string& _Name, UINT _X, UINT _Y);

	ID3D11RenderTargetView* CreateRenderTargetView();
	ID3D11DepthStencilView* CreateDepthStencilView();

	void VSSetting(int _BindPoint);
	void PSSetting(int _BindPoint);

	float4 GetFrameData(UINT _Index)
	{
		if (true == CutData.empty())
		{
			MsgBoxAssertString(GetNameCopy() + " 자르지 않은 텍스처를 사용하려고 했습니다.");
		}

		if (CutData.size() <= _Index)
		{
			MsgBoxAssertString(GetNameCopy() + " 프레임 범위를 초과했습니다.");
		}

		return CutData[_Index];
	}

	float4 GetScale()
	{
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height) };
	}

	float4 GetPixel(int _x, int _y);

	void TextureLoad(const std::string& _Path);

	void TextureCreate(const D3D11_TEXTURE2D_DESC& _Desc);

protected:

private:
	ID3D11Texture2D* Texture2D;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11ShaderResourceView* ShaderResourceView;
	ID3D11DepthStencilView* DepthStencilView;

	D3D11_TEXTURE2D_DESC Desc;
	
	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage Image;

	std::vector<float4> CutData;

	void Cut(UINT _X, UINT _Y);
};

