#include "TitleLevel.h"
#include "TitleLogo.h"
#include "Enums.h"
#include "GameEngineCore/GEngine.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	CreateActor<TitleLogo>(GameObjectGroup::UI);
}

void TitleLevel::Update(float _DeltaTime)
{
}

void TitleLevel::End()
{
}
