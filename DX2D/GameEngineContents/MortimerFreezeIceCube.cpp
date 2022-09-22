#include "PreCompile.h"
#include "MortimerFreezeIceCube.h"
#include "MsChalice.h"
#include "MortimerFreezeBoss.h"
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeIceCube::MortimerFreezeIceCube()
	: CubeSize()
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
	}
	if (CubeSize == SizeType::Large && DirType == CubeDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Large");
		Renderer->GetTransform().PixLocalNegativeX();
	}
	
	if (CubeSize == SizeType::Medium && DirType == CubeDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Medium");
	}
	if (CubeSize == SizeType::Medium && DirType == CubeDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Medium");
		Renderer->GetTransform().PixLocalNegativeX();
	}

	if (CubeSize == SizeType::Small && DirType == CubeDIR::LEFT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Small");
	}
	if (CubeSize == SizeType::Small && DirType == CubeDIR::RIGHT)
	{
		Renderer->ChangeFrameAnimation("IceCube_Small");
		Renderer->GetTransform().PixLocalNegativeX();
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
		Renderer->CreateFrameAnimationFolder("IceCube_Large", FrameAnimation_DESC("IceCube_Large", 0.1f, true));

		// Medium
		Renderer->CreateFrameAnimationFolder("IceCube_Medium", FrameAnimation_DESC("IceCube_Medium", 0.1f, true));

		// Small
		Renderer->CreateFrameAnimationFolder("IceCube_Small", FrameAnimation_DESC("IceCube_Small", 0.1f, true));
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

	CubeLerpRatio += _DeltaTime;


	LerpPos = float4::Lerp(StartPosition, EndPosition, CubeLerpRatio);

	float LerpY = GameEngineMath::Lerp(1800, -1800, CubeLerpRatio) * _DeltaTime;
	if (SizeType::Small == CubeSize)
	{
		LerpY = GameEngineMath::Lerp(1200, -1200, CubeLerpRatio) * _DeltaTime;
	}


	YAdd += LerpY;
	if (0 >= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

