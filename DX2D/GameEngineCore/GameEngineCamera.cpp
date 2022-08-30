#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineRenderTarget.h"
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

bool ZSort(GameEngineRenderer* _Left, GameEngineRenderer* _Right)
{
	return _Left->GetTransform().GetWorldPosition().z > _Right->GetTransform().GetWorldPosition().z;
}

void GameEngineCamera::SetCameraOrder(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushCamera(this, _Order);
}

float4 GameEngineCamera::GetMouseScreenPosition()
{
	POINT P;
	GetCursorPos(&P);
	ScreenToClient(GameEngineWindow::GetHWND(), &P);

	return { static_cast<float>(P.x), static_cast<float>(P.y) };
}

float4 GameEngineCamera::GetMouseWorldPosition()
{
	float4 Pos = GetMouseScreenPosition();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.x, Size.y, 0, 0, 0, 1);
	ViewPort.Inverse();

	float4x4 ProjectionInvers = Projection.InverseReturn();
	//float4x4 ViewInvers = View.InverseReturn();

	Pos = Pos * ViewPort;
	Pos = Pos * ProjectionInvers;
	//Pos = Pos * ViewInvers;

	return Pos;
}

float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

void GameEngineCamera::Start()
{
	CameraRenderTarget = GameEngineRenderTarget::Create();
	CameraRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);
	CameraRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
}

void GameEngineCamera::ChangeRenderingOrder(GameEngineRenderer* _Renderer, int _ChangeOrder)
{
	AllRenderer_[_Renderer->GetRenderingOrder()].remove(_Renderer);

	_Renderer->RenderingOrder = _ChangeOrder;

	AllRenderer_[_Renderer->GetRenderingOrder()].push_back(_Renderer);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	CameraRenderTarget->Clear();
	CameraRenderTarget->Setting();
	
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

	for (std::pair<const int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		
		std::list<GameEngineRenderer*>& RenderList = Group.second;
		RenderList.sort(ZSort);

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

void GameEngineCamera::OverRenderer(GameEngineCamera* _NextOver)
{
	if (nullptr == _NextOver)
	{
		MsgBoxAssert("Next Camera is nullptr.");
		return;
	}

	std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
		std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
		std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			GameEngineActor* Root = (*GroupStart)->GetRoot<GameEngineActor>();

			if (true == Root->IsLevelOver)
			{
				_NextOver->AllRenderer_[StartGroupIter->first].push_back(*GroupStart);
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}
		}
	}
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->RenderingOrder].push_back(_Renderer);
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

