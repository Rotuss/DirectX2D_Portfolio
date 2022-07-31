#include "PreCompile.h"
#include "TitleScreenChips.h"

TitleScreenChips::TitleScreenChips() 
	: Renderer(nullptr)
{
}

TitleScreenChips::~TitleScreenChips() 
{
}

void TitleScreenChips::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalPosition({ 0.0f, -300.0f, 0.0f });
		Renderer->SetTexture("title_chips_left_0001.png");
		Renderer->ScaleToTexture();
	}
}

void TitleScreenChips::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

