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
	DetachObject();
	
	Parent = _Parent;
	Parent->Childs.push_back(this);
}

void GameEngineUpdateObject::ReleaseHierarchy()
{
	std::list<GameEngineUpdateObject*>::iterator StartIter = Childs.begin();
	std::list<GameEngineUpdateObject*>::iterator EndIter = Childs.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->ReleaseHierarchy();
	}

	delete this;
}

void GameEngineUpdateObject::ReleaseObject(std::list<GameEngineUpdateObject*>& _RelaseList)
{
	if (true == IsDeath())
	{
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
			GameEngineUpdateObject* DeleteObject = (*StartIter);
			++StartIter;
			DeleteObject->DetachObject();
			continue;
		}

		(*StartIter)->ReleaseObject(_RelaseList);
		++StartIter;
	}
}

void GameEngineUpdateObject::DetachObject()
{
	if (nullptr != Parent)
	{
		Parent->Childs.remove(this);
	}
}
