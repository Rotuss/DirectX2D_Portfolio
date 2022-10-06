#include "PreCompile.h"
#include "OverWorldCuphead.h"
#include "Iris.h"
#include "HourGlass.h"

OverWorldCuphead* OverWorldCuphead::OWCuphead = nullptr;

OverWorldCuphead::OverWorldCuphead() 
	: Renderer(nullptr)
	, RendererInteraction(nullptr)
	, ColRenderer(nullptr)
	, ColorCheck(nullptr)
	, Collision(nullptr)
	, SnowTextureBG0(nullptr)
	, SnowTextureBG1(nullptr)
	, SnowTexture(nullptr)
	, SnowTextureCorp(nullptr)
	, StateManager()
	, CurStateName("")
	, CurUpDownName("")
	, CurDir(OWCupheadDir::Down)
	, SoundRepeatTime(0.5f)
	, Speed(300.0f)
	, IsHourGlassOn(false)
	, IsUIOn(false)
{
	OWCuphead = this;
}

OverWorldCuphead::~OverWorldCuphead() 
{
}

CollisionReturn OverWorldCuphead::SnowUpdateCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("OWCHSelect")
		&& true == IsUIOn)
	{
		GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_StartLevel.wav");
		GlobalContents::Actors::BGM.Stop();
		Iris* FX = GetLevel()->CreateActor<Iris>(OBJECTORDER::Title);
		FX->SetAnimType(AnimType::Front);
		FX->GetRenderer()->AnimationBindEnd("IrisFX", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				IsHourGlassOn = true;
				FX->Death();
			});
	}
	
	if (true == GameEngineInput::GetInst()->IsDown("OWCHSelect")
		&& false == IsUIOn)
	{
		GameEngineSound::SoundPlayOneShot("sfx_worldmap_level_menu_up.wav");
		GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
		
		IsUIOn = true;
		SnowTextureBG0->On();
		SnowTextureBG1->On();
		SnowTexture->On();
		SnowTextureCorp->On();
	}
	if (true == GameEngineInput::GetInst()->IsDown("OWCHOut"))
	{
		IsUIOn = false;
		SnowTextureBG0->Off();
		SnowTextureBG1->Off();
		SnowTexture->Off();
		SnowTextureCorp->Off();
	}

	return CollisionReturn::ContinueCheck;
}

CollisionReturn OverWorldCuphead::SnowEnterCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// Z 상호작용 키기
	GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_BubbleAppear.wav");
	RendererInteraction->On();

	return CollisionReturn::ContinueCheck;
}

CollisionReturn OverWorldCuphead::SnowExitCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// Z 상호작용 끄기
	GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_BubbleDisappear.wav");
	RendererInteraction->Off();

	return CollisionReturn::ContinueCheck;
}
void OverWorldCuphead::BossClear()
{
	IsUIOn = false;
	SnowTextureBG0->Off();
	SnowTextureBG1->Off();
	SnowTexture->Off();
	SnowTextureCorp->Off();

	StateManager.ChangeState("Win");
}
void OverWorldCuphead::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("OWCHLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("OWCHRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("OWCHUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("OWCHDown", VK_DOWN);

		GameEngineInput::GetInst()->CreateKey("OWCHSelect", 'Z');
		GameEngineInput::GetInst()->CreateKey("OWCHOut", VK_ESCAPE);
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("OW_Idle_Side", FrameAnimation_DESC("OW_Idle_Side", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Idle_Side_Waiting", FrameAnimation_DESC("OW_Idle_Side_Waiting", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("OW_Idle_Up", FrameAnimation_DESC("OW_Idle_Up", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Idle_Down", FrameAnimation_DESC("OW_Idle_Down", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Idle_Down_Waiting", FrameAnimation_DESC("OW_Idle_Down_Waiting", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("OW_Idle_Diag_Up", FrameAnimation_DESC("OW_Idle_Diag_Up", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("OW_Idle_Diag_Down", FrameAnimation_DESC("OW_Idle_Diag_Down", 0.1f, true));
		
		Renderer->CreateFrameAnimationFolder("OW_Walk_Side", FrameAnimation_DESC("OW_Walk_Side", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Up", FrameAnimation_DESC("OW_Walk_Up", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Down", FrameAnimation_DESC("OW_Walk_Down", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Side_Up", FrameAnimation_DESC("OW_Walk_Diag_Up", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Side_Down", FrameAnimation_DESC("OW_Walk_Diag_Down", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Up_Up", FrameAnimation_DESC("OW_Walk_Diag_Up", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Up_Down", FrameAnimation_DESC("OW_Walk_Diag_Down", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Down_Up", FrameAnimation_DESC("OW_Walk_Diag_Up", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("OW_Walk_Down_Down", FrameAnimation_DESC("OW_Walk_Diag_Down", 0.06f, true));

		Renderer->CreateFrameAnimationFolder("OverWolrd_Win", FrameAnimation_DESC("OverWolrd_Win", 0.1f, false));
		
		Renderer->ChangeFrameAnimation("OW_Idle_Side");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		GetTransform().SetLocalPosition({ 1100, -720, -3 });
		//GetTransform().SetLocalPosition({ 520, -1430, -3 });

		Collision = CreateComponent<GameEngineCollision>();
		// Collision3D
		//Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 10000.0f });
		// Collision2D
		Collision->SetCollisionMode(CollisionMode::Ex);
		Collision->GetTransform().SetLocalScale({ 50.0f, 80.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
	}

	Renderer->AnimationBindEnd("OverWolrd_Win", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			CurDir = OWCupheadDir::Down;
			StateManager.ChangeState("Idle");
		});

	{
		RendererInteraction = CreateComponent<GameEngineTextureRenderer>();
		RendererInteraction->SetTexture("world_map_PC_glyph_box.png");
		RendererInteraction->ScaleToTexture();
		RendererInteraction->SetPivot(PIVOTMODE::CENTER);
		RendererInteraction->GetTransform().SetLocalPosition(float4(0.0f, 70.0f));
		RendererInteraction->Off();
	}

	{
		SnowTextureBG0 = CreateComponent<GameEngineTextureRenderer>();
		SnowTextureBG0->SetTexture("title_card_fader.png");
		SnowTextureBG0->ScaleToTexture();
		SnowTextureBG0->SetPivot(PIVOTMODE::CENTER);
		SnowTextureBG0->GetTransform().SetLocalPosition(float4{ 0.0f,0.0f,-15.0f });
		SnowTextureBG0->Off();

		SnowTextureBG1 = CreateComponent<GameEngineTextureRenderer>();
		SnowTextureBG1->SetTexture("title_card_background.png");
		SnowTextureBG1->ScaleToTexture();
		SnowTextureBG1->SetPivot(PIVOTMODE::CENTER);
		SnowTextureBG1->GetTransform().SetLocalPosition(float4{ 0.0f,0.0f,-15.0f });
		SnowTextureBG1->Off();

		SnowTexture = CreateComponent<GameEngineTextureRenderer>();
		SnowTexture->SetTexture("title_card_mortimer_freeze_ko.png");
		SnowTexture->ScaleToTexture();
		SnowTexture->SetPivot(PIVOTMODE::CENTER);
		SnowTexture->GetTransform().SetLocalPosition(float4{ 0.0f,80.0f,-15.0f });
		SnowTexture->Off();

		SnowTextureCorp = CreateComponent<GameEngineTextureRenderer>();
		SnowTextureCorp->SetTexture("credits_MDHR_logo.png");
		SnowTextureCorp->ScaleToTexture();
		SnowTextureCorp->SetPivot(PIVOTMODE::CENTER);
		SnowTextureCorp->GetTransform().SetLocalPosition(float4{ 0.0f,-150.0f,-15.0f });
		SnowTextureCorp->Off();
	}

	StateManager.CreateStateMember("Idle", std::bind(&OverWorldCuphead::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&OverWorldCuphead::IdleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Walk", std::bind(&OverWorldCuphead::WalkUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&OverWorldCuphead::WalkStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Win", std::bind(&OverWorldCuphead::WinUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&OverWorldCuphead::WinStart, this, std::placeholders::_1));

	StateManager.ChangeState("Idle");
}

void OverWorldCuphead::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	if (true == IsHourGlassOn)
	{
		IsHourGlassOn = false;

		HourGlass* Hourglass = GetLevel()->CreateActor<HourGlass>(OBJECTORDER::Title);
		Hourglass->GetRenderer()->AnimationBindEnd("Hourglass", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				GlobalContents::Actors::IsTimeOver = true;
				Hourglass->Death(1.0f);
			});

	}
	if (true == GlobalContents::Actors::IsTimeOver)
	{
		GlobalContents::Actors::TimeOverCheck += _DeltaTime;

		if (1.0f <= GlobalContents::Actors::TimeOverCheck)
		{
			GlobalContents::Actors::TimeOverCheck = 0.0f;
			GlobalContents::Actors::IsTimeOver = false;

			GEngine::ChangeLevel("MortimerFreeze");
		}
	}

	Collision->IsCollision(CollisionType::CT_OBB2D, static_cast<int>(OBJECTORDER::WorldSnow), CollisionType::CT_OBB2D,
		/*Update*/std::bind(&OverWorldCuphead::SnowUpdateCollisionCheck, this, std::placeholders::_1, std::placeholders::_2),
		/*Enter*/std::bind(&OverWorldCuphead::SnowEnterCollisionCheck, this, std::placeholders::_1, std::placeholders::_2),
		/*Exit*/std::bind(&OverWorldCuphead::SnowExitCollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

	if (true == IsUIOn)
	{
		return;
	}

	StateManager.Update(_DeltaTime);

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4::BACK * 100.0f);

	Renderer->ChangeFrameAnimation(CurStateName + CurUpDownName);
}

void OverWorldCuphead::IdleStart(const StateInfo& _Info)
{
	switch (CurDir)
	{
	case OWCupheadDir::Left:
		CurStateName = "OW_Idle_Side";
		break;
	case OWCupheadDir::Right:
		CurStateName = "OW_Idle_Side"; 
		break;
	case OWCupheadDir::Up:
		CurStateName = "OW_Idle_Up";
		break;
	case OWCupheadDir::Down:
		CurStateName = "OW_Idle_Down";
		break;
	default:
		break;
	}
}

void OverWorldCuphead::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("OWCHLeft")
		|| true == GameEngineInput::GetInst()->IsPress("OWCHRight")
		|| true == GameEngineInput::GetInst()->IsPress("OWCHUp")
		|| true == GameEngineInput::GetInst()->IsPress("OWCHDown"))
	{
		StateManager.ChangeState("Walk");
	}
}

void OverWorldCuphead::WalkStart(const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("OWCHLeft"))
	{
		CurStateName = "OW_Walk_Side";
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHRight"))
	{
		CurStateName = "OW_Walk_Side";
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHUp"))
	{
		CurStateName = "OW_Walk_Up";
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHDown"))
	{
		CurStateName = "OW_Walk_Down";
	}
}

void OverWorldCuphead::WalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SoundRepeatTime -= _DeltaTime;
	if (0 >= SoundRepeatTime)
	{
		SoundRepeatTime = 0.5f;
		GameEngineSound::SoundPlayOneShot("sfx_WorldMap_Footstep_007.wav");
	}
	
	if (true == GameEngineInput::GetInst()->IsUp("OWCHUp") || true == GameEngineInput::GetInst()->IsUp("OWCHDown"))
	{
		CurUpDownName = "";
	}
	
	if (false == GameEngineInput::GetInst()->IsPress("OWCHLeft")
		&& false == GameEngineInput::GetInst()->IsPress("OWCHRight")
		&& false == GameEngineInput::GetInst()->IsPress("OWCHUp")
		&& false == GameEngineInput::GetInst()->IsPress("OWCHDown"))
	{
		StateManager.ChangeState("Idle");
		return;
	}
	
	if (true == GameEngineInput::GetInst()->IsPress("OWCHLeft"))
	{
		Renderer->GetTransform().PixLocalNegativeX();
		CurStateName = "OW_Walk_Side";
		CurDir = OWCupheadDir::Left;
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHRight"))
	{
		Renderer->GetTransform().PixLocalPositiveX();
		CurStateName = "OW_Walk_Side";
		CurDir = OWCupheadDir::Right;
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHUp"))
	{
		CurStateName = "OW_Walk_Up";
		CurDir = OWCupheadDir::Up;
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHDown"))
	{
		CurStateName = "OW_Walk_Down";
		CurDir = OWCupheadDir::Down;
	}

	if (true == GameEngineInput::GetInst()->IsPress("OWCHUp") && true == GameEngineInput::GetInst()->IsPress("OWCHLeft"))
	{
		CurUpDownName = "_Up";
		CurDir = OWCupheadDir::LeftUp;
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHUp") && true == GameEngineInput::GetInst()->IsPress("OWCHRight"))
	{
		CurUpDownName = "_Up";
		CurDir = OWCupheadDir::RightUp;
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHDown") && true == GameEngineInput::GetInst()->IsPress("OWCHLeft"))
	{
		CurUpDownName = "_Down";
		CurDir = OWCupheadDir::LeftDown;
	}
	if (true == GameEngineInput::GetInst()->IsPress("OWCHDown") && true == GameEngineInput::GetInst()->IsPress("OWCHRight"))
	{
		CurUpDownName = "_Down";
		CurDir = OWCupheadDir::RightDown;
	}

	float4 NextPos = GetTransform().GetLocalPosition();
	switch (CurDir)
	{
	case OWCupheadDir::Left:
		NextPos += float4(-1, 0, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::LeftUp:
		NextPos += float4(-1, 1, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::LeftDown:
		NextPos += float4(-1, -1, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::Right:
		NextPos += float4(1, 0, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::RightUp:
		NextPos += float4(1, 1, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::RightDown:
		NextPos += float4(1, -1, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::Up:
		NextPos += float4(0, 1, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	case OWCupheadDir::Down:
		NextPos += float4(0, -1, 0).NormalizeReturn() * Speed * _DeltaTime;
		break;
	default:
		break;
	}

	ColorCheck = ColRenderer->GetCurTexture();
	if (nullptr == ColorCheck)
	{
		return;
	}
	if (false == ColorCheck->GetPixelToFloat4(NextPos.ix(), -NextPos.iy()).CompareInt4D(float4::BLACK))
	{
		GetTransform().SetLocalPosition(NextPos);
	}
	else
	{
		if (false == ColorCheck->GetPixelToFloat4(NextPos.ix(), -GetTransform().GetLocalPosition().iy()).CompareInt4D(float4::BLACK))
		{
			GetTransform().SetLocalPosition(float4(NextPos.x, GetTransform().GetLocalPosition().y));
		}
		else if (false == ColorCheck->GetPixelToFloat4(GetTransform().GetLocalPosition().ix(), -NextPos.iy()).CompareInt4D(float4::BLACK))
		{
			GetTransform().SetLocalPosition(float4(GetTransform().GetLocalPosition().x, NextPos.y));
		}
	}
}

void OverWorldCuphead::WinStart(const StateInfo& _Info)
{
	CurStateName = "OverWolrd_Win";

	GetTransform().SetWorldPosition(float4{ 3100.0f,-850.0f, -3.0f });
}

void OverWorldCuphead::WinUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
