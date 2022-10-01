#include "PreCompile.h"
#include "ScreenFX.h"

ScreenFX::ScreenFX() 
{
}

ScreenFX::~ScreenFX() 
{
}

void ScreenFX::Start()
{
	//{
	//	Renderer = CreateComponent<GameEngineTextureRenderer>();
	//	
	//	Renderer->CreateFrameAnimationFolder("ScreenFX", FrameAnimation_DESC("ScreenFX", 0.1f, true));
	//	Renderer->ChangeFrameAnimation("ScreenFX");	
	//	Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
	//	Renderer->SetPivot(PIVOTMODE::CENTER);

	//	Renderer->GetPipeLine()->SetOutputMergerBlend("ContentOF");
	//	//Renderer->SetRenderingOrder(100000);
	//}

	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("ScreenFX", FrameAnimation_DESC("ScreenFX", 0.1f, true));
		PostEffectRenderer->ChangeFrameAnimation("ScreenFX");
		PostEffectRenderer->GetTransform().SetLocalScale({ 1920,1080,1 });
		PostEffectRenderer->ChangeCamera(CAMERAORDER::OLDFILMCAMERA);
		PostEffectRenderer->GetPixelData().MulColor = 1.05f;
	}

	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("RevScreenFX", FrameAnimation_DESC("RevScreenFX", 0.1f, true));
		PostEffectRenderer->ChangeFrameAnimation("RevScreenFX");
		PostEffectRenderer->GetTransform().SetLocalScale({ 1920,1080,1 });
		PostEffectRenderer->ChangeCamera(CAMERAORDER::OLDFILMCAMERA);
		PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm");
		PostEffectRenderer->GetPixelData().MulColor = 1.05f;
		PostEffectRenderer->RenderOption.IsOldFilmColor = 1;
	}
}

void ScreenFX::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

