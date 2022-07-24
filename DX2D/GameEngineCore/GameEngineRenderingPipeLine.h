#pragma once
#include "GameEngineRes.h"

// 설명 :
class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineRenderingPipeLine : public GameEngineRes<GameEngineRenderingPipeLine>
{
public:
	// constrcuter destructer
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	// delete Function
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	void Draw();

protected:
	GameEngineInputLayOut* InputLayOut;		// 인풋어셈블러1 세팅
	GameEngineVertexBuffer* VertexBuffer;	// 인풋어셈블러1 세팅
	GameEngineVertexShader* VertexShader;	// 버텍스쉐이더 세팅
	GameEngineIndexBuffer* IndexBuffer;		// 인풋어셈블러2 세팅
	GameEngineRasterizer* Rasterizer;		// 레스터라이저 세팅
	GameEnginePixelShader* PixelShader;		// 픽셀쉐이더 세팅
	GameEngineDepthStencil* DepthStencil;	// 아웃풋머저 누가 앞인지 세팅 
	GameEngineBlend* Blend;					// 아웃풋머저 색상통합 세팅 

private:
	void SetInputAssembler1InputLayOutSetting(const std::string& _Name);
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);
	void SetVertexShader(const std::string& _Name);
	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);
	void SetRasterizer(const std::string& _Name);
	void SetPixelShader(const std::string& _Name);
	void SetOutputMergerBlend(const std::string& _Name);
	void SetOutputMergerDepthStencilSetting(const std::string& _Name);
};

