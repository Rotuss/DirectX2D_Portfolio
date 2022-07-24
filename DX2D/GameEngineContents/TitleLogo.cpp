#include "PreCompile.h"
#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

GameEngineRenderer* RendererTest = nullptr;

TitleLogo::TitleLogo() 
	: TimeAngle(0.0f)
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	GetTransform().SetLocalPosition({ 0, 200, 0 });
	
	{
		GameEngineRenderer* RendererTest = CreateComponent<GameEngineDefaultRenderer>();
		RendererTest->GetTransform().SetLocalScale({ 800, 400, 0 });
	}

	TimeAngle = 0.0f;
}

void TitleLogo::Update(float _DeltaTime)
{
	
}

void TitleLogo::End()
{
}
