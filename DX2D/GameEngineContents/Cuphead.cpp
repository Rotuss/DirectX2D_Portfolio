#include "PreCompile.h"
#include "Cuphead.h"
#include "MDHRLogoLevel.h"
#include "TitleLevel.h"
#include "TitleMainLevel.h"
#include "WorldMapLevel.h"
#include "TutorialLevel.h"

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

	//GameEngineFont::Load("±Ã¼­");

	CreateLevel<MDHRLogoLevel>("MDHRLogo");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<TitleMainLevel>("TitleMain");
	CreateLevel<WorldMapLevel>("World");
	CreateLevel<TutorialLevel>("Tutorial");

	ChangeLevel("Tutorial");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void Cuphead::Update(float _DeltaTime)
{
}

void Cuphead::End()
{
}
