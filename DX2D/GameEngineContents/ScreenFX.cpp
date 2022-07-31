#include "PreCompile.h"
#include "ScreenFX.h"

ScreenFX::ScreenFX() 
	: Renderer(nullptr)
{
}

ScreenFX::~ScreenFX() 
{
}

void ScreenFX::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		
		Renderer->CreateFrameAnimationFolder("ScreenFX", FrameAnimation_DESC("ScreenFX", 0.5f, true));
		Renderer->ChangeFrameAnimation("ScreenFX");	
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}
}

void ScreenFX::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

