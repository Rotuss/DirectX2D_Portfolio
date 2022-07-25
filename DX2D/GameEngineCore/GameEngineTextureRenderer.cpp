#include "PreCompile.h"
#include "GameEngineTextureRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineFolderTexture.h"

GameEngineTextureRenderer::GameEngineTextureRenderer() 
	: CurTex(nullptr)
	, CurAni(nullptr)
{
}

GameEngineTextureRenderer::~GameEngineTextureRenderer() 
{
}

void GameEngineTextureRenderer::SetSamplingModePoint()
{
	ShaderResources.SetSampler("Smp", "EngineSamplerPoint");
}

void GameEngineTextureRenderer::SetSamplingModeLiner()
{
	ShaderResources.SetSampler("Smp", "EngineSamplerLinear");
}

void GameEngineTextureRenderer::SetTexture(GameEngineTexture* _Texture)
{
	CurTex = _Texture;
	ShaderResources.SetTexture("Tex", _Texture);
}

void GameEngineTextureRenderer::SetTexture(GameEngineTexture* _Texture, UINT _Index)
{
	if (nullptr == _Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
		return;
	}

	SetTexture(_Texture);
	SetFrame(_Index);
}

void GameEngineTextureRenderer::SetTexture(const std::string& _Name)
{
	CurTex = ShaderResources.SetTexture("Tex", _Name);
}

void GameEngineTextureRenderer::SetTexture(const std::string& _Name, UINT _Index)
{
	SetTexture(_Name);
	SetFrame(_Index);
}

void GameEngineTextureRenderer::SetFrame(UINT _Index)
{
	FrameData = CurTex->GetFrameData(_Index);
}

void GameEngineTextureRenderer::CreateFrameAnimationFolder(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() != FrameAni.find(Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	FrameAnimation& NewAni = FrameAni[Name];
	NewAni.Info = _Desc;
	NewAni.ParentRenderer = this;
	NewAni.Texture = nullptr;
	NewAni.FolderTexture = GameEngineFolderTexture::Find(_Desc.TextureName);

	if (NewAni.Info.Start == -1)
	{
		NewAni.Info.Start = 0;
	}

	if (NewAni.Info.End == -1)
	{
		NewAni.Info.End = static_cast<unsigned int>(NewAni.FolderTexture->GetTextureCount() - 1);
	}
}

void GameEngineTextureRenderer::CreateFrameAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() != FrameAni.find(Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	FrameAnimation& NewAni = FrameAni[Name];
	NewAni.Info = _Desc;
	NewAni.ParentRenderer = this;
	NewAni.Texture = GameEngineTexture::Find(_Desc.TextureName);
	NewAni.FolderTexture = nullptr;
}

void GameEngineTextureRenderer::ChangeFrameAnimation(const std::string& _AnimationName)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() == FrameAni.find(Name))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	if (CurAni != &FrameAni[Name])
	{
		CurAni = &FrameAni[Name];
		CurAni->Reset();
		
		if (nullptr != CurAni->Texture)
		{
			SetTexture(CurAni->Texture, CurAni->Info.CurFrame);
		}
		else if (nullptr != CurAni->FolderTexture)
		{
			SetTexture(CurAni->FolderTexture->GetTexture(CurAni->Info.CurFrame));
		}
	}
}

void GameEngineTextureRenderer::AnimationBindStart(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> Function)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() == FrameAni.find(Name))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	FrameAni[Name].Start = Function;
}

void GameEngineTextureRenderer::AnimationBindEnd(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> Function)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() == FrameAni.find(Name))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	FrameAni[Name].End = Function;
}

void GameEngineTextureRenderer::AnimationBindFrame(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> Function)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() == FrameAni.find(Name))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	FrameAni[Name].Frame = Function;
}

void GameEngineTextureRenderer::AnimationBindTime(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&, float)> Function)
{
	std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

	if (FrameAni.end() == FrameAni.find(Name))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	FrameAni[Name].Time = Function;
}

void GameEngineTextureRenderer::ScaleToTexture()
{
	GetTransform().SetLocalScale(CurTex->GetScale());
}

void GameEngineTextureRenderer::CurAnimationReset()
{
	CurAnimationSetStartPivotFrame(CurAni->Info.Start);
}

void GameEngineTextureRenderer::CurAnimationSetStartPivotFrame(int SetFrame)
{
	CurAni->Info.CurFrame += CurAni->Info.Start + SetFrame;
}

void GameEngineTextureRenderer::Start()
{
	GameEngineDefaultRenderer::Start();
	SetPipeLine("TextureAtlas");

	FrameData.PosX = 0.0f;
	FrameData.PosY = 0.0f;
	FrameData.SizeX = 1.0f;
	FrameData.SizeY = 1.0f;

	ShaderResources.SetConstantBufferLink("AtlasData", FrameData);
}

void GameEngineTextureRenderer::Update(float _Delta)
{
	if (nullptr != CurAni)
	{
		CurAni->Update(_Delta);
	}
}

void GameEngineTextureRenderer::FrameDataReset()
{
	FrameData = { 0.0f, 0.0f, 1.0f, 1.0f };
}

void FrameAnimation::Reset()
{
	Info.FrameTime = 0.0f;
	Info.CurFrame = Info.Start;
}

void FrameAnimation::Update(float _DeltaTime)
{
	Info.FrameTime += _DeltaTime;

	if (nullptr != Time)
	{
		Time(Info, _DeltaTime);
	}

	if (false == bOnceStart && Info.CurFrame == Info.Start && nullptr != Start)
	{
		Start(Info);
		bOnceStart = true;
		bOnceEnd = false;
	}

	if (Info.Inter <= Info.FrameTime)
	{
		++Info.CurFrame;
		if (nullptr != Frame)
		{
			Frame(Info);
		}

		if (Info.CurFrame > Info.End)
		{
			if (false == bOnceEnd && nullptr != End)
			{
				End(Info);
				bOnceEnd = true;
				bOnceStart = false;
			}

			if (true == Info.Loop)
			{
				Info.CurFrame = Info.Start;
			}
			else 
			{
				Info.CurFrame = Info.End;
			}
		}

		if (nullptr != Texture)
		{
			ParentRenderer->SetTexture(Texture, Info.CurFrame);
		}
		else if (nullptr != FolderTexture)
		{
			ParentRenderer->FrameDataReset();
			ParentRenderer->SetTexture(FolderTexture->GetTexture(Info.CurFrame));
		}
		else
		{
			MsgBoxAssert("텍스처가 세팅되지 않은 애니메이션입니다.");
		}

		Info.FrameTime -= Info.Inter;
	}
}
