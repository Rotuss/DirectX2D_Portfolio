#pragma once
#include "GameEngineRes.h"

// ���� :
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
	GameEngineInputLayOut* InputLayOut;		// ��ǲ�������1 ����
	GameEngineVertexBuffer* VertexBuffer;	// ��ǲ�������1 ����
	GameEngineVertexShader* VertexShader;	// ���ؽ����̴� ����
	GameEngineIndexBuffer* IndexBuffer;		// ��ǲ�������2 ����
	GameEngineRasterizer* Rasterizer;		// �����Ͷ����� ����
	GameEnginePixelShader* PixelShader;		// �ȼ����̴� ����
	GameEngineDepthStencil* DepthStencil;	// �ƿ�ǲ���� ���� ������ ���� 
	GameEngineBlend* Blend;					// �ƿ�ǲ���� �������� ���� 

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

