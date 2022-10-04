#include "PreCompile.h"
#include "MortimerFreezeIceCube.h"
#include "MsChalice.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeIceCube::MortimerFreezeIceCube()
	: Collision(nullptr)
	, CubeSize()
	, StartPosition(float4::ZERO)
	, EndPosition(float4::ZERO)
	, LerpPos(float4::ZERO)
	, CubeLerpRatio(0.0f)
	, YAdd(0.0f)
{
}

MortimerFreezeIceCube::~MortimerFreezeIceCube() 
{
}

void MortimerFreezeIceCube::SetSizeType(SizeType _Type)
{
	CubeSize = _Type;

	if (CubeSize == SizeType::Large && DirType == CubeDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Large");
		Collision->GetTransform().SetLocalScale({ 100,100,-1 });
	}
	if (CubeSize == SizeType::Large && DirType == CubeDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Large");
		Renderer->GetTransform().PixLocalNegativeX();
		Collision->GetTransform().SetLocalScale({ 100,100,-1 });
	}
	
	if (CubeSize == SizeType::Medium && DirType == CubeDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Medium");
		Collision->GetTransform().SetLocalScale({ 70,70,-1 });
	}
	if (CubeSize == SizeType::Medium && DirType == CubeDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Medium");
		Renderer->GetTransform().PixLocalNegativeX();
		Collision->GetTransform().SetLocalScale({ 70,70,-1 });
	}

	if (CubeSize == SizeType::Small && DirType == CubeDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Small");
		Collision->GetTransform().SetLocalScale({ 40,40,-1 });
	}
	if (CubeSize == SizeType::Small && DirType == CubeDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Small");
		Renderer->GetTransform().PixLocalNegativeX();
		Collision->GetTransform().SetLocalScale({ 40,40,-1 });
	}

	Renderer->SetScaleModeImage();
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void MortimerFreezeIceCube::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		// Large
		Renderer->CreateFrameAnimationFolder("IceCube_Large", FrameAnimation_DESC("IceCube_Large", 0.05f, true));

		// Medium
		Renderer->CreateFrameAnimationFolder("IceCube_Medium", FrameAnimation_DESC("IceCube_Medium", 0.05f, true));

		// Small
		Renderer->CreateFrameAnimationFolder("IceCube_Small", FrameAnimation_DESC("IceCube_Small", 0.05f, true));
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->ChangeOrder(OBJECTORDER::Boss);
	}
}

void MortimerFreezeIceCube::Update(float _DeltaTime)
{
	ColorCheck = ColRenderer->GetCurTexture();
	if (true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-GetTransform().GetLocalPosition().y)).CompareInt4D(float4::BLACK))
	{
		if (SizeType::Small != CubeSize)
		{
			{
				MortimerFreezeIceCube* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCube>(OBJECTORDER::Boss);
				Ptr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 0.0f, 10.0f, 0.0f }, GetTransform().GetLocalPosition() - float4{ 200.0f,0.0f });
				if (SizeType::Large == CubeSize)
				{
					Ptr->SetSizeType(SizeType::Medium);
				}
				if (SizeType::Medium == CubeSize)
				{
					Ptr->SetSizeType(SizeType::Small);
				}
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{0.0f, 10.0f, 0.0f});
				Ptr->SetColMap(MsChalice::Chalice->GetColMap());
			}

			{
				MortimerFreezeIceCube* Ptr = GetLevel()->CreateActor<MortimerFreezeIceCube>(OBJECTORDER::Boss);
				Ptr->SetMovePos(GetTransform().GetLocalPosition() + float4{ 0.0f, 10.0f, 0.0f }, GetTransform().GetLocalPosition() + float4{ 200.0f,0.0f });
				if (SizeType::Large == CubeSize)
				{
					Ptr->SetSizeType(SizeType::Medium);
				}
				if (SizeType::Medium == CubeSize)
				{
					Ptr->SetSizeType(SizeType::Small);
				}
				Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4{ 0.0f, 10.0f, 0.0f });
				Ptr->SetColMap(MsChalice::Chalice->GetColMap());
			}
		}
		Renderer->GetActor()->Death();
	}

	CubeLerpRatio += _DeltaTime * 0.6f;


	LerpPos = float4::Lerp(StartPosition, EndPosition, CubeLerpRatio);

	float LerpY = GameEngineMath::Lerp(1100, -1100, CubeLerpRatio) * _DeltaTime;
	if (SizeType::Small == CubeSize)
	{
		LerpY = GameEngineMath::Lerp(1100, -1100, CubeLerpRatio * 1.5f) * _DeltaTime;
	}


	YAdd += LerpY;
	/*if (0 >= YAdd)
	{
		YAdd = 0.0f;
	}*/

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

