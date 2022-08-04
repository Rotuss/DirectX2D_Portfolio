#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

#include "../GameEngineCore/ThirdParty/inc/FW1FontWrapper.h"

#pragma comment(lib, "FW1FontWrapper.lib")

// Ό³Έν :
class GameEngineFont : public GameEngineRes<GameEngineFont>
{
public:
	// constrcuter destructer
	GameEngineFont();
	~GameEngineFont();

	// delete Function
	GameEngineFont(const GameEngineFont& _Other) = delete;
	GameEngineFont(GameEngineFont&& _Other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _Other) = delete;
	GameEngineFont& operator=(GameEngineFont&& _Other) noexcept = delete;

	static IFW1Factory* FontFactory;

	static GameEngineFont* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineFont* Load(const std::string& _Path, const std::string& _Name);

	void FontDraw(const std::string& _Text, float _FontSize, float4 _ScreenPos, float4 Color, UINT Flag = FW1_LEFT);

protected:

private:
	void LoadFont(const std::string& _Path);
	
	IFW1FontWrapper* FontWrapper;
};

