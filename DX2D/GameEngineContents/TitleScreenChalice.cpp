#include "PreCompile.h"
#include "TitleScreenChalice.h"

TitleScreenChalice::TitleScreenChalice() 
	: Renderer(nullptr)
{
}

TitleScreenChalice::~TitleScreenChalice() 
{
}

void TitleScreenChalice::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Chalice", FrameAnimation_DESC("Chalice", 0.07f, true));
		Renderer->ChangeFrameAnimation("Chalice");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -20.0f, -50.0f, 0.0f });
	}
}

void TitleScreenChalice::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

