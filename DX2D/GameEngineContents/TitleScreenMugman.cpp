#include "PreCompile.h"
#include "TitleScreenMugman.h"

TitleScreenMugman::TitleScreenMugman() 
	: Renderer(nullptr)
{
}

TitleScreenMugman::~TitleScreenMugman() 
{
}

void TitleScreenMugman::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalPosition({ 290.0f, -10.0f, 0.0f });

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");
		Dir.Move("Mugman");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("Mugman", FrameAnimation_DESC("Mugman", 0.07f, true));
		Renderer->ChangeFrameAnimation("Mugman");
		Renderer->ScaleToTexture();
	}
}

void TitleScreenMugman::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

