#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineRenderer.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	GetTransform().SetScale({ 100, 100, 100 });
	GetTransform().SetPosition({ 300, 300, 100 });
	
	GameEngineRenderer* Renderer = CreateComponent<GameEngineRenderer>();
}

void TitleLogo::Update(float _DeltaTime)
{
}

void TitleLogo::End()
{
}
