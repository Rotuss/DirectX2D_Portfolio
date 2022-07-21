#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"

GameEngineLevel::GameEngineLevel() 
	: MainCamera(nullptr)
	, UIMainCamera(nullptr)
{
}

GameEngineLevel::~GameEngineLevel() 
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		for (GameEngineActor* Actor : Group.second)
		{
			if (nullptr == Actor)
			{
				continue;
			}

			Actor->ReleaseHierarchy();
		}
	}
}

GameEngineTransform& GameEngineLevel::GetMainCameraActorTransform()
{
	return MainCamera->GetActor()->GetTransform();
}

void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	for (const std::pair<int, std::list<GameEngineActor*>>& Group : AllActors)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

		for (GameEngineActor* const Actor : Group.second)
		{
			if (false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->AllUpdate(ScaleTime, _DeltaTime);
		}
	}
}

void GameEngineLevel::LevelUpdate(float _DeltaTime)
{
	AddAccTime(_DeltaTime);
	Update(_DeltaTime);
	ActorUpdate(_DeltaTime);
	Render(_DeltaTime);
	Release(_DeltaTime);
}

void GameEngineLevel::RemoveActor(GameEngineActor* _Actor)
{
	if (AllActors.end() == AllActors.find(_Actor->GetOrder()))
	{
		MsgBoxAssert("이액터를 루트가 아닙니다 삭제할수 없습니다.");
	}

	AllActors[_Actor->GetOrder()].remove(_Actor);
}

void GameEngineLevel::PushCamera(GameEngineCamera* _Camera)
{
	MainCamera = _Camera;
}

void GameEngineLevel::PushRenderer(GameEngineRenderer* _Renderer)
{
	MainCamera->PushRenderer(_Renderer);
}

void GameEngineLevel::Render(float _DelataTime)
{
	MainCamera->Render(_DelataTime);
}

void GameEngineLevel::Release(float _DelataTime)
{
	for (GameEngineUpdateObject* Object : DeleteObject)
	{
		Object->ReleaseHierarchy();
	}

	DeleteObject.clear();
	
	MainCamera->Release(_DelataTime);

	std::map<int, std::list<GameEngineActor*>>::iterator StartGroupIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator EndGroupIter = AllActors.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineActor*>& Group = StartGroupIter->second;

		std::list<GameEngineActor*>::iterator GroupStart = Group.begin();
		std::list<GameEngineActor*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseObject(DeleteObject);
			if (true == (*GroupStart)->IsDeath())
			{
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}
		}
	}
}

