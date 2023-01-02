#include "PreCompile.h"
#include "StoryLevel.h"
#include <GameEngineCore/GameEngineBlur.h>

StoryLevel::StoryLevel() 
	: Renderer(nullptr)
	, StorySound()
{
}

StoryLevel::~StoryLevel() 
{
}

void StoryLevel::LevelStartEvent()
{
	StorySound = GameEngineSound::SoundPlayControl("mus_dlc_intro_start.wav");
}

void StoryLevel::LevelEndEvent()
{
}

void StoryLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	GameEngineActor* AniRenderer = CreateActor<GameEngineActor>(OBJECTORDER::Title);

	Renderer = AniRenderer->CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("StoryAnim", FrameAnimation_DESC("IntroStory", 0.05f, false));
	Renderer->ChangeFrameAnimation("StoryAnim");
	Renderer->ScaleToTexture();
	Renderer->GetTransform().SetWorldScale({ 1280, 720});

	Renderer->AnimationBindFrame("StoryAnim", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if ( 393 == _Info.CurFrame)
			{
				StorySound.Stop();
				StorySound = GameEngineSound::SoundPlayControl("mus_dlc_intro.wav");
			}
		});
	Renderer->AnimationBindEnd("StoryAnim", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StorySound.Stop();
			GEngine::ChangeLevel("World");
		});
}

void StoryLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (GameEngineInput::GetInst()->IsDown("ChangeNextWorld"))
	{
		StorySound.Stop();
		GEngine::ChangeLevel("World");
	}
}

void StoryLevel::End()
{
}
