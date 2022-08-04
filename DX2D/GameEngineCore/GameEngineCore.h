#pragma once
#include <map>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>

// ���� :
class GameEngineCore
{
	friend class GEngine;

public:
	template<typename CoreType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		CoreType Core;
		WindowCreate(Core.GetWindowTitle(), &Core);
	}

protected:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	virtual std::string GetWindowTitle() { return "MainWindow"; }
	virtual float4 StartWindowSize() { return { 1280.0f, 720.0f }; }
	virtual float4 StartWindowPosition() { return { 0,0 }; }

	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void End() = 0;

	static class GameEngineLevel* FindLevel(const std::string& _Name);
	
	template<typename LevelType>
	static GameEngineLevel* CreateLevel(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		GameEngineLevel* NewLevel = new LevelType();
		InitializeLevel(NewLevel, UpperName);
		return NewLevel;
	}

	static bool ChangeLevel(const std::string& _Name);

private:
	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	static void WindowCreate(const std::string& _Name, GameEngineCore* _UserCore);
	static void CoreStart(GameEngineCore* _UserCore);
	static void CoreUpdate(GameEngineCore* _UserCore);
	static void CoreEnd(GameEngineCore* _UserCore);

	static void EngineResourcesInitialize();
	static void EngineResourcesDestroy();
	
	static std::map<std::string, class GameEngineLevel*> AllLevels;
	static GameEngineLevel* CurrentLevel;
	static GameEngineLevel* NextLevel;

	static void InitializeLevel(GameEngineLevel* _Level, const std::string _Name);
};

