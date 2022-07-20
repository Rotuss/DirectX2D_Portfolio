#include "GEngine.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

void GEngine::ChangeLevel(std::string _Name)
{
	GameEngineCore::ChangeLevel(_Name);
}

GEngine::GEngine()
{
}

GEngine::~GEngine() 
{
}

