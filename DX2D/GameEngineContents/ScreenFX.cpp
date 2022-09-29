#include "PreCompile.h"
#include "ScreenFX.h"
#include <GameEngineCore/GameEngineBlur.h>

ScreenFX::ScreenFX() 
{
}

ScreenFX::~ScreenFX() 
{
}

void ScreenFX::Start()
{
	GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
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
	}

	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("RevScreenFX", FrameAnimation_DESC("RevScreenFX", 0.1f, true));
		PostEffectRenderer->ChangeFrameAnimation("RevScreenFX");
		PostEffectRenderer->GetTransform().SetLocalScale({ 1920,1080,1 });
		PostEffectRenderer->GetPixelData().MulColor = 0.8f;
		PostEffectRenderer->ChangeCamera(CAMERAORDER::OLDFILMCAMERA);
		PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm");
	}
}

void ScreenFX::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

