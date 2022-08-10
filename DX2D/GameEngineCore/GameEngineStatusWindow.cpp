#include "PreCompile.h"
#include "GameEngineStatusWindow.h"
#include "GEngine.h"
#include "GameEngineCameraActor.h"
#include "GameEngineRenderTarget.h"

GameEngineStatusWindow::GameEngineStatusWindow() 
{
}

GameEngineStatusWindow::~GameEngineStatusWindow() 
{
}

void GameEngineStatusWindow::Initialize(class GameEngineLevel* _Level)
{
}

void GameEngineStatusWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	int FPS = static_cast<int>(1.0f / _DeltaTime);

	std::string Name = "FPS : " + std::to_string(FPS);
	ImGui::Text(Name.c_str());

	if (true == ImGui::Button("CollisionDebugSwtich"))
	{
		GEngine::CollisionDebugSwitch();
	}

	if (true == ImGui::Button("FreeCameaOnOff"))
	{
		GEngine::GetCurrentLevel()->GetMainCameraActor()->FreeCameraModeOnOff();
	}

	ImGui::Text("Level Select");
	for (std::pair<std::string, GameEngineLevel*> Pair : GameEngineCore::AllLevels)
	{
		if (true == ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}

		ImGui::SameLine();
	}

	ImGui::NewLine();

	std::string AllRenderTarget = "AllRenderTarget";
	ImGui::Text(AllRenderTarget.c_str());

	for (std::pair<std::string, GameEngineRenderTarget*> RenderTargetPair : GameEngineRenderTarget::NamedRes)
	{
		if (true == ImGui::TreeNodeEx(RenderTargetPair.first.c_str(), 0))
		{
			GameEngineRenderTarget* RenderTarget = RenderTargetPair.second;

			for (ID3D11ShaderResourceView* _View : RenderTarget->ShaderResourceViews)
			{
				float4 Scale = GameEngineWindow::GetScale() * 0.2f;

				if (true == ImGui::ImageButton(static_cast<ImTextureID>(_View), { Scale.x, Scale.y }))
				{
					GameEngineImageShotWindow* NewWindow = GameEngineGUI::CreateGUIWindow<GameEngineImageShotWindow>("ImageShot", nullptr);
					NewWindow->RenderTextureSetting(static_cast<ImTextureID>(_View), { GameEngineWindow::GetScale().x ,GameEngineWindow::GetScale().y });
				}
			}

			ImGui::TreePop();
		}
	}
}

void GameEngineImageShotWindow::RenderTextureSetting(ImTextureID _RenderTexture, ImVec2 _Size)
{
	RenderTexture = _RenderTexture;
	Size = _Size;
}

void GameEngineImageShotWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (true == ImGui::ImageButton(RenderTexture, { Size.x, Size.y }))
	{
		Off();
	}
}
