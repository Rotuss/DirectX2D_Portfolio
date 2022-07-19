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

void Cuphead::UserStart()
{
	CreateLevel<TitleLevel>("Title");

	ChangeLevel("Title");
}

void Cuphead::UserUpdate()
{
}

void Cuphead::UserEnd()
{
}
