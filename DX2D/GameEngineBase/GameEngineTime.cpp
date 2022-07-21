#include "PreCompile.h"
#include "GameEngineTime.h"

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

void GameEngineTime::Reset()
{
}

void GameEngineTime::Update()
{
}

GameEngineTime::GameEngineTime()
{
	Prev = std::chrono::steady_clock::now();
	
	Update();
}

GameEngineTime::~GameEngineTime() 
{
	std::chrono::steady_clock::time_point Current = std::chrono::steady_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(Current - Prev);

	DeltaTimed = time_span.count();

	Prev = Current;
	
	DeltaTimef = static_cast<float>(DeltaTimed);
}

