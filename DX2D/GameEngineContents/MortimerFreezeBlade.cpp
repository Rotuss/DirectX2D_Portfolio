#include "PreCompile.h"
#include "MortimerFreezeBlade.h"

MortimerFreezeBlade::MortimerFreezeBlade() 
{
}

MortimerFreezeBlade::~MortimerFreezeBlade() 
{
}

void MortimerFreezeBlade::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("IceBlade", FrameAnimation_DESC("IceBlade", 0.08f, false));
		
		Renderer->ChangeFrameAnimation("IceBlade");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
	}

	Renderer->AnimationBindEnd("IceBlade", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->GetActor()->Death();
		});
}

void MortimerFreezeBlade::Update(float _DeltaTime)
{
}

