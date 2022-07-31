#include "PreCompile.h"
#include "TitleScreenCuphead.h"

TitleScreenCuphead::TitleScreenCuphead() 
	: Renderer(nullptr)
{
}

TitleScreenCuphead::~TitleScreenCuphead() 
{
}

void TitleScreenCuphead::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Cuphead", FrameAnimation_DESC("Cuphead", 0.07f, true));
		Renderer->ChangeFrameAnimation("Cuphead");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -330.0f, -10.0f, 0.0f });
	}
}

void TitleScreenCuphead::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

