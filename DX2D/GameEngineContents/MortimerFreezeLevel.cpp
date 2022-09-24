#include "PreCompile.h"
#include "MortimerFreezeLevel.h"
#include "MortimerFreezeBackGround.h"
#include "MortimerFreezeBoss.h"
// Test
#include "Player.h"
#include "MsChalice.h"

MortimerFreezeLevel::MortimerFreezeLevel() 
	: Renderer(nullptr)
	, MoveTimer(-10.0f)
	, IsMove(false)
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

	{
		MsChalice* MSChalice = CreateActor<MsChalice>(OBJECTORDER::Player);

		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main-ColMap.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->Off();
		MSChalice->SetColMap(Renderer);
	}

	// 각 GoalPosVec 수치 재조정 필요
	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("sky.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 810, -300, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 810, -300, 100 });
		GoalPosVec.push_back({ 810, 100, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLA", FrameAnimation_DESC("SnowCult_NL_A", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 400, -430, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 400, -430, 100 });
		GoalPosVec.push_back({ 400, -30, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLB", FrameAnimation_DESC("SnowCult_NL_B", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 300, -200, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 300, -200, 100 });
		GoalPosVec.push_back({ 300, 200, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLC", FrameAnimation_DESC("SnowCult_NL_C", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLC");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -450, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -450, 100 });
		GoalPosVec.push_back({ 850, -50, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLD", FrameAnimation_DESC("SnowCult_NL_D", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLD");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -350, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -350, 100 });
		GoalPosVec.push_back({ 850, 50, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLE", FrameAnimation_DESC("SnowCult_NL_E", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLE");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -150, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -150, 100 });
		GoalPosVec.push_back({ 850, 250, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLF", FrameAnimation_DESC("SnowCult_NL_F", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLF");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1300, -200, 100 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 1300, -200, 100 });
		GoalPosVec.push_back({ 1300, 200, 100 });
	}

	/*{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("clouds.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -150, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("icebergs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -150, 100 });
	}*/

	/*{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("icebergs.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 800, -450 });
	}*/

	/*{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lake.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -430, 100 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("castle.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -200, 100 });
	}*/

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("min-main_front_layer.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition(float4{ 0.0f, 0.0f, -0.5f });
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
	GameEngineStatusWindow::AddDebugRenderTarget("BackBuffer", GameEngineDevice::GetBackBuffer());
	GameEngineStatusWindow::AddDebugRenderTarget("MainCamera", GetMainCamera()->GetCameraRenderTarget());
	GameEngineStatusWindow::AddDebugRenderTarget("UICamera", GetUICamera()->GetCameraRenderTarget());
	
	if (true == GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	Ph3MoveCheckUpdate(_DeltaTime);

	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	//if (/*2,3번째 발판 밟은 이후 움직임 시작*/)
	//{
	//	Ph3MoveCheck();
	//}

	// 카메라 좌우 막기 필요, 플레이어 이동 막기 필요
	//GetMainCameraActorTransform().SetLocalPosition(float4{ 800.0f + (Player::MainPlayer->GetTransform().GetLocalPosition().x * 0.1f), -610.0f } + float4::BACK * 100.0f);
	GetMainCameraActorTransform().SetLocalPosition(float4{ 830.0f,-610.0f });
	/*if (GetMainCameraActorTransform().GetLocalPosition().x <= 750)
	{
		GetMainCameraActorTransform().SetLocalPosition(float4{750.0f,-610.0f });
	}*/
}

void MortimerFreezeLevel::End()
{
}

void MortimerFreezeLevel::Ph3MoveCheck()
{
	IsMove = true;
	MoveTimer = 0.0f;
}

void MortimerFreezeLevel::Ph3MoveCheckUpdate(float _DeltaTime)
{
	if (false == IsMove)
	{
		return;
	}

	MoveTimer += _DeltaTime;
	float4 StartPos = { 830.0f,-610.0f };
	float4 GoalPos = { 830.0f,-210.0f }; // 수치 조정 필요

	float4 LerpPos = float4::Lerp(StartPos, GoalPos, MoveTimer);
	GetMainCameraActorTransform().SetLocalPosition(LerpPos);


	for (size_t i = 0; i < MoveVec.size(); i++)
	{
		float4 LerpPos = float4::Lerp(StartPosVec[i], GoalPosVec[i], MoveTimer);
		MoveVec[i]->SetLocalPosition(LerpPos);
	}

	if (MoveTimer >= 1.0f)
	{
		IsMove = false;
	}
}
