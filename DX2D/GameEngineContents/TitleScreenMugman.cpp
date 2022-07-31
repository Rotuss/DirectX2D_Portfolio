#include "PreCompile.h"
#include "TitleScreenMugman.h"

TitleScreenMugman::TitleScreenMugman() 
	: Renderer(nullptr)
{
}

TitleScreenMugman::~TitleScreenMugman() 
{
}

void TitleScreenMugman::Start()
{
		{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Mugman", FrameAnimation_DESC("Mugman", 0.07f, true));
		Renderer->ChangeFrameAnimation("Mugman");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 290.0f, -10.0f, 0.0f });
	}
}

void TitleScreenMugman::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

