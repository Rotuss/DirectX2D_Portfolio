#include "PreCompile.h"
#include "TitleScreenBackGround.h"

TitleScreenBackGround::TitleScreenBackGround()
	: Renderer(nullptr)
{
}

TitleScreenBackGround::~TitleScreenBackGround()
{
}

void TitleScreenBackGround::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("title_screen_background.png");
		Renderer->ScaleToTexture();
	}
}

void TitleScreenBackGround::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

