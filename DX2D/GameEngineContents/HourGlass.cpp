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
	// 사운드 추가
	GameEngineSound::SoundPlayOneShot("sfx_noise_1920s_01.wav");
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("BlackBackground.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);
		Renderer->GetTransform().SetLocalScale({ 1280, 720 });
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("Hourglass", 0.07f, true));
		Renderer->ChangeFrameAnimation("Hourglass");
		Renderer->ScaleToTexture();
		Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);
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

