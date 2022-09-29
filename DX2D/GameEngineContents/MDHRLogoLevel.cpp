#include "PreCompile.h"
#include "MDHRLogoLevel.h"
#include "ScreenFX.h"
#include "TitleLogo.h"
#include "GlobalContents.h"

MDHRLogoLevel::MDHRLogoLevel() 
{
}

MDHRLogoLevel::~MDHRLogoLevel() 
{
}

void MDHRLogoLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameaOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameaOnOff", 'O');
	}

	{
		ScreenFX* SFX = CreateActor<ScreenFX>(OBJECTORDER::UI);
		//SFX->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		SFX->SetLevelOverOn();
	}

	{
		TitleLogo* Logo = CreateActor<TitleLogo>(OBJECTORDER::Title);
	}
}

void MDHRLogoLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void MDHRLogoLevel::End()
{
}
