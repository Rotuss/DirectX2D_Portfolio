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
	// [O]���� 14~17 �ݺ� - �̴Ͼ� 1~13c(SpawnBoyAppear)
	// [O]���� 18~21 - �̴Ͼ� 13c����(SpawnBoyAppearFix)
	// [ ]���� 22~ - �̴Ͼ� 14~ + ȿ��
	// [ ]���� 24~ - �̴Ͼ� 16~19 �ݺ�(ù 18���� �̵� ����, ���� ������ 20~ �� �� �浹ü ����)

	if (true == MortimerFreezeBoss::MFBoss->MinionPixRemoveReturn())
	{
		Renderer->CurAnimationPauseSwitch();
	}
}

