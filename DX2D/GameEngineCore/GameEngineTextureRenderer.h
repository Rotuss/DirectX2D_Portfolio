#pragma once
#include "GameEngineDefaultRenderer.h"

enum class PIVOTMODE
{
	CENTER,
	LEFTTOP,
	BOT,
	CUSTOM,
};

enum class SCALEMODE
{
	IMAGE,
	CUSTOM,
};

struct ColorData
{
	float4 MulColor;
	float4 PlusColor;

	ColorData()
		: MulColor(float4::WHITE)
		, PlusColor(float4::ZERO)
	{

	}
};

class FrameAnimation_DESC
{
public:
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

	bool bOnceStart;
	bool bOnceEnd;

	std::function<void(const FrameAnimation_DESC&)> Frame;
	std::function<void(const FrameAnimation_DESC&)> End;
	std::function<void(const FrameAnimation_DESC&)> Start;
	std::function<void(const FrameAnimation_DESC&, float)> Time;

	void Reset();
	void Update(float _DeltaTime);

public:
	FrameAnimation()
		: bOnceStart(true)
		, bOnceEnd(false)
	{
	}
};

// ���� :
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

	ColorData& GetColorData()
	{
		return ColorData;
	}

	void SetSamplingModePoint();
	void SetSamplingModeLiner();

	void SetTexture(GameEngineTexture* _Texture);
	void SetTexture(GameEngineTexture* _Texture, UINT _Index);
	void SetTexture(const std::string& _Name);
	void SetTexture(const std::string& _Name, UINT _Index);
	void SetFrame(UINT _Index);

	void SetPivot();
	void SetPivot(PIVOTMODE _Mode);
	void SetPivotToVector(const float4& _Value);

	void CreateFrameAnimationFolder(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);

	void CreateFrameAnimationCutTexture(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeFrameAnimation(const std::string& _AnimationName);

	// ���� ������
	void AnimationBindStart(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü�����Ϸ��� �߽��ϴ�.");
			return;
		}

		FrameAni[Name].Start = _Function;
	}
	// �� ������
	void AnimationBindEnd(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü�����Ϸ��� �߽��ϴ�.");
			return;
		}

		FrameAni[Name].End = _Function;
	}
	// ü���� ������
	void AnimationBindFrame(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> _Function)
	{
		std::string Name = GameEngineString::ToUpperReturn(_AnimationName);

		if (FrameAni.end() == FrameAni.find(Name))
		{
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü�����Ϸ��� �߽��ϴ�.");
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
			MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü�����Ϸ��� �߽��ϴ�.");
			return;
		}

		FrameAni[Name].Time = _Function;
	}

	void ScaleToTexture();
	void ScaleToCutTexture(int _Index);
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
	float4				FrameData;

	std::map<std::string, FrameAnimation> FrameAni;
	FrameAnimation* CurAni;

	ColorData ColorData;

	void FrameDataReset();
};

