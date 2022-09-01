#pragma once
#include "GameEngineDefaultRenderer.h"

enum class PIVOTMODE
{
	CENTER,
	TOP,
	BOT,
	LEFT,
	RIGHT,
	LEFTTOP,
	RIGHTTOP,
	LEFTBOT,
	RIGHTBOT,
	CUSTOM,
};

enum class SCALEMODE
{
	IMAGE,
	CUSTOM,
};

struct PixelData
{
	float4 MulColor;
	float4 PlusColor;
	float4 Slice;

	PixelData()
		: MulColor(float4::WHITE)
		, PlusColor(float4::ZERO)
		, Slice(float4::ZERO)
	{

	}
};

struct AtlasData
{
public:
	float4 FrameData;
	float4 PivotPos;
};

class FrameAnimation_DESC
{
public:
	class GameEngineTextureRenderer* Renderer;
	
	std::string TextureName;
	std::vector<unsigned int> Frames;

	unsigned int CurFrame;
	
	float FrameTime;
	float Inter;

	bool Loop;

public:
	FrameAnimation_DESC()
		: CurFrame(-1)
		, FrameTime(0.0f)
		, Inter(0.1f)
		, Loop(false)
	{
	}

	FrameAnimation_DESC(const std::string _TextureName, unsigned int _Start, unsigned int _End, float _Inter, bool _Loop = true)
		: TextureName(_TextureName)
		, CurFrame(0)
		, FrameTime(0.0f)
		, Inter(_Inter)
		, Loop(_Loop)
	{
		for (unsigned int i = _Start; i <= _End; i++)
		{
			Frames.push_back(i);
		}
	}

	FrameAnimation_DESC(const std::string _TextureName, const std::vector<unsigned int>& _Frames, float _Inter, bool _Loop = true)
		: TextureName(_TextureName)
		, Frames(_Frames)
		, FrameTime(0.0f)
		, Inter(_Inter)
		, Loop(_Loop)
	{
	}

	FrameAnimation_DESC(const std::string _TextureName, float _Inter, bool _Loop = true)
		: TextureName(_TextureName)
		, CurFrame(0)
		, FrameTime(0.0f)
		, Inter(_Inter)
		, Loop(_Loop)
	{
	}
};

class GameEngineFolderTexture;
class GameEngineTextureRenderer;
class FrameAnimation : public GameEngineNameObject
{
	friend GameEngineTextureRenderer;

	FrameAnimation_DESC Info;

	GameEngineTextureRenderer* ParentRenderer;
	GameEngineTexture* Texture;
	GameEngineFolderTexture* FolderTexture;

	bool Pause;
	bool bOnceStart;
	bool bOnceEnd;

	std::function<void(const FrameAnimation_DESC&)> Frame;
	std::function<void(const FrameAnimation_DESC&)> End;
	std::function<void(const FrameAnimation_DESC&)> Start;
	std::function<void(const FrameAnimation_DESC&, float)> Time;

	void PauseSwtich();
	void Reset();
	void Update(float _DeltaTime);

public:
	FrameAnimation()
		: Pause(false)
		, bOnceStart(false)
		, bOnceEnd(false)
	{
	}
};

// 설명 :
class GameEngineTextureRenderer : public GameEngineDefaultRenderer
{
	friend FrameAnimation;

public:
	// constrcuter destructer
	GameEngineTextureRenderer();
	~GameEngineTextureRenderer();

	// delete Function
	GameEngineTextureRenderer(const GameEngineTextureRenderer& _Other) = delete;
	GameEngineTextureRenderer(GameEngineTextureRenderer&& _Other) noexcept = delete;
	GameEngineTextureRenderer& operator=(const GameEngineTextureRenderer& _Other) = delete;
	GameEngineTextureRenderer& operator=(GameEngineTextureRenderer&& _Other) noexcept = delete;

	GameEngineTexture* GetCurTexture();

	void SetScaleModeImage()
	{
		ScaleMode = SCALEMODE::IMAGE;
	}

	void SetScaleRatio(float _Scale)
	{
		ScaleRatio = _Scale;
	}

	float GetScaleRatio()
	{
		return ScaleRatio;
	}

	PixelData& GetPixelData()
	{
		return PixelDataInst;
	}

	bool IsCurAnimation()
	{
		if (nullptr == CurAni)
		{
			return false;
		}

		return true;
	}

	void SetSamplingModePoint();
	void SetSamplingModeLiner();

	void SetTexture(GameEngineTexture* _Texture);
	void SetTexture(GameEngineTexture* _Texture, UINT _Index);
	void SetTexture(const std::string& _Name);
	void SetTexture(const std::string& _Name, UINT _Index);
	void SetFrame(UINT _Index);
	void SetFolderTextureToIndex(const std::string& _Text, UINT _Index);

	void SetPivot();
	void SetPivot(PIVOTMODE _Mode);
	void SetPivotToVector(const float4& _Value);

	void CreateFrameAnimationFolder(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);

	void CreateFrameAnimationCutTexture(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeFrameAnimation(const std::string& _AnimationName);

	// 시작 프레임
	void AnimationBindStart(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
			return;
		}

		FrameAni[Name].Start = _Function;
	}
	// 끝 프레임
	void AnimationBindEnd(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
			return;
		}

		FrameAni[Name].End = _Function;
	}
	// 체인지 프레임
	void AnimationBindFrame(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
			return;
		}

		FrameAni[Name].Frame = _Function;
	}
	// Update
	void AnimationBindTime(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&, float)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
			return;
		}

		FrameAni[Name].Time = _Function;
	}

	void ScaleToTexture();
	void ScaleToCutTexture(int _Index);
	
	bool IsCurAnimationPause();
	void CurAnimationPauseOn();
	void CurAnimationPauseOff();
	void CurAnimationPauseSwitch();
	void CurAnimationReset();
	void CurAnimationSetStartPivotFrame(int SetFrame);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void SetTextureRendererSetting();

private:
	PIVOTMODE	PivotMode;
	SCALEMODE	ScaleMode;
	float		ScaleRatio;

	GameEngineTexture*	CurTex;

	std::map<std::string, FrameAnimation> FrameAni;
	FrameAnimation* CurAni;

	PixelData PixelDataInst;
	AtlasData AtlasDataInst;

	void FrameDataReset();
};

