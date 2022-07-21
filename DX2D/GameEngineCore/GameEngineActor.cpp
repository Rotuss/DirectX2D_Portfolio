#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineComponent.h"
#include "GameEngineTransformComponent.h"

GameEngineActor::GameEngineActor() 
	:ParentLevel(nullptr)
{
}

GameEngineActor::~GameEngineActor() 
{
}

void GameEngineActor::SettingTransformComponent(GameEngineTransformComponent* TransCom)
{
	TransCom->GetTransform().SetParentTransform(GetTransform());
}

void GameEngineActor::Start()
{
}

void GameEngineActor::Update(float _DeltaTime)
{
}

void GameEngineActor::End()
{
}

void GameEngineActor::ComponentUpdate(float _ScaleDeltaTime, float _DeltaTime)
{
	for (GameEngineComponent* Com : AllComList)
	{
		Com->AddAccTime(_DeltaTime);
		Com->Update(_ScaleDeltaTime);
	}
}

void GameEngineActor::ComponentCalculateTransform()
{
	GetTransform().CalculateWorld();
}
