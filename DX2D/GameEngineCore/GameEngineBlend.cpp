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
		MsgBoxAssert("블렌드가 nullptr 입니다. 세팅할수 없습니다.");
		return;
	}

	GameEngineDevice::GetContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}

void GameEngineBlend::Create(const D3D11_BLEND_DESC& _Desc)
{
	Desc = _Desc;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBlendState(&Desc, &State))
	{
		MsgBoxAssert("블렌드 생성에 실패했습니다.");
	}
}

