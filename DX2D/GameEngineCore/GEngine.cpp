#include "PreCompile.h"
#include "GEngine.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

bool GEngine::CollisionDebug = false;

void GEngine::ChangeLevel(std::string _Name)
{
	GameEngineCore::ChangeLevel(_Name);
}

void GEngine::CollisionDebugOn()
{
	CollisionDebug = true;
}

void GEngine::CollisionDebugOff()
{
	CollisionDebug = false;
}

void GEngine::CollisionDebugSwitch()
{
	CollisionDebug = !CollisionDebug;
}

bool GEngine::IsCollisionDebug()
{
	return CollisionDebug;
}

GameEngineLevel* GEngine::GetCurrentLevel()
{
	return GameEngineCore::GetCurLevel();
}

GEngine::GEngine()
{
}

GEngine::~GEngine() 
{
}

