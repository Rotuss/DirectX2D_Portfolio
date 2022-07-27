#include "PreCompile.h"
#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

TitleLogo::TitleLogo() 
	: Renderer(nullptr)
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	GetTransform().SetLocalScale({ 1, 1, 1 });

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Texture");
		Dir.Move("MDHR_Logo");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		Renderer->CreateFrameAnimationFolder("Logo", FrameAnimation_DESC("MDHR_Logo", 0.05f, false));
		Renderer->ChangeFrameAnimation("Logo");
		Renderer->AnimationBindEnd("Logo", &TitleLogo::EndFunction, this);
		Renderer->GetTransform().SetLocalScale({ 1280, 720, 100 });
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}
}

void TitleLogo::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);
}

void TitleLogo::End()
{
}

void TitleLogo::EndFunction(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Title");
}
