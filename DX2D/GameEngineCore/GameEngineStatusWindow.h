#pragma once
#include "GameEngineGUI.h"

class GameEngineImageShotWindow : public GameEngineGUIWindow
{
public:
	void RenderTextureSetting(ImTextureID _RenderTexture, ImVec2 _Size);

	void Initialize(class GameEngineLevel* _Level) {}
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	ImTextureID RenderTexture;
	ImVec2		Size;
};

// Ό³Έν :
class GameEngineStatusWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	GameEngineStatusWindow();
	~GameEngineStatusWindow();

	// delete Function
	GameEngineStatusWindow(const GameEngineStatusWindow& _Other) = delete;
	GameEngineStatusWindow(GameEngineStatusWindow&& _Other) noexcept = delete;
	GameEngineStatusWindow& operator=(const GameEngineStatusWindow& _Other) = delete;
	GameEngineStatusWindow& operator=(GameEngineStatusWindow&& _Other) noexcept = delete;

	static void AddDebugRenderTarget(const std::string& _DebugName, GameEngineRenderTarget* _RenderTarget);

protected:

private:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	static std::map<std::string, GameEngineRenderTarget*> DebugRenderTarget;

	std::list<GameEngineImageShotWindow*> Window;
};

