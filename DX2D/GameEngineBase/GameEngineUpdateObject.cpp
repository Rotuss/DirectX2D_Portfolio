#include "GameEngineUpdateObject.h"

GameEngineUpdateObject::GameEngineUpdateObject() 
	: Order_(0)
	, DeathTime_(0.0f)
	, AccTime_(0.0f)
	, IsUpdate_(true)
	, IsDeath_(false)
	, IsReleaseUpdate_(false)
{
}

GameEngineUpdateObject::~GameEngineUpdateObject() 
{
}

