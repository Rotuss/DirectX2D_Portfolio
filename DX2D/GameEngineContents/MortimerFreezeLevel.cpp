#include "PreCompile.h"
#include "MortimerFreezeLevel.h"
#include "MortimerFreezeBackGround.h"
#include "MortimerFreezeBoss.h"
// Test
#include "Player.h"

MortimerFreezeLevel::MortimerFreezeLevel() 
	: Renderer(nullptr)
{
}

MortimerFreezeLevel::~MortimerFreezeLevel() 
{
}

void MortimerFreezeLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	MortimerFreezeBackGround* MFBackGround = CreateActor<MortimerFreezeBackGround>(OBJECTORDER::Boss);
	MortimerFreezeBoss* MFBoss = CreateActor<MortimerFreezeBoss>(OBJECTORDER::Boss);
	// 좌상단
	//MFBoss->GetTransform().SetLocalPosition({ 300, -380, -1 });
	// 우상단
	//MFBoss->GetTransform().SetLocalPosition({ 1350, -380, -1 });
	// Test
	{
		Player* NewPlayer = CreateActor<Player>(OBJECTORDER::Player);
		//NewPlayer->GetTransform().SetLocalPosition({ 750, -380, -1 });

		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main-ColMap.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->Off();
		NewPlayer->SetColMap(Renderer);
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("sky.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 810, -300, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLA", FrameAnimation_DESC("SnowCult_NL_A", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 400, -430, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLB", FrameAnimation_DESC("SnowCult_NL_B", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 300, -200, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLC", FrameAnimation_DESC("SnowCult_NL_C", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLC");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -450, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLD", FrameAnimation_DESC("SnowCult_NL_D", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLD");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -350, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLE", FrameAnimation_DESC("SnowCult_NL_E", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLE");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -150, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLF", FrameAnimation_DESC("SnowCult_NL_F", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLF");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1300, -200, 100 });
	}

	/*{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("clouds.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -550, 100 });
	}*/

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("icebergs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 800, -450 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	}

	// Members 피벗 조정 필요
	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Members_Back", FrameAnimation_DESC("Members_Back", 0.15f, true));
		Renderer->ChangeFrameAnimation("Members_Back");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 795, -440 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main_back_seats.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 800, -290 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Members_Front", FrameAnimation_DESC("Members_Front", 0.15f, true));
		Renderer->ChangeFrameAnimation("Members_Front");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 800, -490 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("min-main_front_layer.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 805, -530 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("fg_candles_rock.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 820, -875, -10 });
	}
}

void MortimerFreezeLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void MortimerFreezeLevel::End()
{
}
