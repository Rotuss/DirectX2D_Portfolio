#include "PreCompile.h"
#include "TutorialLevel.h"
#include "TutorialBackGround.h"
#include "Player.h"
#include "GlobalContents.h"

TutorialLevel::TutorialLevel() 
	: Renderer(nullptr)
	, ParryA(nullptr)
	, ParryB(nullptr)
	, ParryC(nullptr)
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
	//NewPlayer->GetTransform().SetLocalPosition({ 300, -750, -3 });

	{
		Renderer = TutorialBG->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("TutorialBackGround", FrameAnimation_DESC("TutorialBackGround", 0.05f, false));
		Renderer->ChangeFrameAnimation("TutorialBackGround");
		Renderer->AnimationBindEnd("TutorialBackGround", std::bind(&TutorialLevel::BGEndFunction, this, std::placeholders::_1));
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	}

	// Test
	{
		Monster* actor = CreateActor<Monster>(OBJECTORDER::Monster);
		actor->GetTransform().SetLocalPosition({ 300.0f, 0.0f, 100.0f });
		actor->GetTransform().SetWorldScale(float4(1.0f, 1.f, 1.0f));
	}

	{
		ParryA = TutorialBG->CreateComponent<GameEngineTextureRenderer>();
		ParryA->CreateFrameAnimationFolder("ParryWheatA", FrameAnimation_DESC("ParryWheatA", 0.1f, true));
		ParryA->ChangeFrameAnimation("ParryWheatA");
		ParryA->ScaleToTexture();
		ParryA->GetTransform().SetLocalPosition({ 895, -740 });
		ParryA->Off();
	}

	{
		ParryB = TutorialBG->CreateComponent<GameEngineTextureRenderer>();
		ParryB->CreateFrameAnimationFolder("ParryWheatB", FrameAnimation_DESC("ParryWheatB", 0.1f, true));
		ParryB->ChangeFrameAnimation("ParryWheatB");
		ParryB->ScaleToTexture();
		ParryB->GetTransform().SetLocalPosition({ 258, -433 });
		ParryB->Off();
	}

	{
		ParryC = TutorialBG->CreateComponent<GameEngineTextureRenderer>();
		ParryC->CreateFrameAnimationFolder("ParryWheatC", FrameAnimation_DESC("ParryWheatC", 0.1f, true));
		ParryC->ChangeFrameAnimation("ParryWheatC");
		ParryC->ScaleToTexture();
		ParryC->GetTransform().SetLocalPosition({ 1100, -310 });
		ParryC->Off();
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

void TutorialLevel::BGEndFunction(const FrameAnimation_DESC& _Info)
{
	ParryA->On();
}
