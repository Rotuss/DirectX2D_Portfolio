#include "PreCompile.h"
#include "WorldMapLevel.h"
#include "WorldMapBackGround.h"
#include "Player.h"
#include "OverWorldCuphead.h"
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

void WorldMapLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	
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
		Renderer->GetTransform().SetLocalPosition({ 1150, -1350 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldCart", FrameAnimation_DESC("World_Cart", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldCart");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1400, -600 });
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
		Renderer->GetTransform().SetLocalPosition({ 1800, -500 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldOmm", FrameAnimation_DESC("World_Omm", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldOmm");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 2490, -450 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("WorldSnow", FrameAnimation_DESC("World_Snow", 0.1f, true));
		Renderer->ChangeFrameAnimation("WorldSnow");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 3280, -650 });
	}

	// 기타 구조물
	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("bakery_neighbor.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 880, -645 });
	}
	
	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs_back_shadow.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 1650, -1550 });
	}
	
	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_canyon_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 1680, -1550 });
	}

	{
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
		Renderer->GetTransform().SetLocalPosition({ 2393, -735, -10 });
	}

	{
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
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_top.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2659, -785, -10 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs_front.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2770, -835, -10 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_ice_stairs.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2800, -800 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_stepping_stone_bridge_bottom.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 2950, -1120 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("hangar_18.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 3012, -1436, -10 });
	}

	{
		Renderer = WorldBackGround->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("lighthouse.png");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::LEFTTOP);
		Renderer->GetTransform().SetLocalPosition({ 3118, -1300, -10 });
	}

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
		NPCRenderer->GetTransform().SetLocalPosition({ 1600, -780 });
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
