#include "PreCompile.h"
#include "MortimerFreezeIceCream.h"

MortimerFreezeIceCream::MortimerFreezeIceCream() 
	: Renderer(nullptr)
	, EffectRenderer(nullptr)
	, LerpPos()
	, StartPosition()
	, CurNumType()
	, CurPosType()
	, EndPosition(float4{800.0f,-300.0f,-560.0f})				// 중앙 위치 고정
	, IceCreamLerpRatio(0.0f)
	, IceCreamMoveTime(10.0f)
{
}

MortimerFreezeIceCream::~MortimerFreezeIceCream() 
{
}

void MortimerFreezeIceCream::SetNumType(NumType _Type)
{
	// 수치 조정 필요
	if (PosType::Pos0 == CurPosType)
	{
		switch (_Type)
		{
		case NumType::Num0:
			StartPosition = float4{ 400.0f,-150.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num1:
			StartPosition = float4{ 1100.0f,-50.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num2:
			StartPosition = float4{ 1200.0f,-500.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num3:
			StartPosition = float4{ 500.0f,-550.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		default:
			break;
		}
	}
	if (PosType::Pos1 == CurPosType)
	{
		switch (_Type)
		{
		case NumType::Num0:
			StartPosition = float4{ 480.0f,-100.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num1:
			StartPosition = float4{ 1100.0f,-80.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num2:
			StartPosition = float4{ 1000.0f,-530.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num3:
			StartPosition = float4{ 400.0f,-500.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		default:
			break;
		}
	}
	if (PosType::Pos2 == CurPosType)
	{
		switch (_Type)
		{
		case NumType::Num0:
			StartPosition = float4{ 580.0f,-80.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num1:
			StartPosition = float4{ 1300.0f,-200.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num2:
			StartPosition = float4{ 950.0f,-630.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		case NumType::Num3:
			StartPosition = float4{ 380.0f,-400.0f,-560.0f };
			GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) + 90 });
			GetTransform().SetLocalPosition(StartPosition);
			break;
		default:
			break;
		}
	}
}

void MortimerFreezeIceCream::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("IceCream_Start", FrameAnimation_DESC("IceCream", 0, 2, 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IceCream", FrameAnimation_DESC("IceCream", 3, 23, 0.05f, true));

	Renderer->ChangeFrameAnimation("IceCream");
	Renderer->SetScaleModeImage();
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);
	Renderer->Off();

	EffectRenderer = CreateComponent<GameEngineTextureRenderer>();
	EffectRenderer->CreateFrameAnimationFolder("IceCream_Spawn_FX_Start", FrameAnimation_DESC("IceCream_Spawn_FX", 0, 5, 0.08f, false));
	EffectRenderer->CreateFrameAnimationFolder("IceCream_Spawn_FX", FrameAnimation_DESC("IceCream_Spawn_FX", 6, 15, 0.06f, true));

	EffectRenderer->ChangeFrameAnimation("IceCream_Spawn_FX_Start");
	EffectRenderer->SetScaleModeImage();
	EffectRenderer->ScaleToTexture();
	EffectRenderer->SetPivot(PIVOTMODE::CENTER);

	EffectRenderer->AnimationBindEnd("IceCream_Spawn_FX_Start", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EffectRenderer->ChangeFrameAnimation("IceCream_Spawn_FX");
		});

	EffectRenderer->AnimationBindTime("IceCream_Spawn_FX", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (0 > IceCreamMoveTime)
			{
				EffectRenderer->Off();
				
				Renderer->ChangeFrameAnimation("IceCream");
				Renderer->On();
			}
		});
}

void MortimerFreezeIceCream::Update(float _DeltaTime)
{
	IceCreamMoveTime -= _DeltaTime;
	
	if (150.0f >= GetTransform().GetLocalPosition().x ||
		1500.0f <= GetTransform().GetLocalPosition().x ||
		100.0f <= GetTransform().GetLocalPosition().y ||
		-800.0f >= GetTransform().GetLocalPosition().y)
	{
		Death();
	}

	if (0 > IceCreamMoveTime)
	{
		IceCreamLerpRatio += _DeltaTime;

		LerpPos = float4::Lerp(StartPosition, EndPosition, IceCreamLerpRatio);

		GetTransform().SetLocalPosition(LerpPos);
	}
}

