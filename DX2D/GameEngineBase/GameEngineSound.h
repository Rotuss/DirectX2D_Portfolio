#pragma once
#include <map>
#include "ThirdParty/inc/fmod.hpp"
#include "GameEngineNameObject.h"
#include "GameEngineFile.h"

// 설명 :
class GameEngineSoundPlayer;
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);

private:
	FMOD::Sound* Sound;

//========================= 매니지먼트 사운드 기능 =========================
public:
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name, unsigned int _LoopCount = 0);

	static void SoundPlayOneShot(const std::string& _Name, int _LoopCount = 0);
	static void Update();

//========================= 리소스 매니지먼트 기능 =========================
public:
	static GameEngineSound* FindRessource(const std::string& _Name);
	static GameEngineSound* LoadRessource(const GameEngineFile& _Path);
	static GameEngineSound* LoadRessource(const std::string& _Path);
	static GameEngineSound* LoadRessource(const std::string& _Path, const std::string& _Name);

	static void ResourcesDestroy();

private:
	static std::map<std::string, GameEngineSound*> AllRes;
};

class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;

public:
	void Stop();
	void PlaySpeed(float _Speed);
	void Volume(float _Value);

	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);

private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;

	GameEngineSoundPlayer(GameEngineSound* Sound, FMOD::Channel* ControlHandle);

public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();
};