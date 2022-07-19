#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

// Ό³Έν :
class GameEngineIndexBuffer : public GameEngineRes<GameEngineIndexBuffer>
{
public:
	friend GameEngineRes<GameEngineIndexBuffer>;

public:
	static void Create(const std::string& _Name, const std::vector<int>& _Indexs);
	static void Create(const std::vector<int>& _Indexs);

	std::vector<int> Indexs;

protected:

private:
	// constrcuter destructer
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	// delete Function
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _Other) noexcept = delete;

	static GameEngineIndexBuffer* CreateRes(const std::vector<int>& _Indexs, const std::string& _Name = "");
};

