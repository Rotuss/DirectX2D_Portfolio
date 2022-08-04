#include "PreCompile.h"
#include "GameEngineFont.h"

IFW1Factory* GameEngineFont::FontFactory = nullptr;

class GameEngineFontInit
{
public:
	GameEngineFontInit()
	{
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::FontFactory);
	}

	~GameEngineFontInit()
	{
		if (nullptr != GameEngineFont::FontFactory)
		{
			GameEngineFont::FontFactory->Release();
		}
	}

protected:

private:

};

GameEngineFontInit Inst;

GameEngineFont::GameEngineFont() 
	: FontWrapper(nullptr)
{
}

GameEngineFont::~GameEngineFont() 
{
	if (nullptr != FontWrapper)
	{
		FontWrapper->Release();
		FontWrapper = nullptr;
	}
}

GameEngineFont* GameEngineFont::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineFont* NewRes = CreateResName(_Name);
	NewRes->LoadFont(_Path);
	return NewRes;
}

void GameEngineFont::FontDraw(const std::string& _Text, float _FontSize, float4 _ScreenPos, float4 Color, UINT Flag)
{
	std::wstring Text = GameEngineString::AnsiToUnicodeReturn(_Text);
	FontWrapper->DrawString(GameEngineDevice::GetContext(), Text.c_str(), _FontSize, _ScreenPos.x, _ScreenPos.y, Color.GetUIntColor(), Flag);
}

void GameEngineFont::LoadFont(const std::string& _Path)
{
	std::wstring WPath = GameEngineString::AnsiToUnicodeReturn(_Path);

	if (S_OK != FontFactory->CreateFontWrapper(GameEngineDevice::GetDevice(), WPath.c_str(), &FontWrapper))
	{
		MsgBoxAssert("폰트 생성에 실패했습니다.");
		return;
	}
}
