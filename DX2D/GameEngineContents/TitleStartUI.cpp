#include "PreCompile.h"
#include "TitleStartUI.h"

TitleStartUI::TitleStartUI()
	: Renderer0(nullptr)
	, Renderer1(nullptr)
	, Renderer2(nullptr)
	, NewGameRenderer0(nullptr)
	, NewGameRenderer1(nullptr)
	, NewGameRenderer2(nullptr)
	, SelectOnBackground(nullptr)
	, SelectSlotColor(nullptr)
	, SelectSlotText(nullptr)
	, SelectPosition()
	, CurrentIndex(0)
{
}

TitleStartUI::~TitleStartUI() 
{
}

void TitleStartUI::Start()
{
	{
		GameEngineUIRenderer* MainRenderer = CreateComponent<GameEngineUIRenderer>();
		MainRenderer->SetTexture("slot_selection_bg.png");
		MainRenderer->ScaleToTexture();
		MainRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	}

	{
		Renderer0 = CreateComponent<GameEngineUIRenderer>();
		Renderer0->SetTexture("slot_selection_box_a.png");
		Renderer0->ScaleToTexture();
		Renderer0->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });
		NewGameRenderer0 = CreateComponent<GameEngineUIRenderer>();
		NewGameRenderer0->SetTexture("NewGameBlack.png");
		NewGameRenderer0->ScaleToTexture();
		NewGameRenderer0->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });

		Renderer1 = CreateComponent<GameEngineUIRenderer>();
		Renderer1->SetTexture("slot_selection_box_a.png");
		Renderer1->ScaleToTexture();
		Renderer1->GetTransform().SetLocalPosition({ 0.0f, 30.0f, 0.0f });
		NewGameRenderer1 = CreateComponent<GameEngineUIRenderer>();
		NewGameRenderer1->SetTexture("NewGameBlack.png");
		NewGameRenderer1->ScaleToTexture();
		NewGameRenderer1->GetTransform().SetLocalPosition({ 0.0f, 30.0f, 0.0f });

		Renderer2 = CreateComponent<GameEngineUIRenderer>();
		Renderer2->SetTexture("slot_selection_box_a.png");
		Renderer2->ScaleToTexture();
		Renderer2->GetTransform().SetLocalPosition({ 0.0f, -125.0f, 0.0f });
		NewGameRenderer2 = CreateComponent<GameEngineUIRenderer>();
		NewGameRenderer2->SetTexture("NewGameBlack.png");
		NewGameRenderer2->ScaleToTexture();
		NewGameRenderer2->GetTransform().SetLocalPosition({ 0.0f, -125.0f, 0.0f });
	}

	{
		SelectSlotColor = CreateComponent<GameEngineUIRenderer>();
		SelectSlotColor->CreateFrameAnimationFolder("slot_selection_box_b", FrameAnimation_DESC("slot_selection_box_b", 0, 0, 0.0f, false));
		SelectSlotColor->CreateFrameAnimationFolder("slot_selection_box_b_MM", FrameAnimation_DESC("slot_selection_box_b", 1, 1, 0.0f, false));
		SelectSlotColor->ChangeFrameAnimation("slot_selection_box_b");
		SelectSlotColor->ScaleToTexture();
		SelectSlotColor->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });

		SelectSlotText = CreateComponent<GameEngineUIRenderer>();
		SelectSlotText->CreateFrameAnimationFolder("NewGame", FrameAnimation_DESC("SelectText", 0, 0, 0.0f, false));
		SelectSlotText->CreateFrameAnimationFolder("SelectPlayerA", FrameAnimation_DESC("SelectText", 1, 1, 0.0f, false));
		SelectSlotText->CreateFrameAnimationFolder("SelectPlayerB", FrameAnimation_DESC("SelectText", 2, 2, 0.0f, false));
		SelectSlotText->ChangeFrameAnimation("NewGame");
		SelectSlotText->ScaleToTexture();
		SelectSlotText->GetTransform().SetLocalPosition({ 0.0f, 185.0f, 0.0f });

		SelectPosition.push_back({ 0.0f, 185.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, 30.0f, 0.0f });
		SelectPosition.push_back({ 0.0f, -125.0f, 0.0f });
	}
}

void TitleStartUI::Update(float _DeltaTime)
{
	// 일단 임시로 안 보이게끔 설정(그치만 옳은 방법은 아닌 듯하다)
	// 셀렉트 실행 별로 클래스를 둬서 따로 관리하는 것이 좋을 듯함.
	if (GameEngineInput::GetInst()->IsDown("Back"))
	{
		Renderer0->Off();
		Renderer1->Off();
		Renderer2->Off();
		NewGameRenderer0->Off();
		NewGameRenderer1->Off();
		NewGameRenderer2->Off();

		SelectSlotColor->Off();
		SelectSlotText->Off();
	}

	if (GameEngineInput::GetInst()->IsDown("Select"))
	{
		SelectIndex();
	}

	if (true == GameEngineInput::GetInst()->IsDown("Up"))
	{
		CurrentIndex -= 1;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
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
	SelectSlotText->GetTransform().SetLocalPosition(SelectPosition[CurrentIndex]);
}

void TitleStartUI::SelectIndex()
{
	switch (CurrentIndex)
	{
	case 0:
	{
		int a = 0;
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
	default:
		break;
	}
}

