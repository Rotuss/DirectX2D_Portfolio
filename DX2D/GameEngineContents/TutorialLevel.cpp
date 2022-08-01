#include "PreCompile.h"
#include "TutorialLevel.h"
#include "TutorialBackGround.h"
#include "Player.h"
#include "GlobalContents.h"

TutorialLevel::TutorialLevel() 
	: Renderer(nullptr)
{
}

TutorialLevel::~TutorialLevel() 
{
}

void TutorialLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
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

	TutorialBackGround* TutorialBG = CreateActor<TutorialBackGround>(OBJECTORDER::Tutorial);
	Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);

	{
		Renderer = TutorialBG->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("TutorialBackGround", FrameAnimation_DESC("TutorialBackGround", 0.05f, false));
		Renderer->ChangeFrameAnimation("TutorialBackGround");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	}
}

void TutorialLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void TutorialLevel::End()
{
}
