#include "PreCompile.h"
#include "MortimerFreezeBlade.h"

MortimerFreezeBlade::MortimerFreezeBlade() 
{
}

MortimerFreezeBlade::~MortimerFreezeBlade() 
{
}

void MortimerFreezeBlade::Start()
{
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 30, 300, 1 });
	}
}

void MortimerFreezeBlade::Update(float _DeltaTime)
{
}

