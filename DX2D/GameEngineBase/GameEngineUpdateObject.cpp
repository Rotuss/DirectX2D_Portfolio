#include "PreCompile.h"
#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: Order_(0)
	, DeathTime_(0.0f)
	, AccTime_(0.0f)
	, IsUpdate_(true)
	, IsDeath_(false)
	, IsReleaseUpdate_(false)
	, Parent(nullptr)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}

void GameEngineUpdateObject::SetParent(GameEngineUpdateObject* _Parent)
{
	RemoveToParentChildList();
	
	Parent = _Parent;
	Parent->Childs.push_back(this);
}

void GameEngineUpdateObject::DeleteChild()
{
	std::list<GameEngineUpdateObject*>::iterator StartIter = Childs.begin();
	std::list<GameEngineUpdateObject*>::iterator EndIter = Childs.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->DeleteChild();
	}

	delete this;
}

void GameEngineUpdateObject::ReleaseObject(std::list<GameEngineUpdateObject*>& _RelaseList)
{
	if (true == IsDeath())
	{
		RemoveToParentChildList();
		DetachObject();
		_RelaseList.push_back(this);
		return;
	}

	std::list<GameEngineUpdateObject*>::iterator StartIter = Childs.begin();
	std::list<GameEngineUpdateObject*>::iterator EndIter = Childs.end();

	for (; StartIter != EndIter;)
	{
		if (true == (*StartIter)->IsDeath())
		{
			_RelaseList.push_back((*StartIter));
			(*StartIter)->DetachObject();
			StartIter = Childs.erase(StartIter);
			continue;
		}

		(*StartIter)->ReleaseObject(_RelaseList);
		++StartIter;
	}
}

void GameEngineUpdateObject::RemoveToParentChildList()
{
	if (nullptr != Parent)
	{
		Parent->Childs.remove(this);
	}
}
