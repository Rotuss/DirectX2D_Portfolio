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
	CreateLevel<TitleLevel>("Title");

	ChangeLevel("Title");
}

void Cuphead::Update(float _DeltaTime)
{
}

void Cuphead::End()
{
}
