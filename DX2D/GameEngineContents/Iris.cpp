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
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

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
}

