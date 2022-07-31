#include "PreCompile.h"
#include "HourGlass.h"

HourGlass::HourGlass() 
	: Renderer(nullptr)
{
}

HourGlass::~HourGlass() 
{
}

void HourGlass::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("BlackBackground.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("Hourglass", 0.07f, true));
		Renderer->ChangeFrameAnimation("Hourglass");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 530.0f, -160.0f, 0.0f });
	}
}

void HourGlass::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

