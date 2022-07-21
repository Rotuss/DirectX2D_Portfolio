#pragma once
#include <list>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include "GameEngineTransformBase.h"

// 설명 : 화면에 등장하는 모든것을 표현하기 위한 클래스
class GameEngineComponent;
class GameEngineTransformComponent;
class GameEngineActor :
	public GameEngineNameObject,
	public GameEngineUpdateObject,
	public GameEngineTransformBase
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor() = 0;

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel() 
	{ 
		return ParentLevel;
	}

	template<typename ComponentType>
	ComponentType* CreateComponent()
	{
		GameEngineComponent* NewComponent = new ComponentType();
		NewComponent->SetParent(this);
		NewComponent->Start();
		
		GameEngineTransformComponent* TransCom = dynamic_cast<GameEngineTransformComponent*>(NewComponent);
		if (nullptr == TransCom)
		{
			AllComList.push_back(NewComponent);
		}
		else
		{
			SettingTransformComponent(TransCom);
			AllTransComList.push_back(TransCom);
		}

		return dynamic_cast<ComponentType*>(NewComponent);
	}

	void SettingTransformComponent(GameEngineTransformComponent* TransCom);
	void ComponentCalculateTransform();

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	void ComponentUpdate(float _ScaleDeltaTime, float _DeltaTime);

	std::list<class GameEngineComponent*> AllComList;
	std::list<class GameEngineTransformComponent*> AllTransComList;

	class GameEngineLevel* ParentLevel;

	void SetLevel(GameEngineLevel* _ParentLevel)
	{
		ParentLevel = _ParentLevel;
	}

};

