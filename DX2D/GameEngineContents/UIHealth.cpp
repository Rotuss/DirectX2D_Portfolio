#include "PreCompile.h"
#include "UIHealth.h"

UIHealth::UIHealth() 
	: Renderer(nullptr)
	, HealthCount(4)
{
}

UIHealth::~UIHealth() 
{
}

void UIHealth::Start()
{
	{
		Renderer = CreateComponent<GameEngineUIRenderer>();
		Renderer->CreateFrameAnimationFolder("UIHealth_01", FrameAnimation_DESC("UIHealth", 0, 1, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("UIHealth_02", FrameAnimation_DESC("UIHealth", 2, 2, 0.0f, false));
		Renderer->CreateFrameAnimationFolder("UIHealth_03", FrameAnimation_DESC("UIHealth", 3, 3, 0.0f, false));
		Renderer->CreateFrameAnimationFolder("UIHealth_04", FrameAnimation_DESC("UIHealth", 4, 4, 0.0f, false));
		Renderer->CreateFrameAnimationFolder("UIHealth_Dead", FrameAnimation_DESC("UIHealth", 5, 5, 0.0f, false));

		Renderer->ChangeFrameAnimation("UIHealth_04");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		Renderer->GetTransform().SetLocalPosition({ -580.0f, -325.0f, 0.0f });
	}
}

void UIHealth::Update(float _DeltaTime)
{
	if (4 == HealthCount)
	{
		Renderer->ChangeFrameAnimation("UIHealth_04");
	}
	if (3 == HealthCount)
	{
		Renderer->ChangeFrameAnimation("UIHealth_03");
	}
	if (2 == HealthCount)
	{
		Renderer->ChangeFrameAnimation("UIHealth_02");
	}
	if (1 == HealthCount)
	{
		Renderer->ChangeFrameAnimation("UIHealth_01");
	}
	if (0 == HealthCount)
	{
		Renderer->ChangeFrameAnimation("UIHealth_Dead");
	}
}

