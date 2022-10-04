#include "PreCompile.h"
#include "MortimerFreezeTable.h"
#include "MortimerFreezeBoss.h"

MortimerFreezeTable::MortimerFreezeTable() 
	: Renderer(nullptr)
	, RendererEffect(nullptr)
	, IsShoot(false)
{
}

MortimerFreezeTable::~MortimerFreezeTable() 
{
}

void MortimerFreezeTable::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("PeashotTableAppear", FrameAnimation_DESC("Peashot_Table_Appear", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("PeashotTableIdle", FrameAnimation_DESC("Peashot_Table_Idle", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("PeashotTableOutro", FrameAnimation_DESC("Peashot_Table_Outro", 0.05f, true));
		Renderer->AnimationBindEnd("PeashotTableAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				Renderer->ChangeFrameAnimation("PeashotTableIdle");
			});
		Renderer->AnimationBindEnd("PeashotTableOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				Renderer->Off();
			});
		
		Renderer->ChangeFrameAnimation("PeashotTableAppear");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
	}

	{
		RendererEffect = CreateComponent<GameEngineTextureRenderer>();
		RendererEffect->CreateFrameAnimationFolder("Peashot_ShootFX", FrameAnimation_DESC("Peashot_ShootFX", 0.06f, false));
		
		RendererEffect->ChangeFrameAnimation("Peashot_ShootFX");
		RendererEffect->SetScaleModeImage();
		RendererEffect->ScaleToTexture();
		RendererEffect->SetPivot(PIVOTMODE::CENTER);
		RendererEffect->Off();

		RendererEffect->AnimationBindEnd("Peashot_ShootFX", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				RendererEffect->Off();
				IsShoot = false;
			});
	}
}

void MortimerFreezeTable::Update(float _DeltaTime)
{
	GetTransform().SetLocalPosition(MortimerFreezeBoss::MFBoss->GetTransform().GetWorldPosition() + float4(0, -50, -1));

	if (true == MortimerFreezeBoss::MFBoss->GetIsCurPeashotStartAttack())
	{
		if (false == IsShoot)
		{
			IsShoot = true;
			RendererEffect->ChangeFrameAnimation("Peashot_ShootFX", true);
			RendererEffect->On();
		}
	}

	if (true == MortimerFreezeBoss::MFBoss->GetIsCurPeashotEnd())
	{
		Renderer->ChangeFrameAnimation("PeashotTableOutro");
	}
}

