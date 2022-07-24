#include "PreCompile.h"
#include "Cuphead.h"
#include "GameEngineContents/TitleLevel.h"

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

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());
	}

	//Dir.Move("Cuphead");
	//GameEngineFolderTexture::Load(Dir.GetFullPath());
	
	CreateLevel<TitleLevel>("Title");

	ChangeLevel("Title");
}

void Cuphead::Update(float _DeltaTime)
{
}

void Cuphead::End()
{
}
