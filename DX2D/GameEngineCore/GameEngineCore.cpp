#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineGUI.h"
#include "GameEngineLevel.h"
#include "GameEngineDevice.h"
#include "GameEngineCamera.h"
#include "GameEngineCoreDebug.h"
#include "GameEngineCameraActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineDevice.h>

#pragma comment(lib, "GameEngineBase.lib")

GameEngineLevel* GameEngineCore::CurrentLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevels;

GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

GameEngineLevel* GameEngineCore::FindLevel(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevels.find(UpperName);
	
	if (FindIter == AllLevels.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

bool GameEngineCore::ChangeLevel(const std::string& _Name)
{
	NextLevel = FindLevel(_Name);

	if (nullptr == NextLevel)
	{
		MsgBoxAssert("존재하지 않는 레벨로 바꾸려고 했습니다.");
		return false;
	}

	return true;
}

void GameEngineCore::WindowCreate(const std::string& _Name, GameEngineCore* _UserCore)
{
	GameEngineWindow::GetInst()->CreateGameWindow(nullptr, _Name.c_str());
	GameEngineWindow::GetInst()->SetWindowScaleAndPosition(_UserCore->StartWindowPosition(), _UserCore->StartWindowSize());
	GameEngineWindow::GetInst()->ShowGameWindow();
	GameEngineDevice::Initialize();

	GameEngineWindow::GetInst()->MessageLoop(std::bind(&GameEngineCore::CoreStart, _UserCore), std::bind(&GameEngineCore::CoreUpdate, _UserCore), std::bind(&GameEngineCore::CoreEnd, _UserCore));
}

void GameEngineCore::CoreStart(GameEngineCore* _UserCore)
{
	GameEngineGUI::Initialize();
	
	EngineResourcesInitialize();

	GameEngineDevice::CreateSwapChain();

	GameEngineDebug::Debug3DInitialize();

	_UserCore->Start();
}

void GameEngineCore::CoreUpdate(GameEngineCore* _UserCore)
{
	if (nullptr != NextLevel)
	{
		Rectangle(GameEngineWindow::GetInst()->GetHDC(), 0, 0, GameEngineWindow::GetInst()->GetScale().ix(), GameEngineWindow::GetInst()->GetScale().iy());
		
		if (nullptr != CurrentLevel)
		{
			CurrentLevel->ActorLevelEndEvent();
			CurrentLevel->LevelEndEvent();
			CurrentLevel->OverChildMove(NextLevel);
		}

		CurrentLevel = NextLevel;
		NextLevel = nullptr;

		CurrentLevel->LevelStartEvent();
		CurrentLevel->ActorLevelStartEvent();
		CurrentLevel->ReSetAccTime();
		GameEngineTime::GetInst()->Reset();
	}

	if (nullptr == CurrentLevel)
	{
		MsgBoxAssert("레벨을 지정해주지 않으면 엔진을 시작할 수 없습니다.");
	}

	GameEngineTime::GetInst()->Update();
	GameEngineSound::Update();

	float DeltaTime = GameEngineTime::GetDeltaTime();
	
	GameEngineInput::GetInst()->Update(DeltaTime);

	_UserCore->Update(DeltaTime);

	CurrentLevel->LevelUpdate(DeltaTime);
}

void GameEngineCore::CoreEnd(GameEngineCore* _UserCore)
{
	_UserCore->End();

	for (auto& Level : AllLevels)
	{
		if (nullptr == Level.second)
		{
			continue;
		}
		delete Level.second;
		Level.second = nullptr;
	}

	GameEngineGUI::GUIDestroy();

	EngineResourcesDestroy();
	
	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineDebug::Destroy();
	GameEngineTime::Destroy();
}

void GameEngineCore::InitializeLevel(GameEngineLevel* _Level, const std::string _Name)
{
	_Level->Start();
	_Level->SetName(_Name);

	AllLevels.insert(std::make_pair(_Name, _Level));
}
