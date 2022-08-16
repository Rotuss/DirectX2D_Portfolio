#pragma once
#include <map>
#include <list>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>

enum class CAMERAORDER
{
	MAINCAMERA,
	USER0,
	USER1,
	USER2,
	USER3,
	USER4,
	USER5,
	USER6,
	USER7,
	UICAMERA,
};

// 설명 : 화면(타이틀 화면, 플레이 화면, 인벤토리 화면)
class GameEngineCore;
class GameEngineActor;
class GameEngineCamera;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineTransform;
class GameEngineCameraActor;
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend GameEngineCore;
	friend GameEngineActor;
	friend GameEngineCamera;
	friend GameEngineRenderer;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	GameEngineCamera* GetMainCamera()
	{
		return Cameras[static_cast<int>(CAMERAORDER::MAINCAMERA)];
	}

	GameEngineCamera* GetUICamera()
	{
		return Cameras[static_cast<int>(CAMERAORDER::UICAMERA)];
	}

	GameEngineCameraActor* GetMainCameraActor();
	GameEngineTransform& GetMainCameraActorTransform();

	GameEngineCameraActor* GetUICameraActor();
	GameEngineTransform& GetUICameraActorTransform();

	template<typename ActorType, typename GroupIndexType>
	ActorType* CreateActor(GroupIndexType _ObjectGroupIndex)
	{
		return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ActorType>
	ActorType* CreateActor(const std::string _Name, int _ObjectGroupIndex = 0)
	{
		CreateActor(_ObjectGroupIndex);
	}

	template<typename ActorType>
	ActorType* CreateActor(int _ObjectGroupIndex = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->SetOrder(_ObjectGroupIndex);
		NewActor->Start();

		PushActor(NewActor, _ObjectGroupIndex);

		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename GroupIndexType>
	std::list<GameEngineActor*> GetGroup(GroupIndexType _ObjectGroupIndex)
	{
		return AllActors[static_cast<int>(_ObjectGroupIndex)];
	}

	std::list<GameEngineActor*> GetGroup(int _ObjectGroupIndex)
	{
		return AllActors[_ObjectGroupIndex];
	}

	template<typename ObjectType, typename GroupIndexType>
	std::list<ObjectType*> GetConvertToGroup(GroupIndexType _ObjectGroupIndex)
	{
		return GetConvertToGroup<ObjectType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ObjectType>
	std::list<ObjectType*> GetConvertToGroup(int _ObjectGroupIndex)
	{
		std::list<ObjectType*> Result;
		for (GameEngineActor* Object : AllActors[_ObjectGroupIndex])
		{
			Result.push_back(dynamic_cast<ObjectType*>(Object));
		}

		return Result;
	}

	void AllClear();

protected:

private:
	std::map<int, std::list<GameEngineActor*>> AllActors;
	std::map<int, std::list<GameEngineCollision*>> AllCollisions;
	std::list<GameEngineUpdateObject*> DeleteObject;
	std::vector<GameEngineCamera*> Cameras;

	void PushActor(GameEngineActor* _Actor, int _ObjectGroupIndex);
	void ActorOnEvent();
	void ActorOffEvent();
	void ActorUpdate(float _DeltaTime);
	void LevelUpdate(float _DeltaTime);
	void RemoveActor(GameEngineActor* _Actor);
	void OverChildMove(GameEngineLevel* _NextLevel);

private:
	void PushCamera(GameEngineCamera* _Camera, CAMERAORDER _Order)
	{
		PushCamera(_Camera, static_cast<int>(_Order));
	}

	void PushRendererToMainCamera(GameEngineRenderer* _Renderer)
	{
		PushRenderer(_Renderer, static_cast<int>(CAMERAORDER::MAINCAMERA));
	}

	void PushRendererToUICamera(GameEngineRenderer* _Renderer)
	{
		PushRenderer(_Renderer, static_cast<int>(CAMERAORDER::UICAMERA));
	}

	void PushRenderer(GameEngineRenderer* _Renderer, CAMERAORDER _Order)
	{
		PushRenderer(_Renderer, static_cast<int>(_Order));
	}

	void PushCamera(GameEngineCamera* _Camera, int _CameraOrder);

	void PushRenderer(GameEngineRenderer* _Renderer, int _CameraOrder);

	void PushCollision(GameEngineCollision* _Collision, int _Order);

	void Render(float _DelataTime);

	void Release(float _DelataTime);
};

