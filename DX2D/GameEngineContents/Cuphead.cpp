#include "PreCompile.h"
#include "Cuphead.h"
#include "MDHRLogoLevel.h"
#include "TitleLevel.h"
#include "TitleMainLevel.h"

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

	for (GameEngineDirectory Test : Tmp)
	{
		GameEngineFolderTexture::Load(Test.GetFullPath());
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

		std::vector<GameEngineFile> TS = Dir.GetAllFile();

		for (size_t i = 0; i < TS.size(); i++)
		{
			GameEngineTexture::Load(TS[i].GetFullPath());
		}
	}

	CreateLevel<MDHRLogoLevel>("MDHRLogo");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<TitleMainLevel>("TitleMain");

	ChangeLevel("TitleMain");

	//GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void Cuphead::Update(float _DeltaTime)
{
}

void Cuphead::End()
{
}
