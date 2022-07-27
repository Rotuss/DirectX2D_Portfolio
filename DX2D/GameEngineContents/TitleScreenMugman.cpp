#include "PreCompile.h"
#include "TitleScreenMugman.h"

TitleScreenMugman::TitleScreenMugman() 
	: Renderer(nullptr)
	, ReverseEvent(true)
{
}

TitleScreenMugman::~TitleScreenMugman() 
{
}

void TitleScreenMugman::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalPosition({ 300.0f, -10.0f, 0.0f });

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("TitleScreen");
		Dir.Move("Mugman");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("Mugman", FrameAnimation_DESC("Mugman", 1, 13, 0.07f, true));
		Renderer->ChangeFrameAnimation("Mugman");
		Renderer->AnimationBindEnd("Mugman", &TitleScreenMugman::EndFunction, this);
		Renderer->ScaleToTexture();
	}
}

void TitleScreenMugman::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

void TitleScreenMugman::EndFunction(const FrameAnimation_DESC& _Info)
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
