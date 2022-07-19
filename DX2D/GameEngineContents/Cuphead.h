#pragma once
#include <GameEngineCore/GameEngineCore.h>

// ���� : ���α׷� ��ü�� ����
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

