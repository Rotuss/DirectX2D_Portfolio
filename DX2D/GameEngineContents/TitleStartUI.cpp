#include "PreCompile.h"
#include "TitleStartUI.h"
#include "TitleMainLevel.h"
#include "HourGlass.h"

TitleStartUI::TitleStartUI()
	: MainRenderer(nullptr)
	, Renderer0(nullptr)
	, Renderer1(nullptr)
	, Renderer2(nullptr)
	, NewGameRenderer0(nullptr)
	, NewGameRenderer1(nullptr)
	, NewGameRenderer2(nullptr)
	, NewGameText(nullptr)
	, SelectOnBackground(nullptr)
	, SelectSlotColor(nullptr)
	, SelectSlotText(nullptr)
	, SelectCuphead(nullptr)
	, SelectMugman(nullptr)
	, SelectPosition()
	, CurrentIndex(0)
	, PlayerIndex(0)
	, FirstCheck(false)
	, SelectCheck(false)
	, AnimCheck(false)
{
}

TitleStartUI::~TitleStartUI() 
{
}

void TitleStartUI::Start()
{
	GetLevel<TitleMainLevel>()->SetSelectUICheck(true);

	{
		MainRenderer = CreateComponent<GameEngineTextureRenderer>();
		MainRenderer->SetTexture("slot_selection_bg.png");
		MainRenderer->ScaleToTexture();
		MainRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	}

	{
		Renderer0 = CreateComponent<GameEngineTextureRenderer>();
		Renderer0->SetTexture("slot_selection_box_a.png");
		Renderer0->ScaleToTexture();
		Renderer0->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });
		NewGameRenderer0 = CreateComponent<GameEngineTextureRenderer>();
		NewGameRenderer0->SetTexture("NewGameBlack.png");
		NewGameRenderer0->ScaleToTexture();
		NewGameRenderer0->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });

		Renderer1 = CreateComponent<GameEngineTextureRenderer>();
		Renderer1->SetTexture("slot_selection_box_a.png");
		Renderer1->ScaleToTexture();
		Renderer1->GetTransform().SetLocalPosition({ 0.0f, 30.0f, 0.0f });
		NewGameRenderer1 = CreateComponent<GameEngineTextureRenderer>();
		NewGameRenderer1->SetTexture("NewGameBlack.png");
		NewGameRenderer1->ScaleToTexture();
		NewGameRenderer1->GetTransform().SetLocalPosition({ 0.0f, 30.0f, 0.0f });

		Renderer2 = CreateComponent<GameEngineTextureRenderer>();
		Renderer2->SetTexture("slot_selection_box_a.png");
		Renderer2->ScaleToTexture();
		Renderer2->GetTransform().SetLocalPosition({ 0.0f, -125.0f, 0.0f });
		NewGameRenderer2 = CreateComponent<GameEngineTextureRenderer>();
		NewGameRenderer2->SetTexture("NewGameBlack.png");
		NewGameRenderer2->ScaleToTexture();
		NewGameRenderer2->GetTransform().SetLocalPosition({ 0.0f, -125.0f, 0.0f });
	}

	{
		SelectSlotColor = CreateComponent<GameEngineTextureRenderer>();
		SelectSlotColor->CreateFrameAnimationFolder("slot_selection_box_b", FrameAnimation_DESC("slot_selection_box_b", 0, 0, 0.0f, false));
		SelectSlotColor->CreateFrameAnimationFolder("slot_selection_box_b_MM", FrameAnimation_DESC("slot_selection_box_b", 1, 1, 0.0f, false));
		SelectSlotColor->ChangeFrameAnimation("slot_selection_box_b");
		SelectSlotColor->ScaleToTexture();
		SelectSlotColor->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });

		NewGameText = CreateComponent<GameEngineTextureRenderer>();
		NewGameText->SetTexture("NewGame.png");
		NewGameText->ScaleToTexture();
		NewGameText->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });

		SelectPosition.push_back({ 0.0f, 185.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, 30.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, -125.0f, 0.0f });
	}

	{
		SelectSlotText = CreateComponent<GameEngineTextureRenderer>();
		SelectSlotText->CreateFrameAnimationFolder("SelectPlayerA", FrameAnimation_DESC("SelectText", 0, 0, 0.0f, false));
		SelectSlotText->CreateFrameAnimationFolder("SelectPlayerB", FrameAnimation_DESC("SelectText", 1, 1, 0.0f, false));
		SelectSlotText->ChangeFrameAnimation("SelectPlayerA");
		SelectSlotText->ScaleToTexture();
		SelectSlotText->GetTransform().SetLocalPosition({ -150.0f, 185.0f, 0.0f });
		SelectSlotText->Off();

		SelectCuphead = CreateComponent<GameEngineTextureRenderer>();
		SelectCuphead->CreateFrameAnimationFolder("SelectPlayerCHOff", FrameAnimation_DESC("CHOff", 0.1f, true));
		SelectCuphead->CreateFrameAnimationFolder("SelectPlayerCHOn", FrameAnimation_DESC("CHOn", 0.1f, true));
		SelectCuphead->CreateFrameAnimationFolder("SelectPlayerCHSelect", FrameAnimation_DESC("CHSelect", 0.1f, false));
		SelectCuphead->ChangeFrameAnimation("SelectPlayerCHOn");
		SelectCuphead->ScaleToTexture();
		SelectCuphead->GetTransform().SetLocalPosition({ 50.0f, 185.0f, 0.0f });
		SelectCuphead->Off();

		SelectCuphead->AnimationBindEnd("SelectPlayerCHSelect", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				GlobalContents::Actors::BGM.Stop();
				HourGlass* Hourglass = GetLevel()->CreateActor<HourGlass>(OBJECTORDER::Title);
				Hourglass->GetRenderer()->AnimationBindEnd("Hourglass", [/*&*/=](const FrameAnimation_DESC& _Info)
					{
						GlobalContents::Actors::IsTimeOver = true;
					});
			});

		SelectMugman = CreateComponent<GameEngineTextureRenderer>();
		SelectMugman->CreateFrameAnimationFolder("SelectPlayerMMOff", FrameAnimation_DESC("MMOff", 0.1f, true));
		SelectMugman->CreateFrameAnimationFolder("SelectPlayerMMOn", FrameAnimation_DESC("MMOn", 0.1f, true));
		SelectMugman->CreateFrameAnimationFolder("SelectPlayerMMSelect", FrameAnimation_DESC("MMSelect", 0.1f, false));
		SelectMugman->ChangeFrameAnimation("SelectPlayerMMOff");
		SelectMugman->ScaleToTexture();
		SelectMugman->GetTransform().SetLocalPosition({ 200.0f, 185.0f, 0.0f });
		SelectMugman->Off();
	}
}

void TitleStartUI::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("Back"))
	{
		GameEngineSound::SoundPlayOneShot("Menu_Category_Select.wav");
		
		if (true == SelectCheck)
		{
			SelectCheck = false;
			
			if (1 == PlayerIndex)
			{
				PlayerIndex = 0;
				SelectSlotColor->ChangeFrameAnimation("slot_selection_box_b");
				SelectSlotText->ChangeFrameAnimation("SelectPlayerA");
				SelectCuphead->ChangeFrameAnimation("SelectPlayerCHOn");
				SelectMugman->ChangeFrameAnimation("SelectPlayerMMOff");
			}
			NewGameText->On();
			SelectSlotText->Off();
			SelectCuphead->Off();
			SelectMugman->Off();
		}
		else
		{
			Death();
			GetLevel<TitleMainLevel>()->SetSelectUICheck(false);
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Select"))
	{
		if (false == FirstCheck)
		{
			FirstCheck = true;
			return;
		}

		GameEngineSound::SoundPlayOneShot("Menu_CardDown.wav");
		
		if (true == SelectCheck)
		{
			AnimPlayerIndex();
			return;
		}
		SelectIndex();
	}

	if (true == GlobalContents::Actors::IsTimeOver)
	{
		AddAccTime(GameEngineTime::GetDeltaTime());

		if (4.0f <= GetAccTime())
		{
			ReSetAccTime();
			GlobalContents::Actors::IsTimeOver = false;

			GEngine::ChangeLevel("Story");
		}
	}

	if (true == AnimCheck)
	{
		return;
	}

	if (true == SelectCheck)
	{
		if (true == GameEngineInput::GetInst()->IsDown("Left"))
		{
			GameEngineSound::SoundPlayOneShot("Menu_Move.wav");
			PlayerIndex -= 1;
		}
		if (true == GameEngineInput::GetInst()->IsDown("Right"))
		{
			GameEngineSound::SoundPlayOneShot("Menu_Move.wav");
			PlayerIndex += 1;
		}

		if (0 > PlayerIndex)
		{
			PlayerIndex = 1;
		}
		if (1 < PlayerIndex)
		{
			PlayerIndex = 0;
		}

		if (0 == PlayerIndex)
		{
			SelectSlotColor->ChangeFrameAnimation("slot_selection_box_b");
			SelectSlotText->ChangeFrameAnimation("SelectPlayerA");
			SelectCuphead->ChangeFrameAnimation("SelectPlayerCHOn");
			SelectMugman->ChangeFrameAnimation("SelectPlayerMMOff");
		}
		else if (1 == PlayerIndex)
		{
			SelectSlotColor->ChangeFrameAnimation("slot_selection_box_b_MM");
			SelectSlotText->ChangeFrameAnimation("SelectPlayerB");
			SelectCuphead->ChangeFrameAnimation("SelectPlayerCHOff");
			SelectMugman->ChangeFrameAnimation("SelectPlayerMMOn");
		}

		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Up"))
	{
		GameEngineSound::SoundPlayOneShot("Menu_Cardflip.wav");
		CurrentIndex -= 1;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		GameEngineSound::SoundPlayOneShot("Menu_Cardflip.wav");
		CurrentIndex += 1;
	}

	if (0 > CurrentIndex)
	{
		CurrentIndex = 2;
	}
	if (2 < CurrentIndex)
	{
		CurrentIndex = 0;
	}

	SelectSlotColor->GetTransform().SetLocalPosition(SelectPosition[CurrentIndex]);
	NewGameText->GetTransform().SetLocalPosition(SelectPosition[CurrentIndex]);
	SelectSlotText-> GetTransform().SetLocalPosition(SelectPosition[CurrentIndex] + float4(-150.0f, 0.0f, 0.0f, 0.0f));
	SelectCuphead->GetTransform().SetLocalPosition(SelectPosition[CurrentIndex] + float4(50.0f, 0.0f, 0.0f, 0.0f));
	SelectMugman->GetTransform().SetLocalPosition(SelectPosition[CurrentIndex] + float4(200.0f, 0.0f, 0.0f, 0.0f));
}

void TitleStartUI::SelectIndex()
{
	switch (CurrentIndex)
	{
	case 0:
	{
		SelectCheck = true;
		NewGameText->Off();
		SelectSlotText->On();
		SelectCuphead->On();
		SelectMugman->On();

		break;
	}
	case 1:
	{
		SelectCheck = true;
		NewGameText->Off();
		SelectSlotText->On();
		SelectCuphead->On();
		SelectMugman->On();

		break;
	}
	case 2:
	{
		SelectCheck = true;
		NewGameText->Off();
		SelectSlotText->On();
		SelectCuphead->On();
		SelectMugman->On();

		break;
	}
	default:
		break;
	}
}

void TitleStartUI::AnimPlayerIndex()
{
	if (1 == PlayerIndex)
	{
		return;
	}

	AnimCheck = true;
	GameEngineSound::SoundPlayOneShot("Menu_Ready.wav");
	SelectCuphead->ChangeFrameAnimation("SelectPlayerCHSelect");
}

