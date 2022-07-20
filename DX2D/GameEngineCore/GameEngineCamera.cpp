#include "GameEngineCamera.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineCamera::GameEngineCamera() 
{
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::PersPective;
	Near = 0.1f;
	Far = 1000.0f;
	Fov = 60.0f;
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
	View.LookAtLH(GetActor()->GetTransform().GetLocalPosition(), GetActor()->GetTransform().GetForwardVector(), GetActor()->GetTransform().GetUpVector());

	switch (Mode)
	{
	case CAMERAPROJECTIONMODE::PersPective:
		Projection.PerspectiveFovLH(Fov, Size.x, Size.y, Near, Far);
		break;
	case CAMERAPROJECTIONMODE::Orthographic:
		Projection.OrthographicLH(Size.x, Size.y, Near, Far);
		break;
	default:
		break;
	}

	float4 WindowSize = GameEngineWindow::GetInst()->GetScale();

	ViewPort.ViewPort(WindowSize.x, WindowSize.y, 0.0f, 0.0f, 0.0f, 0.0f);

	for (const std::pair<int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineRenderer* const Renderer : Group.second)
		{
			Renderer->GetTransform().SetView(View);
			Renderer->GetTransform().SetProjection(Projection);
			Renderer->GetTransform().CalculateWorldViewProjection();
			Renderer->ViewPort = ViewPort;
			Renderer->Render(ScaleTime);
		}
	}
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}

