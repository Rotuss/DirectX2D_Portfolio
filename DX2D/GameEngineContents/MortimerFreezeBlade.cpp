#include "PreCompile.h"
#include "MortimerFreezeBlade.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeBlade::MortimerFreezeBlade()
	: Renderer(nullptr)
	, BubbleRenderer(nullptr)
	, Collision(nullptr)
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
		Renderer->Off();
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 50,250,-1 });
		Collision->GetTransform().SetLocalPosition({ 0,150,-1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
	}

	int BubbleRandom = GameEngineRandom::MainRandom.RandomInt(0, 1);

	{
		BubbleRenderer = CreateComponent<GameEngineTextureRenderer>();
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleA_Start", FrameAnimation_DESC("IceBlade_BubbleA", 0, 6, 0.08f, false));
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleA_Up", FrameAnimation_DESC("IceBlade_BubbleA", 7, 12, 0.08f, false));
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleA_UpRepeat", FrameAnimation_DESC("IceBlade_BubbleA", 13, 15, 0.08f, true));
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleA_End", FrameAnimation_DESC("IceBlade_BubbleA", 16, 21, 0.08f, false));
		
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleB_Start", FrameAnimation_DESC("IceBlade_BubbleB", 0, 6, 0.08f, false));
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleB_Up", FrameAnimation_DESC("IceBlade_BubbleB", 7, 12, 0.08f, false));
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleB_UpRepeat", FrameAnimation_DESC("IceBlade_BubbleB", 13, 15, 0.08f, true));
		BubbleRenderer->CreateFrameAnimationFolder("IceBlade_BubbleB_End", FrameAnimation_DESC("IceBlade_BubbleB", 16, 21, 0.08f, false));

		if (0 == BubbleRandom)
		{
			BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleA_Start");
		}
		if (1 == BubbleRandom)
		{
			BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleB_Start");
		}
		
		BubbleRenderer->SetScaleModeImage();
		BubbleRenderer->ScaleToTexture();
		BubbleRenderer->SetPivot(PIVOTMODE::BOT);
		BubbleRenderer->GetTransform().SetLocalPosition(float4{ 0,-10,0 });
	}

	BubbleRenderer->AnimationBindEnd("IceBlade_BubbleA_Start", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleA_Up");
		});

	BubbleRenderer->AnimationBindStart("IceBlade_BubbleA_Up", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("IceBlade", true);
			Renderer->On();
		});

	BubbleRenderer->AnimationBindEnd("IceBlade_BubbleA_Up", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleA_UpRepeat");
		});

	BubbleRenderer->AnimationBindEnd("IceBlade_BubbleA_End", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	BubbleRenderer->AnimationBindEnd("IceBlade_BubbleB_Start", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleB_Up");
		});

	BubbleRenderer->AnimationBindStart("IceBlade_BubbleB_Up", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("IceBlade", true);
			Renderer->On();
		});

	BubbleRenderer->AnimationBindEnd("IceBlade_BubbleB_Up", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleB_UpRepeat");
		});

	BubbleRenderer->AnimationBindEnd("IceBlade_BubbleB_End", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	Renderer->AnimationBindFrame("IceBlade", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (16 == _Info.CurFrame)
			{
				BubbleRenderer->ChangeFrameAnimation("IceBlade_BubbleA_End");
			}
		});

	Renderer->AnimationBindEnd("IceBlade", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->Off();
		});
}

void MortimerFreezeBlade::Update(float _DeltaTime)
{
}

