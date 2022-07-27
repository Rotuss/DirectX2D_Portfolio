#include "PreCompile.h"
#include "TitleScreenCuphead.h"

TitleScreenCuphead::TitleScreenCuphead() 
	: Renderer(nullptr)
	, ReverseEvent(true)
{
}

TitleScreenCuphead::~TitleScreenCuphead() 
{
}

void TitleScreenCuphead::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalPosition({ -300.0f, -10.0f, 0.0f });

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");
		Dir.Move("Cuphead");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("Cuphead", FrameAnimation_DESC("Cuphead", 0, 12, 0.07f, true));
		Renderer->ChangeFrameAnimation("Cuphead");
		Renderer->AnimationBindEnd("Cuphead", &TitleScreenCuphead::EndFunction, this);
		Renderer->ScaleToTexture();
	}
}

void TitleScreenCuphead::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

void TitleScreenCuphead::EndFunction(const FrameAnimation_DESC& _Info)
{
	if (true == ReverseEvent)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		//Renderer->GetTransform().PixLocalPositiveX();
		ReverseEvent = false;
	}
	else if (false == ReverseEvent)
	{
		//Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().PixLocalPositiveX();
		ReverseEvent = true;
	}
}
