#include "PreCompile.h"
#include "MortimerFreezeMinion.h"
#include "MortimerFreezeBoss.h"

MortimerFreezeMinion::MortimerFreezeMinion() 
	: Renderer(nullptr)
	, EffectRenderer(nullptr)
	, Collision(nullptr)
	, GenderType(GENDER::BOY)
	, DirType(DIR::LEFT)
	, Speed(200.0f)
	, MinionMoveStart(false)
	, MinionFollowStart(false)
	, IsRanding(false)
	, MoveDir(0)
{
}

MortimerFreezeMinion::~MortimerFreezeMinion() 
{
}

CollisionReturn MortimerFreezeMinion::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == IsRanding)
	{
		_This->GetActor()->Death();
		_Other->GetActor()->Death();
	}
	return CollisionReturn::ContinueCheck;
}

CollisionReturn MortimerFreezeMinion::CollisionCheckWhale(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// 애니메이션 전환
	_This->Death();
	Speed = 400.0f;

	if (GENDER::BOY == GenderType)
	{
		Renderer->ChangeFrameAnimation("3DDeathBoy");
	}
	if (GENDER::GIRL == GenderType)
	{
		Renderer->ChangeFrameAnimation("3DDeathGirl");
	}

	return CollisionReturn::ContinueCheck;
}

void MortimerFreezeMinion::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		// Boy
		Renderer->CreateFrameAnimationFolder("SpawnBoyAppear", FrameAnimation_DESC("Minion_Spawn_Boy", 0, 16, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SpawnBoyRolling", FrameAnimation_DESC("Minion_Spawn_Boy", 17, 20, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("SpawnBoyGroundCol", FrameAnimation_DESC("Minion_Spawn_Boy", 21, 36, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SpawnRunBoy", FrameAnimation_DESC("Minion_Spawn_Run_Boy", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("3DDeathBoy", FrameAnimation_DESC("Minion_3D_Death_Boy", 0.08f, false));

		// Girl
		Renderer->CreateFrameAnimationFolder("SpawnGirlAppear", FrameAnimation_DESC("Minion_Spawn_Girl", 0, 16, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SpawnGirlRolling", FrameAnimation_DESC("Minion_Spawn_Girl", 17, 20, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("SpawnGirlGroundCol", FrameAnimation_DESC("Minion_Spawn_Girl", 21, 36, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SpawnRunGirl", FrameAnimation_DESC("Minion_Spawn_Run_Girl", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("3DDeathGirl", FrameAnimation_DESC("Minion_3D_Death_Girl", 0.08f, false));
	}

	{
		EffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		EffectRenderer->CreateFrameAnimationFolder("MinionSparkB", FrameAnimation_DESC("Minion_SparkB", 0.1f, false));
	}

	Renderer->AnimationBindFrame("SpawnBoyAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (14 == _Info.CurFrame)
			{
				Renderer->CurAnimationPauseSwitch();

				MortimerFreezeBoss::MFBoss->MinionPixStateSwitch(true);
			}
		});

	Renderer->AnimationBindEnd("SpawnBoyAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SpawnBoyRolling");
		});

	Renderer->AnimationBindFrame("SpawnBoyGroundCol", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (10 == _Info.CurFrame)
			{
				{
					Collision = CreateComponent<GameEngineCollision>();
					Collision->GetTransform().SetLocalScale({ 50,50,-1 });
					Collision->ChangeOrder(OBJECTORDER::BossMinion);

					// (미니언 < 플레이어 = 음수)미니언 - 플레이어 => 미니언이 오른쪽으로
					// (미니언 > 플레이어 = 양수)미니언 - 플레이어 => 미니언이 왼쪽으로
					float Value = GetTransform().GetLocalPosition().x - MsChalice::Chalice->GetTransform().GetLocalPosition().x;

					if (0 < Value)
					{
						if (DirType == DIR::RIGHT)
						{
							Renderer->GetTransform().PixLocalPositiveX();
							DirType = DIR::LEFT;
						}
						
					}
					if (0 > Value)
					{
						if (DirType == DIR::LEFT)
						{
							Renderer->GetTransform().PixLocalNegativeX();
							DirType = DIR::RIGHT;
						}
					}
				}
			}
		});

	Renderer->AnimationBindEnd("SpawnBoyGroundCol", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SpawnRunBoy");
			MinionFollowStart = true;
		});

	Renderer->AnimationBindEnd("3DDeathBoy", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	Renderer->AnimationBindFrame("SpawnGirlAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (14 == _Info.CurFrame)
			{
				Renderer->CurAnimationPauseSwitch();

				MortimerFreezeBoss::MFBoss->MinionPixStateSwitch(true);
			}
		});

	Renderer->AnimationBindEnd("SpawnGirlAppear", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SpawnGirlRolling");
		});

	Renderer->AnimationBindFrame("SpawnGirlGroundCol", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (10 == _Info.CurFrame)
			{
				{
					Collision = CreateComponent<GameEngineCollision>();
					Collision->GetTransform().SetLocalScale({ 50,50,-1 });
					Collision->ChangeOrder(OBJECTORDER::BossMinion);

					float Value = GetTransform().GetLocalPosition().x - MsChalice::Chalice->GetTransform().GetLocalPosition().x;

					if (0 < Value)
					{
						if (DirType == DIR::RIGHT)
						{
							Renderer->GetTransform().PixLocalPositiveX();
							DirType = DIR::LEFT;
						}

					}
					if (0 > Value)
					{
						if (DirType == DIR::LEFT)
						{
							Renderer->GetTransform().PixLocalNegativeX();
							DirType = DIR::RIGHT;
						}
					}
				}
			}
		});

	Renderer->AnimationBindEnd("SpawnGirlGroundCol", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("SpawnRunGirl");
			MinionFollowStart = true;
		});

	Renderer->AnimationBindEnd("3DDeathGirl", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Death();
		});

	EffectRenderer->AnimationBindEnd("MinionSparkB", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			EffectRenderer->Off();

			MinionMoveStart = true;
		});
}

void MortimerFreezeMinion::Update(float _DeltaTime)
{
	// [O]보스 14~17 반복 - 미니언 1~13b(SpawnBoyAppear)
	// [O]보스 18~21 - 미니언 13c고정
	// [O]보스 22~23 - 미니언 14~ + 효과
	// [O]보스 24~30 - 미니언 16~19 반복(첫 18부터 이동 시작, 땅에 닿을시 20~ 이 때 충돌체 생성)
	if (-10.0f > GetTransform().GetLocalPosition().x)
	{
		Renderer->GetActor()->Death();
		return;
	}
	if (1650.0f < GetTransform().GetLocalPosition().x)
	{
		Renderer->GetActor()->Death();
		return;
	}
	
	if (true == MortimerFreezeBoss::MFBoss->MinionPixRemoveReturn())
	{
		Renderer->CurAnimationPauseSwitch();

		EffectRenderer->ChangeFrameAnimation("MinionSparkB");
		EffectRenderer->SetScaleModeImage();
		EffectRenderer->ScaleToTexture();
		EffectRenderer->SetPivot(PIVOTMODE::CENTER);
	}

	if (true == MinionMoveStart)
	{
		if (0 == MoveDir)
		{
			// 왼쪽
			GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + (((GetTransform().GetLeftVector()) / 2.0f + GetTransform().GetDownVector()) * 400 * _DeltaTime));
		}
		else
		{
			// 오른쪽
			GetTransform().SetWorldPosition(GetTransform().GetWorldPosition() + (((GetTransform().GetRightVector()) / 2.0f + GetTransform().GetDownVector()) * 400 * _DeltaTime));
		}
	}
	
	ColorCheck = ColRenderer->GetCurTexture();
	if (nullptr == ColorCheck)
	{
		return;
	}
	if (true == ColorCheck->GetPixelToFloat4(static_cast<int>(GetTransform().GetLocalPosition().x), static_cast<int>(-(GetTransform().GetLocalPosition().y - 30.0f))).CompareInt4D(float4::BLACK) && true == MinionMoveStart)
	{
		MinionMoveStart = false;
		IsRanding = true;
		GetTransform().SetWorldMove(float4::ZERO);

		if (GENDER::BOY == GenderType)
		{
			MortimerFreezeBoss::MFBoss->MinionPixRemoveSetting(false);
			Renderer->ChangeFrameAnimation("SpawnBoyGroundCol");
		}

		if (GENDER::GIRL == GenderType)
		{
			MortimerFreezeBoss::MFBoss->MinionPixRemoveSetting(false);
			Renderer->ChangeFrameAnimation("SpawnGirlGroundCol");
		}	
	}

	if (nullptr == Collision)
	{
		return; 
	}

	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Weapon, CollisionType::CT_OBB2D, std::bind(&MortimerFreezeMinion::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::BossWhale, CollisionType::CT_OBB2D, std::bind(&MortimerFreezeMinion::CollisionCheckWhale, this, std::placeholders::_1, std::placeholders::_2));

	if (false == MinionFollowStart)
	{
		return;
	}

	if (DirType == DIR::LEFT)
	{
		GetTransform().SetWorldLeftMove(Speed, _DeltaTime);
	}
	if(DirType == DIR::RIGHT)
	{
		GetTransform().SetWorldRightMove(Speed, _DeltaTime);
	}
}

