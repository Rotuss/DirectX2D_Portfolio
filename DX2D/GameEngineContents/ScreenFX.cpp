#include "PreCompile.h"
#include "ScreenFX.h"
#include <GameEngineCore/GameEngineBlur.h>

ScreenFX::ScreenFX() 
	: Renderer(nullptr)
{
}

ScreenFX::~ScreenFX() 
{
}

void ScreenFX::Start()
{
	GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		
		Renderer->CreateFrameAnimationFolder("ScreenFX", FrameAnimation_DESC("ScreenFX", 0.1f, true));
		Renderer->ChangeFrameAnimation("ScreenFX");	
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
		Renderer->SetPivot(PIVOTMODE::CENTER);

		Renderer->GetPipeLine()->SetOutputMergerBlend("ContentOF");
		//Renderer->SetRenderingOrder(100000);
	}
}

void ScreenFX::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

