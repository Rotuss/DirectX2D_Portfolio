#include "PreCompile.h"
#include "GameEngineBlend.h"

GameEngineBlend* GameEngineBlend::Create(const std::string& _Name, const D3D11_BLEND_DESC& _Desc)
{
	GameEngineBlend* NewRes = CreateResName(_Name);
	NewRes->Create(_Desc);

	return NewRes;
}

GameEngineBlend::GameEngineBlend()
    : Mask(0xffffffff)
{
}

GameEngineBlend::~GameEngineBlend() 
{
	if (nullptr != State)
	{
		State->Release();
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("���尡 nullptr �Դϴ�. �����Ҽ� �����ϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}

void GameEngineBlend::Create(const D3D11_BLEND_DESC& _Desc)
{
	Desc = _Desc;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBlendState(&Desc, &State))
	{
		MsgBoxAssert("���� ������ �����߽��ϴ�.");
	}
}

