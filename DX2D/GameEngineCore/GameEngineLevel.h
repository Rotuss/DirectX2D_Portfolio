#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>

// 설명 : 화면(타이틀 화면, 플레이 화면, 인벤토리 화면)
class GameEngineActor;
class GameEngineLevel :
	public GameEngineNameObject,
	public GameEngineUpdateObject
{
	friend class GameEngineRenderer;
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
	template<typename ActorType, typename GroupIndexType>
	GameEngineActor* CreateActor(GroupIndexType _ObjectGroupIndex)
	{
		return CreateActor<ActorType>(static_cast<int>(_ObjectGroupIndex));
	}

	template<typename ActorType>
	GameEngineActor* CreateActor(int _ObjectGroupIndex = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->ParentLevel = this;
		NewActor->Start();
		NewActor->SetLevel(this);

		std::list<GameEngineActor*>& Group = AllActors[_ObjectGroupIndex];

		Group.push_back(NewActor);

		return NewActor;
	}

private:
	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorUpdate(float _DelataTime);
	void LevelUpdate(float _DeltaTime);

private:
	std::map<int, std::list<class GameEngineRenderer*>> AllRenderer_;

	void PushRenderer(GameEngineRenderer* _Renderer);

	void Render(float _DelataTime);
};

