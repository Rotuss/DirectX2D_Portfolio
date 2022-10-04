#include "PreCompile.h"
#include "MortimerFreezeBoss.h"
#include "GlobalContents.h"
#include "ReadyWALLOP.h"
#include "MortimerFreezeTable.h"
#include "MortimerFreezeCard.h"
#include "MortimerFreezeMinion.h"
#include "MortimerFreezeWhale.h"

#include <iostream>
#include <GameEngineBase/GameEngineRandom.h>

MortimerFreezeBoss* MortimerFreezeBoss::MFBoss= nullptr;

MortimerFreezeBoss::MortimerFreezeBoss()
	: Renderer(nullptr)
	, AddRenderer(nullptr)
	, AddRenderer01(nullptr)
	, SubRenderer00(nullptr)
	, SubRenderer01(nullptr)
	, SubRenderer02(nullptr)
	, SubRenderer03(nullptr)
	, EffectRenderer00(nullptr)
	, EffectRenderer01(nullptr)
	, EffectRenderer02(nullptr)
	, Collision(nullptr)
	, WhaleCollision(nullptr)
	, Phase3BotCollision(nullptr)
	, CurMFDir(MFBossDIR::LEFT)
	, CurMeltingDir()
	, StartPos()
	, EndPos()
	, LerpPos()
	, Speed(200.0f)
	, YAdd(0.0f)
	, IdleLerpRatio(0.0f)
	, PeashotAttackMoveTime(0.0f)
	, HP(1)
	, Phase2TransitionMotionCount(2)
	, PeashotStateCount(GameEngineRandom::MainRandom.RandomInt(3, 5))
	, PeashotAttackCount(GameEngineRandom::MainRandom.RandomInt(1, 2))
	, QuadshotStateCount(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, WhaleStateCount(GameEngineRandom::MainRandom.RandomInt(3, 4))
	, SnowBeastIntroCount(1)
	, IsP1IdleStart(true)
	, MFMoveReplay(false)
	, IsCurRStartPos(true)
	, IsCurPeashotLStartPos(true)
	, IsCurPeashotStartAttack(false)
	, IsCurPeashotEnd(false)
	, IsIdleTransState(false)
	, MinionPixCheck(false)
	, MinionPixRemove(false)
	, IsEndPhase1(false)
	, IsSnowBeastIntroStartEnd(false)
	, IsSnowBeastIntroMoveDown(false)
	, IsSnowBeastIntroLand(false)
	, DashTime(GameEngineRandom::MainRandom.RandomFloat(0.2f, 1.0f))
	, FridgeTime(GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f))
	, SmashTime(GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f))
	, IceTime(0.0f)
	, BladeTime(1.0f)
	, PlatformTime(0.0f)
	, PrevSkill(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, DashMove(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, IceCubeCount(GameEngineRandom::MainRandom.RandomInt(1, 3))
	, IceBatCount(4)
	, BladeCount(-1)
	, SmashRepeatCount(3)
	, Phase3TransitionMotionCount(2)
	, PlatformCount(5)
	, LegCount(2)
	, IsDashPatternBegin(true)
	, IsPreparing(false)
	, IsPrevDash(false)
	, IsPrevJump(false)
	, IsJump(static_cast<bool>(GameEngineRandom::MainRandom.RandomInt(0, 1)))
	, IsShoot(false)
	, IsBatOpen(false)
	, IsPlatformOn(false)
	, IsLegMove(false)
	, EyeTime(GameEngineRandom::MainRandom.RandomFloat(0.2f, 1.0f))
	, IceCreamTime(GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f))
	, SplitTime(GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f))
	, IceCreamAppearTime(0.0f)
	, BucketAppearTime(0.0f)
	, SwapCount(GameEngineRandom::MainRandom.RandomInt(1, 2))
	, EyeRepeatCount(4)
	, IceCreamRandom(GameEngineRandom::MainRandom.RandomInt(0, 2))
	, IceCreamCount(4)
	, BucketCount(3)
	, IsPh3DownMove(false)
	, IsPh3XMove(false)
	, IsReverse(false)
	, IsSwapA(false)
	, IsIceCreamPatternEnd(false)
	, IsBucketMove(false)
	, PrevState("")
{
	MFBoss = this;
}

MortimerFreezeBoss::~MortimerFreezeBoss() 
{
}

CollisionReturn MortimerFreezeBoss::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	_Other->GetActor()->Death();
	
	HP -= 1;
	
	if (0 >= HP)
	{
		HP = 0;
	}

	return CollisionReturn::ContinueCheck;
}

void MortimerFreezeBoss::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Change_Phase3"))
	{
		GameEngineInput::GetInst()->CreateKey("Change_Phase3", 'Q');
		GameEngineInput::GetInst()->CreateKey("Appear_SnowPlatform", 'A');
	}

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("MFIntro_Top", FrameAnimation_DESC("MFIntro_Top", 0, 43, 0.05f, false));
		Renderer->CreateFrameAnimationFolder("MFIntro_TopLast", FrameAnimation_DESC("MFIntro_Top", 44, 64, 0.04f, false));
		Renderer->CreateFrameAnimationFolder("MFIdle", FrameAnimation_DESC("MFIdle", 0, 23, 0.06f, true));
		Renderer->CreateFrameAnimationFolder("MFIdleTrans", FrameAnimation_DESC("MFIdle", 24, 32, 0.06f, false));
		
		Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("Peashot_Intro", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("PeashotIdle", FrameAnimation_DESC("Peashot_Idle", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("PeashotShoot", FrameAnimation_DESC("Peashot_Shoot", 0.05f, false));	
		Renderer->CreateFrameAnimationFolder("PeashotOutro", FrameAnimation_DESC("Peashot_Outro", 0.05f, true));

		Renderer->CreateFrameAnimationFolder("QuadshotStart", FrameAnimation_DESC("MF_Attack_Quadshot", 0, 15, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("QuadshotMinionAppear", FrameAnimation_DESC("MF_Attack_Quadshot", 15, 18, 0.05f, true));
		Renderer->CreateFrameAnimationFolder("QuadshotMinionAfter", FrameAnimation_DESC("MF_Attack_Quadshot", 19, 30, 0.06f, false));
		
		Renderer->CreateFrameAnimationFolder("WhaleDrop", FrameAnimation_DESC("Wizard_Whale_Drop", 0.06f, false));
		Renderer->CreateFrameAnimationFolder("WhaleDropAttackOutro", FrameAnimation_DESC("Wizard_Drop_Attack_Outro", 0.06f, false));
		
		Renderer->CreateFrameAnimationFolder("MFPhase2Transition0", FrameAnimation_DESC("MFPhase2_Transition", 0, 10, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("MFPhase2Transition1", FrameAnimation_DESC("MFPhase2_Transition", 11, 15, 0.06f, true));
		Renderer->CreateFrameAnimationFolder("MFPhase2Transition2", FrameAnimation_DESC("MFPhase2_Transition", 16, 27, 0.06f, false));
		
		// Phase2
		Renderer->CreateFrameAnimationFolder("MF2Idle", FrameAnimation_DESC("MF2Idle", 0.06f, true));

		// Dash패턴 첫 공격 전 모션
		Renderer->CreateFrameAnimationFolder("SnowBeast_DashPreAttack", FrameAnimation_DESC("SnowBeast_PreAttack", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowBeast_DashSnowBeastBall", FrameAnimation_DESC("SnowBeastBall", 0.06f, true));
		// Dash 모션
		Renderer->CreateFrameAnimationFolder("SnowBeast_Dash_Attack", FrameAnimation_DESC("SnowBeast_Dash_Attack", 0.08f, false));
		// Dash -> Dash
		Renderer->CreateFrameAnimationFolder("SnowBeast_DashtoAny_Trans", FrameAnimation_DESC("SnowBeast_DashtoAny_Trans", 0.08f, false));
		// Jump -> Dash
		Renderer->CreateFrameAnimationFolder("SnowBeast_JumptoDash_Trans", FrameAnimation_DESC("SnowBeast_JumptoDash_Trans", 0.08f, false));
		// Dash -> Idle
		Renderer->CreateFrameAnimationFolder("SnowBeast_DashtoIdle_Trans", FrameAnimation_DESC("SnowBeast_DashtoIdle_Trans", 0.1f, false));
		// Jump 모션
		Renderer->CreateFrameAnimationFolder("SnowBeast_Jump_Attack", FrameAnimation_DESC("SnowBeast_Jump_Attack", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowBeast_Jump_Attack_NotFirst", FrameAnimation_DESC("SnowBeast_Jump_Attack", 1, 14, 0.08f, false));
		// Jump -> Jump
		Renderer->CreateFrameAnimationFolder("SnowBeast_JumptoJump_Trans", FrameAnimation_DESC("SnowBeast_JumptoJump_Trans", 0.08f, false));
		// Dash -> Jump
		Renderer->CreateFrameAnimationFolder("SnowBeast_DashtoJump_Trans", FrameAnimation_DESC("SnowBeast_DashtoJump_Trans", 0.08f, false));
		// Jump -> Idle
		Renderer->CreateFrameAnimationFolder("SnowBeast_JumptoIdle_Trans", FrameAnimation_DESC("SnowBeast_JumptoIdle_Trans", 0.1f, false));
		// Dash 패턴 이후 Idle(Dash -> Idle 또는 Jump -> Idle 끝나고 실행)
		Renderer->CreateFrameAnimationFolder("SnowBeast_AttacktoIdle_Trans", FrameAnimation_DESC("SnowBeast_AttacktoIdle_Trans", 0.1f, false));

		Renderer->CreateFrameAnimationFolder("SnowBeastFridge_Morph", FrameAnimation_DESC("SnowBeast_Fridge_Morph", 0.05f, false));
		Renderer->CreateFrameAnimationFolder("SnowBeastFridge_Idle", FrameAnimation_DESC("SnowBeast_Fridge_Idle", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("SnowBeastFridge_Shoot", FrameAnimation_DESC("SnowBeast_Fridge_Shoot", 0.12f, true));
		Renderer->CreateFrameAnimationFolder("SnowBeastFridge_Freezer", FrameAnimation_DESC("SnowBeast_Fridge_Freezer", 0, 3, 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowBeastFridge_Freezer_Repeat", FrameAnimation_DESC("SnowBeast_Fridge_Freezer", 4, 7, 0.06f, true));
		Renderer->CreateFrameAnimationFolder("SnowBeastFridge_Freezer_Outro", FrameAnimation_DESC("SnowBeast_Fridge_Freezer_Outro", 0.08f, false));

		Renderer->CreateFrameAnimationFolder("SnowBeastSmash", FrameAnimation_DESC("SnowBeast_Smash", 0, 19, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("SnowBeastSmashRepeat", FrameAnimation_DESC("SnowBeast_Smash", 20, 22, 0.08f, true));
		Renderer->CreateFrameAnimationFolder("SnowBeastSmashOutro", FrameAnimation_DESC("SnowBeast_Smash_Outro", 0.06f, false));

		// 애니메이션 조정 필요
		Renderer->CreateFrameAnimationFolder("MFPhase3Transition0", FrameAnimation_DESC("SnowBeast_Death", 0, 14, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("MFPhase3Transition1", FrameAnimation_DESC("SnowBeast_Death", 15, 19, 0.06f, true));
		Renderer->CreateFrameAnimationFolder("MFPhase3Transition2", FrameAnimation_DESC("SnowBeast_Death", 20, 26, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("MFPhase3Transition3", FrameAnimation_DESC("SnowBeast_Death", 27, 33, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("MFPhase3Transition_Legs", FrameAnimation_DESC("SnowBeast_Death_Legs", 0, 4, 0.08f, true));
		Renderer->CreateFrameAnimationFolder("MFPhase3Transition_LegsMove", FrameAnimation_DESC("SnowBeast_Death_Legs", 5, 15, 0.05f, true));

		// Phase3
		Renderer->CreateFrameAnimationFolder("MF3Intro", FrameAnimation_DESC("MF3Intro", 0.07f, false));
		Renderer->CreateFrameAnimationFolder("MF3IntroMove", FrameAnimation_DESC("SnowFlake_SwapA", {3,2,1}, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("MF3Idle", FrameAnimation_DESC("SnowFlake_IdleBacker", 0.06f, true));
		Renderer->CreateFrameAnimationFolder("Attack_After_MF3Idle", FrameAnimation_DESC("SnowFlake_IdleBacker", 8, 15, 0.06f, false));
		
		Renderer->CreateFrameAnimationFolder("SnowFlake_SwapA", FrameAnimation_DESC("SnowFlake_SwapA", 1, 8, 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_SwapAR", FrameAnimation_DESC("SnowFlake_SwapA", { 8,7,6,5,4,3,2,1 }, 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_SwapB", FrameAnimation_DESC("SnowFlake_SwapB_Backer", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_SwapC", FrameAnimation_DESC("SnowFlake_SwapC_Backer", 0.08f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_SwapCLast", FrameAnimation_DESC("SnowFlake_SwapC_Backer", { 2,1,0 }, 0.1f, false));

		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker0", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 0, 19, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker1", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 20, 22, 0.06f, true));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker2", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 23, 24, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker3", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 25, 33, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker4", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 34, 49, 0.05f, true));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker5", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 50, 58, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker6", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 59, 61, 0.06f, true));
		Renderer->CreateFrameAnimationFolder("EyeBall_BodyBacker7", FrameAnimation_DESC("Attack_EyeBall_BodyBacker", 62, 69, 0.06f, false));

		Renderer->CreateFrameAnimationFolder("SnowFlake_IceCreamBacker0", FrameAnimation_DESC("SnowFlake_IceCreamBacker", 0, 5, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_IceCreamBacker1", FrameAnimation_DESC("SnowFlake_IceCreamBacker", 6, 12, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_IceCreamBackerR0", FrameAnimation_DESC("SnowFlake_IceCreamBacker", { 5,4,3,2,1,0 }, 0.06f, false));
		Renderer->CreateFrameAnimationFolder("SnowFlake_IceCreamBackerR1", FrameAnimation_DESC("SnowFlake_IceCreamBacker", { 12,11,10,9,8,7,6 }, 0.06f, false));

		Renderer->CreateFrameAnimationFolder("SplitShot_SnowFlakeBacker0", FrameAnimation_DESC("SplitShot_SnowFlakeBacker", 0, 12, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SplitShot_SnowFlakeBacker1", FrameAnimation_DESC("SplitShot_SnowFlakeBacker", 13, 15, 0.1f, true));
		Renderer->CreateFrameAnimationFolder("SplitShot_SnowFlakeBacker2", FrameAnimation_DESC("SplitShot_SnowFlakeBacker", 16, 25, 0.08f, true));
		/*Renderer->CreateFrameAnimationFolder("SplitShot_SnowFlakeBacker2", FrameAnimation_DESC("SplitShot_SnowFlakeBacker", 16, 18, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("SplitShot_SnowFlakeBacker3", FrameAnimation_DESC("SplitShot_SnowFlakeBacker", 19, 25, 0.1f, false));*/
		Renderer->CreateFrameAnimationFolder("SplitShot_SnowFlakeBacker4", FrameAnimation_DESC("SplitShot_SnowFlakeBacker", 26, 37, 0.1f, false));

		Renderer->CreateFrameAnimationFolder("Ph3Wizard_Death", FrameAnimation_DESC("Ph3Wizard_Death", 0.1f, true));

		Renderer->ChangeFrameAnimation("MFIntro_Top");
		Renderer->SetScaleModeImage();
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::CENTER);
		//Renderer->GetTransform().SetLocalPosition({ 1180.0f, -390.0f, -1.0f });
		GetTransform().SetLocalPosition({ 805, -530, -1 });
		//GetTransform().SetLocalPosition({ 1350, -380, -1 });
		//GetTransform().SetLocalPosition({ 950, -360, -1 });
	}

	{
		// AddRenderer 을 Renderer의 자식으로?-?
		AddRenderer = CreateComponent<GameEngineTextureRenderer>();
		AddRenderer->CreateFrameAnimationFolder("MFPhase2Transition1_Arm", FrameAnimation_DESC("MFPhase2_Transition", 28, 35, 0.06f, true));
		AddRenderer->CreateFrameAnimationFolder("SnowBeastFridgeFreezer_Top", FrameAnimation_DESC("SnowBeast_Fridge_Freezer_Top", 0.1f, false));
		AddRenderer->CreateFrameAnimationFolder("SnowBeast_Limbs_ReformingA", FrameAnimation_DESC("SnowBeast_Limbs_ReformingA", 0.1f, false));

		AddRenderer->ChangeFrameAnimation("MFPhase2Transition1_Arm");
		AddRenderer->SetScaleModeImage();
		AddRenderer->ScaleToTexture();
		AddRenderer->SetPivot(PIVOTMODE::TOP);
		AddRenderer->Off();
	}

	{
		AddRenderer01 = CreateComponent<GameEngineTextureRenderer>();
		AddRenderer01->CreateFrameAnimationFolder("SnowBeast_Limbs_ReformingB", FrameAnimation_DESC("SnowBeast_Limbs_ReformingB", 0.1f, false));

		AddRenderer01->ChangeFrameAnimation("SnowBeast_Limbs_ReformingB");
		AddRenderer01->SetScaleModeImage();
		AddRenderer01->ScaleToTexture();
		AddRenderer01->SetPivot(PIVOTMODE::BOT);
		AddRenderer01->Off();
	}

	std::vector<unsigned int> Rev;
	for (int i = 0; i < 18; i++)
	{
		Rev.push_back(17 - i);
	}

	{
		SubRenderer00 = CreateComponent<GameEngineTextureRenderer>();
		SubRenderer00->CreateFrameAnimationFolder("MFIntro", FrameAnimation_DESC("MFIntro", 0.05f, false));
		
		SubRenderer00->CreateFrameAnimationFolder("SnowBeastIntro_Start", FrameAnimation_DESC("SnowBeast_Intro", 0, 2, 0.08f, true));
		//SubRenderer00->CreateFrameAnimationFolder("SnowBeastIntro", FrameAnimation_DESC("SnowBeast_Intro", 3, 56, 0.1f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowBeastIntro", FrameAnimation_DESC("SnowBeast_Intro", 3, 44, 0.08f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowBeastIntro_Fall", FrameAnimation_DESC("SnowBeast_Intro", 45, 48, 0.09f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowBeastIntro_Land", FrameAnimation_DESC("SnowBeast_Intro", 49, 56, 0.08f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowBeast_Limbs_MeltingA", FrameAnimation_DESC("SnowBeast_Limbs_MeltingA", 0.06f, false));
		
		SubRenderer00->CreateFrameAnimationFolder("IceCream_Ghost", FrameAnimation_DESC("IceCream_Ghost", 0.07f, false));
		SubRenderer00->CreateFrameAnimationFolder("SplitShot_Arms0", FrameAnimation_DESC("SplitShot_Arms", 0, 3, 0.1f, false));
		SubRenderer00->CreateFrameAnimationFolder("SplitShot_Arms1", FrameAnimation_DESC("SplitShot_Arms", 4, 11, 0.06f, true));
		SubRenderer00->CreateFrameAnimationFolder("SplitShot_Arms2", FrameAnimation_DESC("SplitShot_Arms", 12, 12, 0.1f, false));
		SubRenderer00->CreateFrameAnimationFolder("SplitShot_Arms3", FrameAnimation_DESC("SplitShot_Arms", 13, 14, 0.1f, true));
		SubRenderer00->CreateFrameAnimationFolder("SplitShot_Arms4", FrameAnimation_DESC("SplitShot_Arms", 15, 19, 0.06f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowFlake_Death0", FrameAnimation_DESC("SnowFlake_Death", 0, 7, 0.1f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowFlake_Death1", FrameAnimation_DESC("SnowFlake_Death", 8, 32, 0.1f, false));
		SubRenderer00->CreateFrameAnimationFolder("SnowFlake_Death_Alt", FrameAnimation_DESC("SnowFlake_Death_AltBacker", 0.1f, false));

		SubRenderer00->ChangeFrameAnimation("MFIntro");
		SubRenderer00->SetScaleModeImage();
		SubRenderer00->ScaleToTexture();
		SubRenderer00->SetPivot(PIVOTMODE::CENTER);
		//SubRenderer00->Off();
		SubRenderer00->GetTransform().SetLocalPosition({ 0, 0, 0.8f });
	}

	{
		SubRenderer01 = CreateComponent<GameEngineTextureRenderer>();
		SubRenderer01->CreateFrameAnimationFolder("SnowBeastIntro_Backer_Start", FrameAnimation_DESC("SnowBeast_Intro_Backer", 0, 2, 0.08f, true));
		SubRenderer01->CreateFrameAnimationFolder("SnowBeastIntro_Backer", FrameAnimation_DESC("SnowBeast_Intro_Backer", 3, 11, 0.08f, false));
		SubRenderer01->CreateFrameAnimationFolder("SnowBeast_Limbs_MeltingB", FrameAnimation_DESC("SnowBeast_Limbs_MeltingB", 0.06f, false));
		
		SubRenderer01->CreateFrameAnimationFolder("SnowFlake_DeathBacker", FrameAnimation_DESC("SnowFlake_DeathBacker", 0.1f, false));

		SubRenderer01->ChangeFrameAnimation("SnowBeastIntro_Backer_Start");
		SubRenderer01->SetScaleModeImage();
		SubRenderer01->ScaleToTexture();
		SubRenderer01->SetPivot(PIVOTMODE::CENTER);
		SubRenderer01->Off();
	}

	{
		SubRenderer02 = CreateComponent<GameEngineTextureRenderer>();
		SubRenderer02->CreateFrameAnimationFolder("SnowBeast_Limbs_RMeltingA", FrameAnimation_DESC("SnowBeast_Limbs_MeltingA", Rev, 0.04f, false));

		SubRenderer02->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingA");
		SubRenderer02->SetScaleModeImage();
		SubRenderer02->ScaleToTexture();
		SubRenderer02->SetPivot(PIVOTMODE::BOT);
		SubRenderer02->Off();
	}

	{
		SubRenderer03 = CreateComponent<GameEngineTextureRenderer>();
		SubRenderer03->CreateFrameAnimationFolder("SnowBeast_Limbs_RMeltingB", FrameAnimation_DESC("SnowBeast_Limbs_MeltingB", Rev, 0.04f, false));

		SubRenderer03->ChangeFrameAnimation("SnowBeast_Limbs_RMeltingB");
		SubRenderer03->SetScaleModeImage();
		SubRenderer03->ScaleToTexture();
		SubRenderer03->SetPivot(PIVOTMODE::BOT);
		SubRenderer03->Off();
	}

	{
		EffectRenderer00 = CreateComponent<GameEngineTextureRenderer>();
		EffectRenderer00->CreateFrameAnimationFolder("SnowBeast_Jump_FXA", FrameAnimation_DESC("SnowBeast_Jump_FXA", 0.04f, false));
		EffectRenderer00->CreateFrameAnimationFolder("SnowBeast_Dash_FXA", FrameAnimation_DESC("SnowBeast_Dash_FXA", 0.04f, false));

		EffectRenderer00->ChangeFrameAnimation("SnowBeast_Jump_FXA");
		EffectRenderer00->SetScaleModeImage();
		EffectRenderer00->ScaleToTexture();
		EffectRenderer00->SetPivot(PIVOTMODE::BOT);
		EffectRenderer00->Off();
	}

	{
		EffectRenderer01 = CreateComponent<GameEngineTextureRenderer>();
		EffectRenderer01->CreateFrameAnimationFolder("SnowBeast_Jump_FXB", FrameAnimation_DESC("SnowBeast_Jump_FXB", 0.04f, false));
		EffectRenderer01->CreateFrameAnimationFolder("SnowBeast_Dash_FXB", FrameAnimation_DESC("SnowBeast_Dash_FXB", 0.04f, false));

		EffectRenderer01->ChangeFrameAnimation("SnowBeast_Jump_FXB");
		EffectRenderer01->SetScaleModeImage();
		EffectRenderer01->ScaleToTexture();
		EffectRenderer01->SetPivot(PIVOTMODE::BOT);
		EffectRenderer01->Off();
	}

	{
		EffectRenderer02 = CreateComponent<GameEngineTextureRenderer>();
		EffectRenderer02->CreateFrameAnimationFolder("SnowBeastBall_GroundFXA", FrameAnimation_DESC("SnowBeastBall_GroundFXA", 0.04f, true));
		
		EffectRenderer02->ChangeFrameAnimation("SnowBeastBall_GroundFXA");
		EffectRenderer02->SetScaleModeImage();
		EffectRenderer02->ScaleToTexture();
		EffectRenderer02->SetPivot(PIVOTMODE::BOT);
		EffectRenderer02->Off();
	}

	{
		Collision = CreateComponent<GameEngineCollision>();
		Collision->GetTransform().SetLocalScale({ 200,300,1 });
		Collision->ChangeOrder(OBJECTORDER::Boss);
	}

	{
		StartPos.push_back({ 300,-380,-1 });
		StartPos.push_back({ 1350,-380,-1 });
		StartPos.push_back({ 400,-950,-1 });
		StartPos.push_back({ 1250,-950,-1 });

		EndPos.push_back({ 1350,-380,-1 });
		EndPos.push_back({ 300,-380,-1 });
		EndPos.push_back({ 1250,-950,-1 });
		EndPos.push_back({ 400,-950,-1 });
	}

	PhaseManager.CreateStateMember("MFPhase1", std::bind(&MortimerFreezeBoss::Phase1Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase1Start, this, std::placeholders::_1));
	PhaseManager.CreateStateMember("MFPhase2", std::bind(&MortimerFreezeBoss::Phase2Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase2Start, this, std::placeholders::_1));
	PhaseManager.CreateStateMember("MFPhase3", std::bind(&MortimerFreezeBoss::Phase3Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase3Start, this, std::placeholders::_1));
	PhaseManager.ChangeState("MFPhase1");
}

void MortimerFreezeBoss::Update(float _DeltaTime)
{
	PhaseManager.Update(_DeltaTime);

	Collision->IsCollision(CollisionType::CT_OBB2D, OBJECTORDER::Weapon, CollisionType::CT_OBB2D, std::bind(&MortimerFreezeBoss::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

	if (true == GameEngineInput::GetInst()->IsDown("Change_Phase3"))
	{
		PhaseManager.ChangeState("MFPhase3");
	}
}

void MortimerFreezeBoss::Phase1Start(const StateInfo& _Info)
{
	if (false == GameEngineInput::GetInst()->IsKey("Num1_Peashot"))
	{
		GameEngineInput::GetInst()->CreateKey("Num1_Peashot", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Num2_Quadshot", VK_NUMPAD2);
		GameEngineInput::GetInst()->CreateKey("Num3_Whale", VK_NUMPAD3);
	}
	
	StateManager.CreateStateMember("Intro", std::bind(&MortimerFreezeBoss::P1IntroUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P1IntroStart, this, std::placeholders::_1));

	StateManager.CreateStateMember("MF1Idle", std::bind(&MortimerFreezeBoss::P1IdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::P1IdleStart, this, std::placeholders::_1));

	StateManager.CreateStateMember("Peashot", std::bind(&MortimerFreezeBoss::AttackPeashotUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackPeashotStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Quadshot", std::bind(&MortimerFreezeBoss::AttackQuadshotUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackQuadshotStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Whale", std::bind(&MortimerFreezeBoss::AttackWhaleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::AttackWhaleStart, this, std::placeholders::_1));
	StateManager.CreateStateMember("Transition_Phase2", std::bind(&MortimerFreezeBoss::Phase1to2Update, this, std::placeholders::_1, std::placeholders::_2), std::bind(&MortimerFreezeBoss::Phase1to2Start, this, std::placeholders::_1));

	StateManager.ChangeState("Intro");
}

void MortimerFreezeBoss::Phase1Update(float _DeltaTime, const StateInfo& _Info)
{
	StateManager.Update(_DeltaTime);
}

void MortimerFreezeBoss::P1IntroStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFIntro_Top");
	SubRenderer00->ChangeFrameAnimation("MFIntro");

	Renderer->AnimationBindEnd("MFIntro_Top", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("MFIntro_TopLast");
		});

	Renderer->AnimationBindEnd("MFIntro_TopLast", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			GetTransform().SetLocalPosition({ 1350, -380, -1 });
			StateManager.ChangeState("MF1Idle");
		});

	SubRenderer00->AnimationBindEnd("MFIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->Off();
		});

	ReadyWALLOP* RW = GetLevel()->CreateActor<ReadyWALLOP>();
	RW->GetTransform().SetWorldPosition({ 830.0f,-610.0f,-15.0f });
	RW->GetRenderer()->AnimationBindEnd("ReadyWALLOP", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			RW->Death();
		});
}

void MortimerFreezeBoss::P1IntroUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MortimerFreezeBoss::P1IdleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFIdle");

	Renderer->AnimationBindEnd("MFIdleTrans", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsIdleTransState = false;
			Renderer->ChangeFrameAnimation("MFIdle");
			
			if (0 == Num)
			{
				Renderer->GetTransform().PixLocalNegativeX();
			}
			if (1 == Num)
			{
				Renderer->GetTransform().PixLocalPositiveX();
			}

			IdleLerpRatio = 0.0f;
		});
}

void MortimerFreezeBoss::P1IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;
	float PeashotRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float QuadshotRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);
	float WhaleRandomPer = GameEngineRandom::MainRandom.RandomFloat(0.0f, 1.0f);

	if (true == GameEngineInput::GetInst()->IsDown("Num1_Peashot"))
	{
		PeashotRandomPer = 0.7f;
		PeashotStateCount = 0;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Num2_Quadshot"))
	{
		QuadshotRandomPer = 0.8f;
		QuadshotStateCount = 0;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Num3_Whale"))
	{
		WhaleRandomPer = 0.9f;
		WhaleStateCount = 0;
	}

	// 보스의 x값이 300 혹은 1350일 때 랜덤한 확률로 Peashot 상태
	if (0 < HP && (300.0f >= MFCurXPos || 1350.0f <= MFCurXPos))
	{
		if (0.7f >= PeashotRandomPer && 0 == PeashotStateCount)
		{
			PeashotStateCount = GameEngineRandom::MainRandom.RandomInt(3, 5);
			StateManager.ChangeState("Peashot");
			return;
		}

		if (0 >= PeashotStateCount)
		{
			PeashotStateCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}
	}

	// x값이 650 ~ 950일 때 랜덤한 확률 Quadshot 상태
	if (0 < HP && (650.0f <= MFCurXPos && 950.0f >= MFCurXPos))
	{
		if (0.8f >= QuadshotRandomPer && 0 == QuadshotStateCount)
		{
			QuadshotStateCount = GameEngineRandom::MainRandom.RandomInt(3, 5);
			StateManager.ChangeState("Quadshot");
			return;
		}

		if (0 >= QuadshotStateCount)
		{
			QuadshotStateCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}
	}

	// 보스와 플레이어의 x값이 일치할 때 랜덤한 확률로 Whale 상태
	if (0 < HP && (MsChalice::Chalice->GetTransform().GetLocalPosition().x + 10.0f >= MFCurXPos
		&& MsChalice::Chalice->GetTransform().GetLocalPosition().x - 10.0f <= MFCurXPos))
	{
		if (0.9f >= WhaleRandomPer && 0 == WhaleStateCount)
		{
			WhaleStateCount = GameEngineRandom::MainRandom.RandomInt(3, 5);
			StateManager.ChangeState("Whale");
			return;
		}

		if (0 >= WhaleStateCount)
		{
			WhaleStateCount = GameEngineRandom::MainRandom.RandomInt(1, 3);
		}
	}

	if (true == MFMoveReplay)
	{
		if (MFBossDIR::LEFT == CurMFDir)
		{
			MFMoveReplay = false;
			Num = 1;
		}
		if (MFBossDIR::RIGHT == CurMFDir)
		{
			MFMoveReplay = false;
			Num = 0;
		}
	}

	if (true == IsCurRStartPos)
	{
		if (StartPos[1].x <= MFCurXPos)
		{
			IsCurRStartPos = false;
			IsIdleTransState = true;
			CurMFDir = MFBossDIR::LEFT;
			Num = 1;

			if (false == IsP1IdleStart)
			{
				Renderer->ChangeFrameAnimation("MFIdleTrans");
			}
			if (true == IsP1IdleStart)
			{
				IsP1IdleStart = false;
				IsIdleTransState = false;
			}
			--PeashotStateCount;
			--QuadshotStateCount;
			--WhaleStateCount;

			if (0 == HP)
			{
				IsEndPhase1 = true;
				return;
			}
		}

		if (StartPos[0].x + 100 <= MFCurXPos && true == IsEndPhase1)
		{
			StateManager.ChangeState("Transition_Phase2");
			return;
		}
	}
	else
	{
		if (StartPos[0].x >= MFCurXPos)
		{
			IsCurRStartPos = true;
			IsIdleTransState = true;
			CurMFDir = MFBossDIR::RIGHT;
			Num = 0;

			if (false == IsP1IdleStart)
			{
				Renderer->ChangeFrameAnimation("MFIdleTrans");
			}
			if (true == IsP1IdleStart)
			{
				IsP1IdleStart = false;
				IsIdleTransState = false;
			}
			--PeashotStateCount;
			--QuadshotStateCount;
			--WhaleStateCount;

			if (0 == HP)
			{
				IsEndPhase1 = true;
				return;
			}
		}

		if (StartPos[1].x - 100 >= MFCurXPos && true == IsEndPhase1)
		{
			StateManager.ChangeState("Transition_Phase2");
			return;
		}
	}

	if (true == IsIdleTransState)
	{
		return;
	}

	IdleLerpRatio += _DeltaTime;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	LerpPos = float4::LerpLimit(StartPos[Num], EndPos[Num], IdleLerpRatio);
	float LerpY = GameEngineMath::LerpLimit(-200, 200, IdleLerpRatio) * _DeltaTime;
	if (true == IsEndPhase1)
	{
		LerpY = GameEngineMath::LerpLimit(-500, 500, IdleLerpRatio) * _DeltaTime;
	}

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

void MortimerFreezeBoss::AttackPeashotStart(const StateInfo& _Info)
{
	PeashotAttackMoveTime = 0.0f;
	PeashotAttackCount = GameEngineRandom::MainRandom.RandomInt(1, 2);
	IsCurPeashotStartAttack = false;
	IsCurPeashotEnd = false;

	if (true == IsCurRStartPos)
	{
		IsCurPeashotLStartPos = true;
	}
	else
	{
		IsCurPeashotLStartPos = false;
	}

	Renderer->ChangeFrameAnimation("PeashotIntro");
	MortimerFreezeTable* TableActor = GetLevel()->CreateActor<MortimerFreezeTable>(OBJECTORDER::Boss);

	Renderer->AnimationBindStart("PeashotIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::RIGHT == CurMFDir)
			{
				Renderer->GetTransform().PixLocalNegativeX();
			}
		});

	Renderer->AnimationBindEnd("PeashotIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("PeashotIdle");
		});

	Renderer->AnimationBindStart("PeashotShoot", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsCurPeashotStartAttack = true;
		});

	Renderer->AnimationBindEnd("PeashotShoot", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsCurPeashotStartAttack = false;
			Renderer->ChangeFrameAnimation("PeashotIdle");
		});

	Renderer->AnimationBindEnd("PeashotOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			IsP1IdleStart = true;
			IdleLerpRatio = 0.0f;
			StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackPeashotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	float MFCurXPos = GetTransform().GetLocalPosition().x;
	
	PeashotAttackMoveTime += _DeltaTime;

	if (1.0f >= PeashotAttackMoveTime)
	{
		return;
	}

	if (true == IsCurPeashotStartAttack)
	{
		return;
	}

	if (false == IsCurPeashotLStartPos)
	{
		if (StartPos[1].x <= MFCurXPos)
		{
			IsCurPeashotLStartPos = true;
			CurMFDir = MFBossDIR::LEFT;

			if (0 == PeashotAttackCount)
			{
				Renderer->ChangeFrameAnimation("PeashotOutro");
				Renderer->GetTransform().PixLocalPositiveX();
				IsCurRStartPos = true;
				IsCurPeashotEnd = true;
				return;
			}

			Renderer->ChangeFrameAnimation("PeashotShoot");
			Renderer->GetTransform().PixLocalPositiveX();
			Num = 1;
			--PeashotAttackCount;
			IdleLerpRatio = 0.0f;

			MortimerFreezeCard* Ptr = GetLevel()->CreateActor<MortimerFreezeCard>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
			Ptr->SetColMap(MsChalice::Chalice->GetColMap());
		}
	}
	else
	{
		if (StartPos[0].x >= MFCurXPos)
		{
			IsCurPeashotLStartPos = false;
			CurMFDir = MFBossDIR::RIGHT;

			if (0 == PeashotAttackCount)
			{
				Renderer->ChangeFrameAnimation("PeashotOutro");
				Renderer->GetTransform().PixLocalNegativeX();
				IsCurRStartPos = false;
				IsCurPeashotEnd = true;
				return;
			}

			Renderer->ChangeFrameAnimation("PeashotShoot");
			Renderer->GetTransform().PixLocalNegativeX();
			Num = 0;
			--PeashotAttackCount;
			IdleLerpRatio = 0.0f;

			MortimerFreezeCard* Ptr = GetLevel()->CreateActor<MortimerFreezeCard>(OBJECTORDER::Boss);
			Ptr->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
			Ptr->SetColMap(MsChalice::Chalice->GetColMap());
		}
	}

	IdleLerpRatio += _DeltaTime;
	if (1.0f <= IdleLerpRatio)
	{
		IdleLerpRatio = 1.0f;
	}

	LerpPos = float4::LerpLimit(StartPos[Num], EndPos[Num], IdleLerpRatio);
	float LerpY = GameEngineMath::LerpLimit(-200, 200, IdleLerpRatio) * _DeltaTime;

	YAdd += LerpY;
	if (0 <= YAdd)
	{
		YAdd = 0.0f;
	}

	float4 MFMovePos = LerpPos + float4(0, YAdd, 0);
	GetTransform().SetLocalPosition(MFMovePos);
}

void MortimerFreezeBoss::AttackQuadshotStart(const StateInfo& _Info)
{
	int RandomItemNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
	
	Renderer->ChangeFrameAnimation("QuadshotStart");
	Renderer->AnimationBindFrame("QuadshotStart", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (15 == _Info.CurFrame)
			{
				Renderer->ChangeFrameAnimation("QuadshotMinionAppear");
				
				Minion0 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion0->SetDir(DIR::LEFT);
				Minion0->SetMoveDir(RandomItemNum);
				Minion0->SetGender(GENDER::BOY);
				Minion0->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(-340.0f, 20.0f, -1.0f));
				Minion0->SetColMap(MsChalice::Chalice->GetColMap());

				Minion1 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion1->SetDir(DIR::LEFT);
				Minion1->SetMoveDir(RandomItemNum);
				Minion1->SetGender(GENDER::GIRL);
				Minion1->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(-110.0f, -30.0f, -1.0f));
				Minion1->SetColMap(MsChalice::Chalice->GetColMap());

				Minion2 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion2->SetDir(DIR::RIGHT);
				Minion2->SetMoveDir(RandomItemNum);
				Minion2->SetGender(GENDER::BOY);
				Minion2->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(110.0f, -40.0f, -1.0f));
				Minion2->SetColMap(MsChalice::Chalice->GetColMap());

				Minion3 = GetLevel()->CreateActor<MortimerFreezeMinion>(OBJECTORDER::Boss);
				Minion3->SetDir(DIR::RIGHT);
				Minion3->SetMoveDir(RandomItemNum);
				Minion3->SetGender(GENDER::GIRL);
				Minion3->GetTransform().SetLocalPosition(GetTransform().GetLocalPosition() + float4(340.0f, 30.0f, -1.0f));
				Minion3->SetColMap(MsChalice::Chalice->GetColMap());
			}
		});

	Renderer->AnimationBindFrame("QuadshotMinionAfter", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (3 == _Info.CurFrame)
			{
				MinionPixRemove = true;
			}
		});

	Renderer->AnimationBindEnd("QuadshotMinionAfter", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			MFMoveReplay = true;
			StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackQuadshotUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == MinionPixCheck)
	{
		MinionPixCheck = false;

		Renderer->ChangeFrameAnimation("QuadshotMinionAfter");
	}
}

void MortimerFreezeBoss::AttackWhaleStart(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("WhaleDrop");
	Renderer->SetPivot(PIVOTMODE::TOP);
	Renderer->SetPivotToVector(float4{ 0, 250.0f });

	{
		WhaleCollision = CreateComponent<GameEngineCollision>();
		WhaleCollision->GetTransform().SetLocalScale({ 450,100,1 });
		WhaleCollision->GetTransform().SetLocalPosition(float4{ 0.0f,-450.0f });
		WhaleCollision->ChangeOrder(OBJECTORDER::BossWhale);
		WhaleCollision->Off();
	}

	Renderer->AnimationBindFrame("WhaleDrop", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (29 == _Info.CurFrame)
			{
				WhaleCollision->On();
			}
		});

	Renderer->AnimationBindEnd("WhaleDrop", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("WhaleDropAttackOutro");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			Renderer->SetPivotToVector(float4{ 0, -20.0f });

			WhaleCollision->Death();
			// Whale 생성
			MortimerFreezeWhale* Whale = GetLevel()->CreateActor<MortimerFreezeWhale>(OBJECTORDER::Boss);
			Whale->GetTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y * 2 - 115.0f, -1.0f });
		});
	Renderer->AnimationBindEnd("WhaleDropAttackOutro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			StateManager.ChangeState("MF1Idle");
		});
}

void MortimerFreezeBoss::AttackWhaleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void MortimerFreezeBoss::Phase1to2Start(const StateInfo& _Info)
{
	Renderer->ChangeFrameAnimation("MFPhase2Transition0");
	
	Renderer->AnimationBindEnd("MFPhase2Transition0", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			Renderer->ChangeFrameAnimation("MFPhase2Transition1");
			
			if (MFBossDIR::LEFT == CurMFDir)
			{
				AddRenderer->GetTransform().PixLocalPositiveX();
				AddRenderer->GetTransform().SetLocalPosition(float4{ -150.0f, 140.0f, 0.5f });
				AddRenderer->On();
			}
			if (MFBossDIR::RIGHT== CurMFDir)
			{
				AddRenderer->GetTransform().PixLocalNegativeX();
				AddRenderer->GetTransform().SetLocalPosition(float4{ 150.0f, 140.0f, 0.5f });
				AddRenderer->On();
			}
		});

	Renderer->AnimationBindEnd("MFPhase2Transition2", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (MFBossDIR::LEFT == CurMFDir)
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeastIntro_Start");
				SubRenderer00->GetTransform().PixLocalPositiveX();
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 0.0f, 350.0f, -1.5f });
				SubRenderer00->On();

				SubRenderer01->ChangeFrameAnimation("SnowBeastIntro_Backer_Start");
				SubRenderer01->GetTransform().PixLocalPositiveX();
				SubRenderer01->GetTransform().SetLocalPosition(float4{ 0.0f, 350.0f, 0.5f });
				SubRenderer01->On();
			}
			if (MFBossDIR::RIGHT == CurMFDir)
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeastIntro_Start");
				SubRenderer00->GetTransform().PixLocalNegativeX();
				SubRenderer00->GetTransform().SetLocalPosition(float4{ 0.0f, 350.0f, -1.5f });
				SubRenderer00->On();

				SubRenderer01->ChangeFrameAnimation("SnowBeastIntro_Backer_Start");
				SubRenderer01->GetTransform().PixLocalNegativeX();
				SubRenderer01->GetTransform().SetLocalPosition(float4{ 0.0f, 350.0f, 0.5f });
				SubRenderer01->On();
			}
		});

	AddRenderer->AnimationBindEnd("MFPhase2Transition1_Arm", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (0 == Phase2TransitionMotionCount)
			{
				AddRenderer->Off();
				Renderer->ChangeFrameAnimation("MFPhase2Transition2");
				
				if (MFBossDIR::LEFT == CurMFDir)
				{
					Renderer->GetTransform().SetLocalPosition(float4{ -70.0f, 0.0f, 0.0f });
				}
				if (MFBossDIR::RIGHT == CurMFDir)
				{
					Renderer->GetTransform().SetLocalPosition(float4{ 70.0f, 0.0f, 0.0f });
				}
			}

			Phase2TransitionMotionCount -= 1;
		});

	SubRenderer00->AnimationBindFrame("SnowBeastIntro", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			if (9 == _Info.CurFrame)
			{
				Renderer->Off();
			}
			if (40 == _Info.CurFrame)
			{
				IsSnowBeastIntroMoveDown = true;
				SubRenderer00->ChangeFrameAnimation("SnowBeastIntro_Fall");
			}
		});

	SubRenderer00->AnimationBindTime("SnowBeastIntro_Fall", [/*&*/=](const FrameAnimation_DESC& _Info, float _Delta)
		{
			if (true == IsSnowBeastIntroLand)
			{
				SubRenderer00->ChangeFrameAnimation("SnowBeastIntro_Land");
			}
		});

	SubRenderer00->AnimationBindEnd("SnowBeastIntro_Land", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer00->Off();

			PhaseManager.ChangeState("MFPhase2");
		});

	SubRenderer01->AnimationBindEnd("SnowBeastIntro_Backer", [/*&*/=](const FrameAnimation_DESC& _Info)
		{
			SubRenderer01->Off();
		});
}

void MortimerFreezeBoss::Phase1to2Update(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsSnowBeastIntroStartEnd)
	{
		IsSnowBeastIntroStartEnd = false;

		SubRenderer00->ChangeFrameAnimation("SnowBeastIntro");
		SubRenderer01->ChangeFrameAnimation("SnowBeastIntro_Backer");
	}

	if (true == SubRenderer00->IsUpdate() || true == SubRenderer01->IsUpdate())
	{
		if (Renderer->GetTransform().GetLocalPosition().y + 70.0f > SubRenderer00->GetTransform().GetLocalPosition().y)
		{
			SubRenderer00->GetTransform().SetLocalPosition(float4{ 0,Renderer->GetTransform().GetLocalPosition().y + 70.0f ,0 });

			if (1 == SnowBeastIntroCount)
			{
				--SnowBeastIntroCount;
				IsSnowBeastIntroStartEnd = true;
			}
		}
		if (Renderer->GetTransform().GetLocalPosition().y + 70.0f > SubRenderer01->GetTransform().GetLocalPosition().y)
		{
			SubRenderer01->GetTransform().SetLocalPosition(float4{ 0,Renderer->GetTransform().GetLocalPosition().y + 70.0f ,0 });

			//IsSnowBeastIntroStartEnd = true;
		}
	}

	if (true == IsSnowBeastIntroMoveDown)
	{
		if (-820.0f >= GetTransform().GetLocalPosition().y)
		{
			if (false == IsSnowBeastIntroLand)
			{
				IsSnowBeastIntroLand = true;
			}
			
			GetTransform().SetLocalPosition(GetTransform().GetLocalPosition());
			
			SubRenderer00->GetTransform().SetLocalPosition(float4{ 0.0f,-130.0f,0.0f });
			SubRenderer00->SetPivot(PIVOTMODE::BOT);
			
			//Collision->GetTransform().SetLocalPosition(float4{ 0.0f,150.0f,0.0f });

			return;
		}
		else
		{
			GetTransform().SetLocalMove(GetTransform().GetDownVector() * _DeltaTime * 800.0f);
		}
	}

	SubRenderer00->GetTransform().SetLocalMove(GetTransform().GetDownVector() * _DeltaTime * 700.0f);
	SubRenderer01->GetTransform().SetLocalMove(GetTransform().GetDownVector() * _DeltaTime * 700.0f);
}

