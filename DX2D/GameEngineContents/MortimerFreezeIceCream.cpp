#include "PreCompile.h"
#include "MortimerFreezeIceCream.h"

MortimerFreezeIceCream::MortimerFreezeIceCream() 
	: Renderer(nullptr)
	, LerpPos()
	, StartPosition()
	, EndPosition()				// 중앙 위치 고정
	, IceCreamLerpRatio(0.0f)
{
}

MortimerFreezeIceCream::~MortimerFreezeIceCream() 
{
}

void MortimerFreezeIceCream::Start()
{
}

void MortimerFreezeIceCream::Update(float _DeltaTime)
{
	LerpPos = float4::Lerp(StartPosition, EndPosition, IceCreamLerpRatio);

	GetTransform().SetLocalRotation({ 0,0,float4::VectorXYtoDegree(StartPosition, EndPosition) - 90 });
	GetTransform().SetLocalPosition(LerpPos);
}

