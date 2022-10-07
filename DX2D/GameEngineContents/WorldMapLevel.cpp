#include "PreCompile.h"
#include "WorldMapLevel.h"
#include "WorldMapBackGround.h"
#include "Iris.h"
#include "Player.h"
#include "OverWorldCuphead.h"
#include "GlobalContents.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineBlur.h>

WorldMapLevel::WorldMapLevel() 
	: Renderer(nullptr)
	, NPCRenderer(nullptr)
{
}

WorldMapLevel::~WorldMapLevel() 
{
}

void WorldMapLevel::LevelStartEvent()
{
	GlobalContents::Actors::BGM.Stop();
	if (true == GlobalContents::Actors::IsClear)
	{
		GlobalContents::Actors::IsClear = false;
		
		// OverWorldCuphead 상태 변경
		OverWorldCuphead::OWCuphead->BossClear();

		// win 사운드 따로
		GlobalContents::Actors::BGM = GameEngineSound::SoundPlayControl("mus_dlc_map_b.wav");
	}
	else
	{
		GlobalContents::Actors::BGM = GameEngineSound::SoundPlayControl("mus_dlc_map_a.wav");

		Iris* FX = CreateActor<Iris>(OBJECTORDER::Title);
		FX->SetAnimType(AnimType::Back);
		FX->GetRenderer()->AnimationBindEnd("IrisFXRev", [/*&*/=](const FrameAnimation_DESC& _Info)
			{
				FX->Death();
			});
	}
}

void WorldMapLevel::LevelEndEvent()
{
	GlobalContents::Actors::BGM.Stop();
}

void WorldMapLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetIrisCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	if (false == GameEngineInput::GetInst()->IsKey("ChangeTutorial"))
	{
		GameEngineInput::GetInst()->CreateKey("ChangeTutorial", 'T');
	}

	if (false == GameEngineInput::GetInst()->IsKey("Select"))
	{
		GameEngineInput::GetInst()->CreateKey("Select", 'Z');
		GameEngineInput::GetInst()->CreateKey("Back", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("Up", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
	}

	WorldMapBackGround* WorldBackGround = CreateActor<WorldMapBackGround>(OBJECTORDER::World);
	
	{
		OverWorldCuphead* NewCH = CreateActor<OverWorldCuphead>(OBJECTORDER::Player);

		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_land_Col.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		//Renderer->GetTransform().SetWorldPosition({0, 0, -100});
		//Renderer->GetPixelData().MulColor.a = 0.3f;
		Renderer->Off();
		NewCH->SetColMap(Renderer);
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_water_multiply.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetWorldPosition({-400, 300});
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_land.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldSaltbaker", FrameAnimation_DESC("World_Saltbaker", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldSaltbaker");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1020, -530 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldRumrunners", FrameAnimation_DESC("World_Rumrunners", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldRumrunners");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1145, -1365 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldCart", FrameAnimation_DESC("World_Cart", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldCart");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1420, -610 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldCowgirl", FrameAnimation_DESC("World_Cowgirl", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldCowgirl");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1500, -1800 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldShop", FrameAnimation_DESC("World_Shop", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldShop");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1750, -516 });
	}

	{// 수정 필요(모르겠다)
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldOmm", FrameAnimation_DESC("World_Omm", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldOmm");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2505, -380 });
	}

	{// ㅠㅅㅠ
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldSnow", FrameAnimation_DESC("World_Snow", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldSnow");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3250, -645 });

		GameEngineCollision* SnowCollision = WorldBackGround->CreateComponent<GameEngineCollision>();
		SnowCollision->GetTransform().SetLocalScale({ 280.0f, 280.0f, 1.0f });
		SnowCollision->GetTransform().SetLocalPosition({ 3250, -645 });
		SnowCollision->ChangeOrder(OBJECTORDER::WorldSnow);
	}

	// 기타 구조물
	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("bakery_neighbor.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 828, -547 });
	}
	
	{// 수정 필요
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs_back_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 1650, -1550 });
	}
	
	{// 수정 필요
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 1680, -1550 });
	}

	{// 수정 필요
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_wood_bridge.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2200, -1600 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("picnic_table.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2243, -628, -10 });
	}

	/*{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("graves_back.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2405, -1100, -5 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("graves_front.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2410, -1265, -5 });
	}*/

	{// 약간의 수정 필요
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_top.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2624, -709, -10 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_front.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2652, -708, -10 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2620, -635 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_bottom.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2775, -1035 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("hangar_18.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 3012, -1436, -10 });
	}

	/*{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lighthouse.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 3118, -1300, -10 });
	}*/

	// NPC
	{
		NPCRenderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		NPCRenderer->CreateFrameAnimationFolder("BoatMan", FrameAnimation_DESC("BoatMan", 0.1f, true));
		NPCRenderer->ChangeFrameAnimation("BoatMan");
		NPCRenderer->ScaleToTexture();
		NPCRenderer->GetTransform().SetLocalPosition({ 250, -1450 });
	}
	
	{
		NPCRenderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		NPCRenderer->CreateFrameAnimationFolder("NewsieCat", FrameAnimation_DESC("NewsieCat", 0.1f, true));
		NPCRenderer->ChangeFrameAnimation("NewsieCat");
		NPCRenderer->ScaleToTexture();
		NPCRenderer->GetTransform().SetLocalPosition({ 1630, -800 });
	}
	
	{
		NPCRenderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		NPCRenderer->CreateFrameAnimationFolder("CactusGirl", FrameAnimation_DESC("CactusGirl", 0.1f, true));
		NPCRenderer->ChangeFrameAnimation("CactusGirl");
		NPCRenderer->ScaleToTexture();
		NPCRenderer->GetTransform().SetLocalPosition({ 1830, -1800 });
	}

	{
		NPCRenderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		NPCRenderer->CreateFrameAnimationFolder("GhostDetective", FrameAnimation_DESC("GhostDetective", 0.1f, true));
		NPCRenderer->ChangeFrameAnimation("GhostDetective");
		NPCRenderer->ScaleToTexture();
		NPCRenderer->GetTransform().SetLocalPosition({ 2690, -1150 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_top.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 10, 0, -10 });
	}


}

void WorldMapLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	if (GameEngineInput::GetInst()->IsDown("ChangeTutorial"))
	{
		GEngine::ChangeLevel("Tutorial");
	}
}

void WorldMapLevel::End()
{
}
