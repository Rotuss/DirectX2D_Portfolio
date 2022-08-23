#pragma once
#include <vector>
#include "GameEngineTexture.h"
#include "GameEngineShaderResourcesHelper.h"

// Ό³Έν :
class GameEngineStatusWindow;
class GameEngineRenderTarget : public GameEngineRes <GameEngineRenderTarget>
{
	friend GameEngineStatusWindow;

public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static GameEngineRenderTarget* Create(const std::string& _Name);
	static GameEngineRenderTarget* Create();

	static ID3D11RenderTargetView* PrevRenderTargetViews;
	static ID3D11DepthStencilView* PrevDepthStencilView;

	inline GameEngineTexture* GetDepthTexture()
	{
		return DepthTexture;
	}

	static void GetPrevRenderTarget();
	static void SetPrevRenderTarget();

	void CreateRenderTargetTexture(ID3D11Texture2D* _Texture, float4 _Color);
	void CreateRenderTargetTexture(GameEngineTexture* _Texture, float4 _Color);
	void CreateRenderTargetTexture(D3D11_TEXTURE2D_DESC _Data, float4 _Color);
	void CreateRenderTargetTexture(float4 _Size, float4 _Color);
	void CreateRenderTargetTexture(float4 _Size, DXGI_FORMAT _Format, float4 _Color);

	void Clear();

	void Setting();

	void SettingDepthTexture(GameEngineTexture* _Texture);

	void CreateDepthTexture(int _Index = 0);

	GameEngineTexture* GetRenderTargetTexture(size_t _Index);
	void Merge(GameEngineRenderTarget* _Other, int _Index);
	void Effect(GameEngineRenderingPipeLine* _Other, GameEngineShaderResourcesHelper* _ShaderResourcesHelper);

protected:
	std::vector<GameEngineTexture*>			RenderTargets;
	std::vector<ID3D11RenderTargetView*>	RenderTargetViews;
	std::vector<ID3D11ShaderResourceView*>	ShaderResourceViews;
	std::vector<float4>						ClearColors;

	ID3D11DepthStencilView*			DepthStencilView;
	GameEngineTexture*				DepthTexture;
	GameEngineRenderingPipeLine*	MergePipeLine;
	GameEngineShaderResourcesHelper MergeShaderResourcesHelper;

private:

};

