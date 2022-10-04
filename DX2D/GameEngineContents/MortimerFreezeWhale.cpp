#include "PreCompile.h"
#include "MortimerFreezeWhale.h"

MortimerFreezeWhale::MortimerFreezeWhale() 
	: Renderer(nullptr)
{
}

MortimerFreezeWhale::~MortimerFreezeWhale() 
{
}

void MortimerFreezeWhale::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WhaleOutro", FrameAnimation_DESC("Wizard_Whale_Outro", 0.06f, false));
		
		Renderer->ChangeFrameAnimation("WhaleOutro");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);
	}

	Renderer->AnimationBindEnd("WhaleOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});
}

void MortimerFreezeWhale::Update(float _DeltaTime)
{
}

