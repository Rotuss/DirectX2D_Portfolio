#pragma once
#include <map>
#include <list>
#include <vector>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineNameObject.h>

// Ό³Έν :
class GameEngineMesh : public GameEngineNameObject
{
public:
	static void Create(const std::string& _Name, const std::vector<float4>& _Vertex);
	static void Create(const std::vector<float4>& _Vertex);

protected:

private:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	std::vector<float4> Vertex;
	static std::map<std::string, GameEngineMesh*> NamedRes;
	static std::list<GameEngineMesh*> UnNamedRes;
	static GameEngineMesh* CreateRes(const std::vector<float4>& _Vertex, const std::string& _Name = "");

};

