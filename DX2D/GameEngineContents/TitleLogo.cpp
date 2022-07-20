#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>

GameEngineRenderer* RendererTest = nullptr;

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	//GetTransform().SetScale({ 100, 50, 100 });
	GetTransform().SetLocalPosition({ 300, 300, 100 });
	
	{
		RendererTest = CreateComponent<GameEngineRenderer>();
		RendererTest->GetTransform().SetLocalScale({ 100, 100, 100 });
		RendererTest->GetTransform().SetLocalPosition({ 100, 0, 0 });
	}
	
	{
		GameEngineCamera* Camera = CreateComponent<GameEngineCamera>();
	}

	TimeAngle = 0.0f;
}

void TitleLogo::Update(float _DeltaTime)
{
	TimeAngle += _DeltaTime * 20.0f;

	GetTransform().SetLocalRotation({ 0.0f , 0.0f, TimeAngle });
	RendererTest->GetTransform().SetLocalRotation({ TimeAngle , TimeAngle, TimeAngle });
}

void TitleLogo::End()
{
}
