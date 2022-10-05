#include "PreCompile.h"
#include "OverWorldCuphead.h"

OverWorldCuphead* OverWorldCuphead::OWCuphead = nullptr;

OverWorldCuphead::OverWorldCuphead() 
	: Renderer(nullptr)
	, ColRenderer(nullptr)
	, ColorCheck(nullptr)
	, Collision(nullptr)
	, StateManager()
	, CurStateName("")
	, CurUpDownName("")
	, CurDir(OWCupheadDir::Down)
	, Speed(300.0f)
{
	OWCuphead = this;
}

OverWorldCuphead::~OverWorldCuphead() 
{
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
		GetTransform().SetLocalPosition({ 300, -1430, -3 });
		
		Collision = CreateComponent<GameEngineCollision>();
		// Collision3D
		//Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 10000.0f });
		// Collision2D
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(OBJECTORDER::Player);
	}

	StateManager.CreateStateMember("Idle", std::bind(&OverWorldCuphead::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&OverWorldCuphead::IdleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Walk", std::bind(&OverWorldCuphead::WalkUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&OverWorldCuphead::WalkStart, this, std::placeholders::_1));
	
	StateManager.ChangeState("Idle");
}

void OverWorldCuphead::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
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
