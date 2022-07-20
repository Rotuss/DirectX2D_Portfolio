#include "GameEngineCamera.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"

GameEngineCamera::GameEngineCamera() 
{
}

GameEngineCamera::~GameEngineCamera() 
{
}

void GameEngineCamera::Start()
{
	GetActor()->GetLevel()->PushCamera(this);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	View.View(GetActor()->GetTransform().GetLocalPosition(), GetActor()->GetTransform().GetForwardVector(), GetActor()->GetTransform().GetUpVector());

	for (const std::pair<int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineRenderer* const Renderer : Group.second)
		{
			Renderer->GetTransform().SetView(View);
			Renderer->GetTransform().SetProjection(Projection);
			Renderer->GetTransform().CalculateWorldViewProjection();
			Renderer->Render(ScaleTime);
		}
	}
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

