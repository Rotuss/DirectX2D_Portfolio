#include "PreCompile.h"
#include "MortimerFreezeLevel.h"
#include "MortimerFreezeSnowPlatform.h"
#include "MortimerFreezeBackGround.h"
#include "MortimerFreezeBoss.h"
// Test
#include "Player.h"
#include "MsChalice.h"

#include <GameEngineCore/GameEngineBlur.h>

MortimerFreezeLevel::MortimerFreezeLevel()
	: Renderer(nullptr)
	, PPtr(nullptr)
	, MoveTimer(-10.0f)
	, IsMove(false)
{
}

MortimerFreezeLevel::~MortimerFreezeLevel()
{
}

std::vector<GameEngineTextureRenderer*> TmpVector;
void MortimerFreezeLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

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
		Renderer->GetTransform().SetLocalPosition({ 810, -300, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 810, -300, 300 });
		GoalPosVec.push_back({ 810, -300, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLA", FrameAnimation_DESC("SnowCult_NL_A", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 400, -430, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 400, -430, 300 });
		GoalPosVec.push_back({ 400, -230, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLB", FrameAnimation_DESC("SnowCult_NL_B", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 300, -200, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 300, -200, 300 });
		GoalPosVec.push_back({ 300, 00, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLC", FrameAnimation_DESC("SnowCult_NL_C", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLC");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -450, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -450, 300 });
		GoalPosVec.push_back({ 850, -250, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLD", FrameAnimation_DESC("SnowCult_NL_D", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLD");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -350, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -350, 300 });
		GoalPosVec.push_back({ 850, -150, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLE", FrameAnimation_DESC("SnowCult_NL_E", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLE");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -150, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -150, 300 });
		GoalPosVec.push_back({ 850, 50, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("NLF", FrameAnimation_DESC("SnowCult_NL_F", 0.1f, true));
		Renderer->ChangeFrameAnimation("NLF");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1300, -200, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 1300, -200, 300 });
		GoalPosVec.push_back({ 1300, 00, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("clouds.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -550, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 780, -550, 300 });
		GoalPosVec.push_back({ 780, -330, 300 });
	}

	/*{
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

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lower_sky_mountains.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -680, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 780, -680, 300 });
		GoalPosVec.push_back({ 780, -555, 300 });
	}

	/*{ 400 이동시
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lower_sky_mountains.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -370, 100 });
	}*/

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lake.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 780, -830, 300 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 780, -830, 300 });
		GoalPosVec.push_back({ 780, -620, 300 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("castle.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, 150, 50 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, 150, 50 });
		GoalPosVec.push_back({ 850, -400, 50 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("front_walls.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 850, -50, 50 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 850, -50, 50 });
		GoalPosVec.push_back({ 850, -700, 50 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 0, 0, 0 });
		GoalPosVec.push_back({ 0, -700, 0 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("min-main_front_layer.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition(float4{ 0.0f, 0.0f, -0.5f });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 0, 0, -0.5 });
		GoalPosVec.push_back({ 0, -700, -0.5 });
	}

	// Members 피벗 조정 필요
	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Members_Back", FrameAnimation_DESC("Members_Back", 0.15f, true));
		Renderer->ChangeFrameAnimation("Members_Back");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 795, -440 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 795, -440, 0 });
		GoalPosVec.push_back({ 795, -1140, 0 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("mid-main_back_seats.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 800, -290 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 800, -290, 0 });
		GoalPosVec.push_back({ 800, -990, 0 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Members_Front", FrameAnimation_DESC("Members_Front", 0.15f, true));
		Renderer->ChangeFrameAnimation("Members_Front");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 800, -490 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 800, -490, 0 });
		GoalPosVec.push_back({ 800, -1190, 0 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("min-main_front_layer.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 805, -530 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 805, -530, 0 });
		GoalPosVec.push_back({ 805, -1230, 0 });
	}

	{
		Renderer = MFBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("fg_candles_rock.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 820, -875, -10 });
		MoveVec.push_back(&Renderer->GetTransform());
		StartPosVec.push_back({ 820, -875, -10 });
		GoalPosVec.push_back({ 820, -1575, -10 });
	}
	GetMainCameraActorTransform().SetLocalPosition(float4{ 830.0f,-610.0f });

	{
		GameEngineActor* TmpActor = CreateActor<GameEngineActor>();
		TmpActor->GetTransform().SetWorldScale({ 1,1,1 });
		TmpActor->GetTransform().SetWorldPosition({ 810, 100, 0 });
		TmpActor->GetTransform().SetWorldRotation(float4::ZERO);
		MoveVec.push_back(&TmpActor->GetTransform());
		StartPosVec.push_back({ 810, 100, 0 });
		GoalPosVec.push_back({ 810, -550, 0 }); // 수치조정 필요

		GameEngineActor* TmpSubActor = CreateActor<GameEngineActor>();
		PPtr = TmpSubActor->CreateComponent<GameEngineTextureRenderer>();
		PPtr->SetParent(TmpActor);
		PPtr->GetTransform().SetLocalScale(float4{ 1,1,1 });
		PPtr->GetTransform().SetLocalPosition({ 0,0,0 });
		PPtr->GetTransform().SetWorldRotation(float4::ZERO);
		PPtr->Off();

		{
			GameEngineTextureRenderer* TmpRender = TmpSubActor->CreateComponent<GameEngineTextureRenderer>();
			TmpRender->SetParent(PPtr);
			TmpRender->GetTransform().SetWorldScale(float4::ONE);
			TmpRender->GetTransform().SetLocalPosition({ 0.0f, 1.0f,-0.8f });
			TmpVector.push_back(TmpRender);
		}
		{
			GameEngineTextureRenderer* TmpRender = TmpSubActor->CreateComponent<GameEngineTextureRenderer>();
			TmpRender->SetParent(PPtr);
			TmpRender->GetTransform().SetWorldScale(float4::ONE);
			TmpRender->GetTransform().SetLocalPosition({ std::cos(18 * GameEngineMath::DegreeToRadian),std::sin(18 * GameEngineMath::DegreeToRadian),-0.8f });
			TmpVector.push_back(TmpRender);
		}
		{
			GameEngineTextureRenderer* TmpRender = TmpSubActor->CreateComponent<GameEngineTextureRenderer>();
			TmpRender->SetParent(PPtr);
			TmpRender->GetTransform().SetWorldScale(float4::ONE);
			TmpRender->GetTransform().SetLocalPosition({ -std::cos(18 * GameEngineMath::DegreeToRadian),std::sin(18 * GameEngineMath::DegreeToRadian),-0.8f });
			TmpVector.push_back(TmpRender);
		}
		{
			GameEngineTextureRenderer* TmpRender = TmpSubActor->CreateComponent<GameEngineTextureRenderer>();
			TmpRender->SetParent(PPtr);
			TmpRender->GetTransform().SetWorldScale(float4::ONE);
			TmpRender->GetTransform().SetLocalPosition({ std::cos(54 * GameEngineMath::DegreeToRadian),-std::sin(54 * GameEngineMath::DegreeToRadian),-0.8f });
			TmpVector.push_back(TmpRender);
		}
		{
			GameEngineTextureRenderer* TmpRender = TmpSubActor->CreateComponent<GameEngineTextureRenderer>();
			TmpRender->SetParent(PPtr);
			TmpRender->GetTransform().SetWorldScale(float4::ONE);
			TmpRender->GetTransform().SetLocalPosition({ -std::cos(54 * GameEngineMath::DegreeToRadian),-std::sin(54 * GameEngineMath::DegreeToRadian),-0.8f });
			TmpVector.push_back(TmpRender);
		}

		for (size_t i = 0; i < TmpVector.size(); i++)
		{
			MortimerFreezeSnowPlatform* Ptr = CreateActor<MortimerFreezeSnowPlatform>(OBJECTORDER::SnowPlatform);
			Ptr->SetPlatformType(static_cast<PlatformType>(i + 1));
			Ptr->SetFollowObj(&TmpVector[i]->GetTransform());
		}

		PPtr->GetTransform().SetLocalScale(float4{ 1,1,1 }*300);
		PPtr->GetTransform().SetLocalRotation({ 50,0,0 });
	}
}

void MortimerFreezeLevel::Update(float _DeltaTime)
{
	GameEngineStatusWindow::AddDebugRenderTarget("BackBuffer", GameEngineDevice::GetBackBuffer());
	GameEngineStatusWindow::AddDebugRenderTarget("MainCamera", GetMainCamera()->GetCameraRenderTarget());
	GameEngineStatusWindow::AddDebugRenderTarget("UICamera", GetUICamera()->GetCameraRenderTarget());

	Ph3MoveCheckUpdate(_DeltaTime);

	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (true == GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	if (2 == MsChalice::Chalice->GetPlatformCount() /*|| true == GameEngineInput::GetInst()->IsDown("Appear_SnowPlatform")*/)
	{
		Ph3MoveCheck();
	}

	// 카메라 좌우 막기 필요, 플레이어 이동 막기 필요
	//GetMainCameraActorTransform().SetLocalPosition(float4{ 800.0f + (Player::MainPlayer->GetTransform().GetLocalPosition().x * 0.1f), -610.0f } + float4::BACK * 100.0f);
	/*if (GetMainCameraActorTransform().GetLocalPosition().x <= 750)
	{
		GetMainCameraActorTransform().SetLocalPosition(float4{750.0f,-610.0f });
	}*/

	if (nullptr != PPtr)
	{
		PPtr->GetTransform().SetLocalRotate({ 0,0,65 * _DeltaTime });
	}
}

void MortimerFreezeLevel::End()
{
}

void MortimerFreezeLevel::Ph3MoveCheck()
{
	if (true == IsMove)
	{
		return;
	}

	IsMove = true;
	MoveTimer = 0.0f;
}

void MortimerFreezeLevel::Ph3MoveCheckUpdate(float _DeltaTime)
{
	if (false == IsMove)
	{
		return;
	}
	if (MoveTimer >= 2.0f)
	{
		MortimerFreezeBoss::MFBoss->ChangPhase3();
		return;
	}

	MoveTimer += _DeltaTime;
	float4 StartPos = { 830.0f,-610.0f };
	float4 GoalPos = { 830.0f,-320.0f }; // 수치 조정 필요

	float4 LerpPos = float4::Lerp(StartPos, GoalPos, MoveTimer / 2);
	GetMainCameraActorTransform().SetLocalPosition(LerpPos);


	for (size_t i = 0; i < MoveVec.size(); i++)
	{
		float4 LerpPos = float4::Lerp(StartPosVec[i], GoalPosVec[i], MoveTimer / 2);
		MoveVec[i]->SetLocalPosition(LerpPos);
	}
}
