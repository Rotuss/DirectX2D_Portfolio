#include "PreCompile.h"
#include "MortimerFreezeSnowPlatform.h"

MortimerFreezeSnowPlatform::MortimerFreezeSnowPlatform() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, CurPlatformType()
	, FollowObj(nullptr)
	, PrevPosition(float4::ZERO)
	, CurPosition(float4::ZERO)
{
}

MortimerFreezeSnowPlatform::~MortimerFreezeSnowPlatform() 
{
}

void MortimerFreezeSnowPlatform::SetPlatformType(PlatformType _Type)
{
	CurPlatformType = _Type;

	switch (_Type)
	{
	case PlatformType::Intro:
		//Renderer->ChangeFrameAnimation("");
		break;
	case PlatformType::TypeA:
		break;
	case PlatformType::TypeB:
		break;
	case PlatformType::TypeC:
		break;
	case PlatformType::TypeD:
		break;
	case PlatformType::TypeE:
		break;
	default:
		break;
	}
}

float4 MortimerFreezeSnowPlatform::GetMovePos()
{
	return CurPosition - PrevPosition;
}

void MortimerFreezeSnowPlatform::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 220.0f,85.0f,0.0f });
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 200.0f, 40.0f, 0.0f });
	Collision->ChangeOrder(OBJECTORDER::SnowPlatform);
}

void MortimerFreezeSnowPlatform::Update(float _DeltaTime)
{
	if (nullptr == FollowObj)
	{
		return;
	}

	PrevPosition = GetTransform().GetWorldPosition();
	GetTransform().SetWorldPosition(FollowObj->GetWorldPosition());
	CurPosition = GetTransform().GetWorldPosition();
}

