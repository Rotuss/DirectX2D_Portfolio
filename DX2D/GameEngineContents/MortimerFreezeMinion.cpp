#include "PreCompile.h"
#include "MortimerFreezeMinion.h"
#include "MortimerFreezeBoss.h"

MortimerFreezeMinion::MortimerFreezeMinion() 
	: Renderer(nullptr)
	, Collision(nullptr)
	, GenderType(GENDER::BOY)
	, DirType(DIR::LEFT)
{
}

MortimerFreezeMinion::~MortimerFreezeMinion() 
{
}

void MortimerFreezeMinion::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		// Boy
		Renderer->CreateFrameAnimationFolder("SpawnBoyAppear", FrameAnimation_DESC("Minion_Spawn_Boy", 0, 16, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SpawnRunBoy", FrameAnimation_DESC("Minion_Spawn_Run_Boy", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("3DDeathBoy", FrameAnimation_DESC("Minion_3D_Death_Boy", 0.1f, true));

		// Girl
		Renderer->CreateFrameAnimationFolder("SpawnGirlAppear", FrameAnimation_DESC("Minion_Spawn_Girl", 0, 16, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SpawnRunGirl", FrameAnimation_DESC("Minion_Spawn_Run_Girl", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("3DDeathGirl", FrameAnimation_DESC("Minion_3D_Death_Girl", 0.1f, true));
	}

	Renderer->AnimationBindFrame("SpawnBoyAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (14 == _Info.CurFrame)
			{
				Renderer->CurAnimationPauseSwitch();

				MortimerFreezeBoss::MFBoss->MinionPixStateSwitch(true);
			}
		});

	Renderer->AnimationBindFrame("SpawnGirlAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (14 == _Info.CurFrame)
			{
				Renderer->CurAnimationPauseSwitch();
			}
		});

	/*{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 25,110,-1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
	}*/
}

void MortimerFreezeMinion::Update(float _DeltaTime)
{
	// [O]보스 14~17 반복 - 미니언 1~13c(SpawnBoyAppear)
	// [O]보스 18~21 - 미니언 13c고정(SpawnBoyAppearFix)
	// [ ]보스 22~ - 미니언 14~ + 효과
	// [ ]보스 24~ - 미니언 16~19 반복(첫 18부터 이동 시작, 땅에 닿을시 20~ 이 때 충돌체 생성)

	if (true == MortimerFreezeBoss::MFBoss->MinionPixRemoveReturn())
	{
		Renderer->CurAnimationPauseSwitch();
	}
}

