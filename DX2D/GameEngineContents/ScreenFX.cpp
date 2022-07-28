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
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("ScreenFX");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

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

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

