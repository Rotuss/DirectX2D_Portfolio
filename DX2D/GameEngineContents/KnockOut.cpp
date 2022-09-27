#include "PreCompile.h"
#include "KnockOut.h"

KnockOut::KnockOut() 
	: Renderer(nullptr)
{
}

KnockOut::~KnockOut() 
{
}

void KnockOut::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("KnockOut", FrameAnimation_DESC("KnockOut", 0.08f, false));
		
		Renderer->ChangeFrameAnimation("KnockOut");
		Renderer->GetTransform().SetLocalScale({ 1280, 720 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}
}

void KnockOut::Update(float _DeltaTime)
{
}

