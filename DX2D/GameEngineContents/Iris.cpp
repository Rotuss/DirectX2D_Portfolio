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
	std::vector<unsigned int> Rev;
	for (int i = 0; i < 17; i++)
	{
		Rev.push_back(16 - i);
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("IrisFX", FrameAnimation_DESC("IrisFX", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("IrisFXRev", FrameAnimation_DESC("IrisFX", Rev, 0.08f, false));
	}
}

void Iris::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

