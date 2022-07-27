#include "PreCompile.h"
#include "TitleScreenChalice.h"

TitleScreenChalice::TitleScreenChalice() 
	: Renderer(nullptr)
	, ReverseEvent(true)
{
}

TitleScreenChalice::~TitleScreenChalice() 
{
}

void TitleScreenChalice::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalPosition({ 0.0f, -50.0f, 0.0f });

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");
		Dir.Move("Chalice");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("Chalice", FrameAnimation_DESC("Chalice", 0.07f, true));
		Renderer->ChangeFrameAnimation("Chalice");
		Renderer->AnimationBindEnd("Chalice", &TitleScreenChalice::EndFunction, this);
		Renderer->ScaleToTexture();
	}
}

void TitleScreenChalice::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

void TitleScreenChalice::EndFunction(const FrameAnimation_DESC& _Info)
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
