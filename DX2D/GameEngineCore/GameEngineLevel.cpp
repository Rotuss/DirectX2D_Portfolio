#include "PreCompile.h"
#include "GameEngineGUI.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineCollision.h"
#include "GameEngineCameraActor.h"

GameEngineLevel::GameEngineLevel() 
{
	Cameras.resize(static_cast<unsigned int>(CAMERAORDER::UICAMERA));

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::MAINCAMERA);
	}

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::UICAMERA);
	}
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

GameEngineCameraActor* GameEngineLevel::GetMainCameraActor()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetMainCameraActorTransform()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)]->GetActor()->GetTransform();
}

GameEngineCameraActor* GameEngineLevel::GetUICameraActor()
{
	return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& GameEngineLevel::GetUICameraActorTransform()
{
	return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)]->GetActor()->GetTransform();
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
		MsgBoxAssert("이 액터는 루트가 아닙니다. 삭제할 수 없습니다.");
	}

	AllActors[_Actor->GetOrder()].remove(_Actor);
}

void GameEngineLevel::OverChildMove(GameEngineLevel* _NextLevel)
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator StartGroupIter = AllActors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator EndGroupIter = AllActors.end();

		std::list<GameEngineActor*> OverList;

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineActor*>& Group = StartGroupIter->second;

			std::list<GameEngineActor*>::iterator GroupStart = Group.begin();
			std::list<GameEngineActor*>::iterator GroupEnd = Group.end();
			for (; GroupStart != GroupEnd; )
			{
				if (true == (*GroupStart)->IsLevelOver)
				{
					OverList.push_back((*GroupStart));
					GroupStart = Group.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}
			}
		}

		for (GameEngineActor* OverActor : OverList)
		{
			OverActor->SetLevel(_NextLevel);
			_NextLevel->AllActors[OverActor->GetOrder()].push_back(OverActor);
		}
	}

	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->OverRenderer(_NextLevel->Cameras[i]);
	}

	{
		std::map<int, std::list<GameEngineCollision*>>::iterator StartGroupIter = AllCollisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator EndGroupIter = AllCollisions.end();

		std::list<GameEngineCollision*> OverList;

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineCollision*>& Group = StartGroupIter->second;

			std::list<GameEngineCollision*>::iterator GroupStart = Group.begin();
			std::list<GameEngineCollision*>::iterator GroupEnd = Group.end();
			for (; GroupStart != GroupEnd; )
			{
				if (true == (*GroupStart)->GetRoot<GameEngineActor>()->IsLevelOver)
				{
					OverList.push_back((*GroupStart));
					GroupStart = Group.erase(GroupStart);
				}
				else
				{
					++GroupStart;
				}
			}
		}

		for (GameEngineCollision* OverActor : OverList)
		{
			_NextLevel->AllCollisions[OverActor->GetOrder()].push_back(OverActor);
		}
	}
}

void GameEngineLevel::PushCamera(GameEngineCamera* _Camera, int _CameraOrder)
{
	Cameras.resize(_CameraOrder + 1);
	
	Cameras[_CameraOrder] = _Camera;
}

void GameEngineLevel::PushRenderer(GameEngineRenderer* _Renderer, int _CameraOrder)
{
	Cameras[static_cast<UINT>(_Renderer->CameraOrder)]->AllRenderer_[_Renderer->GetOrder()].remove(_Renderer);

	_Renderer->CameraOrder = static_cast<CAMERAORDER>(_CameraOrder);
	
	Cameras[_CameraOrder]->PushRenderer(_Renderer);
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _Order)
{
	AllCollisions[_Collision->GetOrder()].remove(_Collision);

	_Collision->SetOrder(_Order);

	AllCollisions[_Collision->GetOrder()].push_back(_Collision);
}

void GameEngineLevel::Render(float _DelataTime)
{
	GameEngineDevice::RenderStart();
	
	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->Render(_DelataTime);
	}

	GameEngineGUI::GUIRender(this, _DelataTime);
	GameEngineDevice::RenderEnd();
}

void GameEngineLevel::Release(float _DelataTime)
{
	for (GameEngineUpdateObject* Object : DeleteObject)
	{
		Object->ReleaseHierarchy();
	}

	DeleteObject.clear();
	
	for (size_t i = 0; i < Cameras.size(); i++)
	{
		if (nullptr == Cameras[i])
		{
			continue;
		}

		Cameras[i]->Release(_DelataTime);
	}

	{
		std::map<int, std::list<GameEngineCollision*>>::iterator StartGroupIter = AllCollisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator EndGroupIter = AllCollisions.end();

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineCollision*>& Group = StartGroupIter->second;

			std::list<GameEngineCollision*>::iterator GroupStart = Group.begin();
			std::list<GameEngineCollision*>::iterator GroupEnd = Group.end();

			for (; GroupStart != GroupEnd; )
			{
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

	{
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
}

