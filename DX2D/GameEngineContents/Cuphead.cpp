#include "PreCompile.h"
#include "Cuphead.h"
#include "MDHRLogoLevel.h"
#include "TitleLevel.h"

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
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;

		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");
		Dir.Move("BackGround");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	CreateLevel<MDHRLogoLevel>("MDHRLogo");
	CreateLevel<TitleLevel>("Title");

	ChangeLevel("MDHRLogo");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void Cuphead::Update(float _DeltaTime)
{
}

void Cuphead::End()
{
}
