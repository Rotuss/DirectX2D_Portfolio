#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

void GameEngineTime::Reset()
{
}

void GameEngineTime::Update()
{
}

GameEngineTime::GameEngineTime()
{
	Update();
}

GameEngineTime::~GameEngineTime() 
{
}

