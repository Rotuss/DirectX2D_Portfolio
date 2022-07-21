#include "PreCompile.h"
#include "GameEngineComponent.h"

GameEngineComponent::GameEngineComponent() 
{
}

GameEngineComponent::~GameEngineComponent() 
{
}

void GameEngineComponent::SetParent(GameEngineUpdateObject* _Parent)
{
	GameEngineUpdateObject::SetParent(_Parent);
}

