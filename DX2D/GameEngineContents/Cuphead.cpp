#include "PreCompile.h"
#include "Cuphead.h"
#include "MDHRLogoLevel.h"
#include "TitleLevel.h"
#include "TitleMainLevel.h"
#include "WorldMapLevel.h"
#include "TutorialLevel.h"
#include "MortimerFreezeLevel.h"
#include <GameEngineCore/GameEngineBlend.h>

#pragma comment(lib, "GameEngineBase.lib")

Cuphead::Cuphead()
	: GameEngineCore()
{
}

Cuphead::~Cuphead() 
{
}

void Cuphead::Start()
{
	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_COLOR;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_ONE;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		GameEngineBlend::Create("ContentOF", Desc);
	}

	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory("ContentResources");
	Dir.Move("ContentResources");
	Dir.Move("Texture");

	std::vector<GameEngineDirectory> Tmp = Dir.GetRecursiveAllDirectory();

	for (GameEngineDirectory Temp : Tmp)
	{
		GameEngineFolderTexture::Load(Temp.GetFullPath());
	}
	

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");

		std::vector<GameEngineFile> Common_ = Dir.GetAllFile();

		for (size_t i = 0; i < Common_.size(); i++)
		{
			GameEngineTexture::Load(Common_[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");

		std::vector<GameEngineFile> Tmp = Dir.GetAllFile();

		for (size_t i = 0; i < Tmp.size(); i++)
		{
			GameEngineTexture::Load(Tmp[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("World");

		std::vector<GameEngineFile> Tmp = Dir.GetAllFile();

		for (size_t i = 0; i < Tmp.size(); i++)
		{
			GameEngineTexture::Load(Tmp[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("MortimerFreeze");
		Dir.Move("MFBackGround");
		Dir.Move("Structure_etc");

		std::vector<GameEngineFile> Tmp = Dir.GetAllFile();

		for (size_t i = 0; i < Tmp.size(); i++)
		{
			GameEngineTexture::Load(Tmp[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("MortimerFreeze");
		Dir.Move("MFBackGround");
		Dir.Move("Candles");

		std::vector<GameEngineFile> Tmp = Dir.GetAllFile();

		for (size_t i = 0; i < Tmp.size(); i++)
		{
			GameEngineTexture::Load(Tmp[i].GetFullPath());
		}
	}

	//GameEngineFont::Load("±Ã¼­");

	CreateLevel<MDHRLogoLevel>("MDHRLogo");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<TitleMainLevel>("TitleMain");
	CreateLevel<WorldMapLevel>("World");
	CreateLevel<TutorialLevel>("Tutorial");
	CreateLevel<MortimerFreezeLevel>("MortimerFreeze");

	ChangeLevel("MortimerFreeze");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void Cuphead::Update(float _DeltaTime)
{
}

void Cuphead::End()
{
}
