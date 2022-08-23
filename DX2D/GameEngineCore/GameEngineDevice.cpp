#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineRenderTarget.h"
#include <GameEngineBase/GameEngineWindow.h>

ID3D11Device* GameEngineDevice::Device_ = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context_ = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain_ = nullptr;
GameEngineRenderTarget* GameEngineDevice::BackBufferTarget = nullptr;

void GameEngineDevice::Destroy()
{
	if (nullptr != SwapChain_)
	{
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}

	if (nullptr != Context_)
	{
		Context_->Release();
		Context_ = nullptr;
	}

	if (nullptr != Device_)
	{
		Device_->Release();
		Device_ = nullptr;
	}
}

void GameEngineDevice::Initialize()
{
	DeviceCreate();
	//CreateSwapChain();
}

void GameEngineDevice::DeviceCreate()
{
	if (nullptr == GameEngineWindow::GetHWND())
	{
		MsgBoxAssert("윈도우가 만들어지지 않았는데 디바이스를 초기화 하려고 했습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
	IDXGIAdapter* pA = GetHighPerformanceAdapter();

	if (S_OK != D3D11CreateDevice(
			pA,
			//D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			iFlag,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&Device_,
			&Level,
			&Context_))
	{
		MsgBoxAssert("디바이스 생성이 실패했습니다.");
	}

	if (nullptr != pA)
	{
		pA->Release();
		pA = nullptr;
	}

	if (Level != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		MsgBoxAssert("11을 지원하지 않는 디바이스 입니다.");
	}

	HRESULT Hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
}

void GameEngineDevice::CreateSwapChain()
{
	float4 ScreenSize = GameEngineWindow::GetScale();

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, };

	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uiy();
	ScInfo.OutputWindow = GameEngineWindow::GetHWND();

	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;

	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ScInfo.Windowed = true;

	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));

	if (nullptr == pD)
	{
		MsgBoxAssert("디바이스 추출에 실패했습니다.");
	}

	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (nullptr == pA)
	{
		MsgBoxAssert("어뎁터 추출에 실패했습니다.");
	}

	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (nullptr == pF)
	{
		MsgBoxAssert("팩토리 추출에 실패했습니다.");
	}

	if (S_OK != pF->CreateSwapChain(Device_, &ScInfo, &SwapChain_))
	{
		MsgBoxAssert("스왑체인 생성에 실패했습니다.");
	}


	pF->Release();
	pA->Release();
	pD->Release();

	ID3D11Texture2D* BackBufferTexture = nullptr;
	if (S_OK != SwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBufferTexture)))
	{
		MsgBoxAssert("백버퍼 텍스처를 얻어오지 못했습니다.");
	}

	BackBufferTarget = GameEngineRenderTarget::Create("BackBuffer");
	BackBufferTarget->CreateRenderTargetTexture(BackBufferTexture, float4::BLUE);
	BackBufferTarget->CreateDepthTexture(0);
}

void GameEngineDevice::RenderStart()
{
	BackBufferTarget->Clear();
	BackBufferTarget->Setting();
}

void GameEngineDevice::RenderEnd()
{
	HRESULT Result = SwapChain_->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("디바이스 프레젠트에 이상이 생겼습니다.");
	}
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* pF = nullptr;
	IDXGIAdapter* pA = nullptr;
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pF);
	size_t prevAdapterVideoMemory = 0;

	for (UINT adapterIndex = 0; ; ++adapterIndex)
	{
		IDXGIAdapter* pA1 = nullptr;
		pF->EnumAdapters(adapterIndex, &pA1);
		if (nullptr == pA1)
		{
			break;
		}

		DXGI_ADAPTER_DESC adapterDesc;
		pA1->GetDesc(&adapterDesc);
		if (prevAdapterVideoMemory <= adapterDesc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = adapterDesc.DedicatedVideoMemory;
			if (nullptr != pA)
			{
				pA->Release();
			}

			pA = pA1;
			continue;
		}

		pA1->Release();
	}

	pF->Release();
	return pA;
}
