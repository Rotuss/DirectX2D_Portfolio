#pragma once
#include <GameEngineCore/GameEngineCore.h>

// 설명 : 프로그램 자체를 시작
class Cuphead : public GameEngineCore
{
public:
	// constrcuter destructer
	Cuphead();
	~Cuphead();

	// delete Function
	Cuphead(const Cuphead& _Other) = delete;
	Cuphead(Cuphead&& _Other) noexcept = delete;
	Cuphead& operator=(const Cuphead& _Other) = delete;
	Cuphead& operator=(Cuphead&& _Other) noexcept = delete;

	std::string GetWindowTitle() override
	{
		return "Cuphead";
	}

protected:
	void UserStart() override;
	void UserUpdate() override;
	void UserEnd() override;

private:

};

