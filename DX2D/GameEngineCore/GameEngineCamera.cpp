#include "PreCompile.h"
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

	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = Size.x;
	ViewPortDesc.Height = Size.y;
	ViewPortDesc.MinDepth = 0.0f;
	ViewPortDesc.MaxDepth = 1.0f;
}

GameEngineCamera::~GameEngineCamera() 
{
}

float4 GameEngineCamera::GetScreenPosition()
{
	POINT P;
	GetCursorPos(&P);
	ScreenToClient(GameEngineWindow::GetHWND(), &P);

	return { static_cast<float>(P.x), static_cast<float>(P.y) };
}

float4 GameEngineCamera::GetMouseWorldPosition()
{
	float4 Pos = GetScreenPosition();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.x, Size.y, 0, 0, 0, 1);
	ViewPort.Inverse();

	float4x4 ProjectionInvers = Projection.InverseReturn();
	float4x4 ViewInvers = View.InverseReturn();

	Pos = Pos * ViewPort;
	Pos = Pos * ProjectionInvers;
	Pos = Pos * ViewInvers;

	return Pos;
}

float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

void GameEngineCamera::Start()
{
	GetActor()->GetLevel()->PushCamera(this);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortDesc);
	
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

	for (const std::pair<int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineRenderer* const Renderer : Group.second)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}
			
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

void GameEngineCamera::Release(float _DelataTime)
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
		std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
		std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseUpdate(_DelataTime);
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

void GameEngineCamera::Update(float _DeltaTime)
{
	float4 MousePos = GetMouseWorldPosition();
	MousePos.w = 0.0f;
	MouseDir = MousePos - PrevMouse;
	PrevMouse = MousePos;
}

