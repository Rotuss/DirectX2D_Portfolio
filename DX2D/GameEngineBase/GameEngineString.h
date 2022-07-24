#pragma once
#include <string>
#include <algorithm>

// Ό³Έν :
class GameEngineString
{
public:
	static void ToUpper(std::string& _Text)
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = static_cast<char>(std::toupper(_Text[i]));
		}
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;

		for (size_t i = 0; i < _Text.size(); i++)
		{
			NewText[i] = static_cast<char>(std::toupper(NewText[i]));
		}

		return NewText;
	}

	static void AnsiToUnicode(const std::string& _Text, std::wstring& _Out);
	static std::wstring AnsiToUnicodeReturn(const std::string& Text);
	static void UniCodeToUTF8(const std::wstring& _Text, std::string& _Out);
	static void AnsiToUTF8(const std::string& _Text, std::string& _Out);
	static std::string AnsiToUTF8Return(const std::string& _Text);
	static std::wstring StringToWStringReturn(const std::string& _Text);

protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};

