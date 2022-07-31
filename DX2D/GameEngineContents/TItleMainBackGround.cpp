#include "PreCompile.h"
#include "TItleMainBackGround.h"

TItleMainBackGround::TItleMainBackGround() 
{
}

TItleMainBackGround::~TItleMainBackGround() 
{
}

void TItleMainBackGround::Start()
{
}

void TItleMainBackGround::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}
}

