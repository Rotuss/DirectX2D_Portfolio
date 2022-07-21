#pragma once
#include <GameEngineBase/GameEngineMath.h>

// ���� :
class GameEngineDevice
{
private:
	static GameEngineDevice* Inst;

public:
	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();

	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	static GameEngineDevice& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

protected:

private:
	static ID3D11Device* Device_;
	static ID3D11DeviceContext* Context_;
	static IDXGISwapChain* SwapChain_;
};

