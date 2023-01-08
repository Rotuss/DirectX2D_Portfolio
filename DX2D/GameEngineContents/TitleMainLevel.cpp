#include "PreCompile.h"
#include "TitleMainLevel.h"
#include "TItleMainBackGround.h"
#include "TitleStartUI.h"
// �ɼ� UI ���
#include "Iris.h"
#include "HourGlass.h"
#include "GlobalContents.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineBlur.h>

TitleMainLevel::TitleMainLevel() 
	: Renderer(nullptr)
	, SelectRenderer(nullptr)
	, SelectPosition()
	, CurrentIndex(0)
	, SelectUICheck(false)
{
}

TitleMainLevel::~TitleMainLevel() 
{
}

void TitleMainLevel::LevelStartEvent()
{
}

void TitleMainLevel::LevelEndEvent()
{
}

void TitleMainLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetIrisCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	if (false == GameEngineInput::GetInst()->IsKey("ChangeNextWorld"))
	{
		GameEngineInput::GetInst()->CreateKey("ChangeNextWorld", 'P');
	}

	if (false == GameEngineInput::GetInst()->IsKey("Select"))
	{
		GameEngineInput::GetInst()->CreateKey("Select", 'Z');
		GameEngineInput::GetInst()->CreateKey("Back", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
	}

	TItleMainBackGround* TitleBackGround = CreateActor<TItleMainBackGround>(OBJECTORDER::Title);
	
	{
		Renderer = TitleBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("cuphead_secondary_title_screen.png");
		Renderer->ScaleToTexture();
	}

	{
		Renderer = TitleBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("MainUI", FrameAnimation_DESC("MainUI", 0, 0, false));
		Renderer->ChangeFrameAnimation("MainUI");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0.0f, 40.0f, 0.0f });
	}

	{
		SelectRenderer = TitleBackGround->CreateComponent<GameEngineTextureRenderer>();
		SelectRenderer->CreateFrameAnimationFolder("MainUIStart", FrameAnimation_DESC("MainUI", 1, 1, false));
		SelectRenderer->CreateFrameAnimationFolder("MainUIOption", FrameAnimation_DESC("MainUI", 2, 2, false));
		SelectRenderer->CreateFrameAnimationFolder("MainUIDLC", FrameAnimation_DESC("MainUI", 3, 3, false));
		SelectRenderer->CreateFrameAnimationFolder("MainUIEnd", FrameAnimation_DESC("MainUI", 4, 4, false));
		SelectRenderer->ChangeFrameAnimation("MainUIStart");
		SelectRenderer->ScaleToTexture();
		SelectRenderer->GetTransform().SetLocalPosition({ 0.0f, 91.0f, 0.0f });
		
		SelectPosition.push_back({ 0.0f, 91.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, 57.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, 26.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, -7.0f, 0.0f });
	}
}

void TitleMainLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (true == SelectUICheck)
	{
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("Select"))
	{
		GameEngineSound::SoundPlayOneShot("Menu_Category_Select.wav");
		//Iris* FX = CreateActor<Iris>(OBJECTORDER::Title);
		//FX->GetRenderer()->AnimationBindEnd("IrisFX", &TitleMainLevel::EndFunction, this);
		SelectIndex();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Up"))
	{
		GameEngineSound::SoundPlayOneShot("Menu_Move.wav");
		CurrentIndex -= 1;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		GameEngineSound::SoundPlayOneShot("Menu_Move.wav");
		CurrentIndex += 1;
	}

	if (0 > CurrentIndex)
	{
		CurrentIndex = 3;
	}
	if (3 < CurrentIndex)
	{
		CurrentIndex = 0;
	}

	switch (CurrentIndex)
	{
	case 0:
	{
		SelectRenderer->ChangeFrameAnimation("MainUIStart");
		break;
	}
	case 1:
	{
		SelectRenderer->ChangeFrameAnimation("MainUIOption");
		break;
	}
	case 2:
	{
		SelectRenderer->ChangeFrameAnimation("MainUIDLC");
		break;
	}
	case 3:
	{
		SelectRenderer->ChangeFrameAnimation("MainUIEnd");
		break;
	}
	default:
		break;
	}
	SelectRenderer->GetTransform().SetLocalPosition(SelectPosition[CurrentIndex]);
}

void TitleMainLevel::End()
{
}

void TitleMainLevel::SelectIndex()
{
	switch (CurrentIndex)
	{
	case 0:
	{
		TitleStartUI* StartUI = CreateActor<TitleStartUI>(OBJECTORDER::UI);
		break;
	}
	case 1:
	{
		int a = 0;
		break;
	}
	case 2:
	{
		int a = 0;
		break;
	}
	case 3:
	{
		int a = 0;
		break;
	}
	default:
		break;
	}
}
