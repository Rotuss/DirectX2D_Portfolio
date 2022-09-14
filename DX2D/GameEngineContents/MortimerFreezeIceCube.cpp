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
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		Renderer->GetTransform().SetLocalScale({ 200, 200, 1 });
	}
	if (CubeSize == SizeType::Large && DirType == CubeDIR::RIGHT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		//Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().SetLocalScale({ 200, 200, 1 });
	}
	
	if (CubeSize == SizeType::Medium && DirType == CubeDIR::LEFT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		Renderer->GetTransform().SetLocalScale({ 100, 100, 1 });
	}
	if (CubeSize == SizeType::Medium && DirType == CubeDIR::RIGHT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		//Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().SetLocalScale({ 100, 100, 1 });
	}

	if (CubeSize == SizeType::Small && DirType == CubeDIR::LEFT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		Renderer->GetTransform().SetLocalScale({ 50, 50, 1 });
	}
	if (CubeSize == SizeType::Small && DirType == CubeDIR::RIGHT)
	{
		//Renderer->ChangeFrameAnimation("SpawnBoyAppear");
		//Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().SetLocalScale({ 50, 50, 1 });
	}

	//Renderer->SetScaleModeImage();
	//Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void MortimerFreezeIceCube::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
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

	float LerpY = GameEngineMath::Lerp(500, -500, CubeLerpRatio) * _DeltaTime;

	YAdd += LerpY;
	if (0 >= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

