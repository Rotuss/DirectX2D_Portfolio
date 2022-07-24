#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

#include "../GameEngineCore/ThirdParty/inc/DirectXTex.h"

#pragma comment(lib, "DirectXTex.lib")

// Ό³Έν :
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
	static GameEngineTexture* Create(ID3D11Texture2D* _Texture);

	ID3D11RenderTargetView* CreateRenderTargetView();

	void VSSetting(int _BindPoint);
	void PSSetting(int _BindPoint);

protected:

private:
	ID3D11Texture2D* Texture2D;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11ShaderResourceView* ShaderResourceView;

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage Image;

	void TextureLoad(const std::string& _Path);
};

