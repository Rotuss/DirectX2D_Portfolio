#pragma once
#include "GameEngineDefaultRenderer.h"

class FrameAnimation_DESC
{
public:
	std::string TextureName;

	unsigned int CurFrame;
	unsigned int Start;
	unsigned int End;

	float FrameTime;
	float Inter;

	bool Loop;

public:
	FrameAnimation_DESC()
		: Loop(false)
		, Inter(0.1f)
		, CurFrame(-1)
		, Start(-1)
		, End(-1)
	{
	}

	FrameAnimation_DESC(const std::string _TextureName, unsigned int _Start, unsigned int _End, float _Inter, bool _Loop = true)
		: TextureName(_TextureName)
		, Loop(_Loop)
		, Inter(_Inter)
		, CurFrame(_Start)
		, Start(_Start)
		, End(_End)
	{
	}

	FrameAnimation_DESC(const std::string _TextureName, float _Inter, bool _Loop = true)
		: TextureName(_TextureName)
		, Loop(_Loop)
		, Inter(_Inter)
		, CurFrame(0)
		, Start(-1)
		, End(-1)
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

	void SetTexture(GameEngineTexture* _Texture);
	void SetTexture(GameEngineTexture* _Texture, UINT _Index);
	void SetTexture(const std::string& _Name);
	void SetTexture(const std::string& _Name, UINT _Index);
	void SetFrame(UINT _Index);

	void CreateFrameAnimationFolder(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);

	void CreateFrameAnimation(const std::string& _AnimationName, const FrameAnimation_DESC& _Desc);
	void ChangeFrameAnimation(const std::string& _AnimationName);

	// 시작 프레임
	void AnimationBindStart(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> Function);
	// 끝 프레임
	void AnimationBindEnd(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> Function);
	// 체인지 프레임
	void AnimationBindFrame(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&)> Function);
	// Update
	void AnimationBindTime(const std::string& _AnimationName, std::function<void(const FrameAnimation_DESC&, float)> Function);

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	GameEngineTexture* CurTex;
	float4 FrameData;

	std::map<std::string, FrameAnimation> FrameAni;
	FrameAnimation* CurAni;

	void FrameDataReset();
};

