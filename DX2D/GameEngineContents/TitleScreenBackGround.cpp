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

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");
		Dir.Move("BackGround");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->SetTexture("title_screen_background.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
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

