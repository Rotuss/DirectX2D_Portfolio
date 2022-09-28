#include "PreCompile.h"
#include "ReadyWALLOP.h"

ReadyWALLOP::ReadyWALLOP() 
	: Renderer(nullptr)
{
}

ReadyWALLOP::~ReadyWALLOP() 
{
}

void ReadyWALLOP::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("ReadyWALLOP", FrameAnimation_DESC("ReadyWALLOP", 0.08f, false));

		Renderer->ChangeFrameAnimation("ReadyWALLOP");
		Renderer->GetTransform().SetLocalScale({ 1280, 720 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}
}

void ReadyWALLOP::Update(float _DeltaTime)
{
}

