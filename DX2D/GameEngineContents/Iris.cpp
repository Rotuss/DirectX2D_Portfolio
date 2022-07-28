#include "PreCompile.h"
#include "Iris.h"

Iris::Iris()
	: Renderer(nullptr)
{
}

Iris::~Iris()
{
}

void Iris::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("IrisFX");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("IrisFX", FrameAnimation_DESC("IrisFX", 0.08f, false));
		Renderer->ChangeFrameAnimation("IrisFX");
		Renderer->GetTransform().SetLocalScale({ 1280, 720 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}
}

void Iris::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

