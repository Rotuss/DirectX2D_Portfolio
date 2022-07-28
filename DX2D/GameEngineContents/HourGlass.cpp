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
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->SetTexture("BlackBackground.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalPosition({ 530.0f, -160.0f, 0.0f });

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("Hourglass");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("Hourglass", 0.07f, true));
		Renderer->ChangeFrameAnimation("Hourglass");
		Renderer->ScaleToTexture();
	}
}

void HourGlass::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

