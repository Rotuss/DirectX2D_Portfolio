#include "GameEngineSound.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

#pragma comment(lib, "fmod_vc.lib")

FMOD::System* SoundSystem_ = nullptr;

class SoundSystemCreater
{
public:
	SoundSystemCreater()
	{
		FMOD::System_Create(&SoundSystem_);

		if (nullptr == SoundSystem_)
		{
			MsgBoxAssert("사운드 시스템 생성에 실패했습니다.");
			return;
		}

		if (FMOD_OK != SoundSystem_->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운드 시스템 설정에 실패했습니다.");
			return;
		}

	}
};

SoundSystemCreater CreateInst = SoundSystemCreater();

GameEngineSound::GameEngineSound() 
{
}

GameEngineSound::~GameEngineSound() 
{
}

bool GameEngineSound::Load(const std::string& _Path)
{
	if (FMOD_OK != SoundSystem_->createSound(_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &Sound))
	{
		MsgBoxAssertString("사운드 로드에 실패했습니다.\n 경로 : " + _Path);
		return false;
	}

	return true;
}


//========================= 매니지먼트 사운드 기능 =========================
GameEngineSoundPlayer GameEngineSound::SoundPlayControl(const std::string& _Name, unsigned int _LoopCount)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	GameEngineSound* FindSound = FindRessource(UpperName);

	if (nullptr == FindSound)
	{
		MsgBoxAssertString("존재하지 않는 사운드를 재생하려고 했습니다.\n 이름 : " + UpperName);
		return GameEngineSoundPlayer();
	}

	FMOD::Channel* PlayControl = nullptr;

	SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);
	PlayControl->setLoopCount(_LoopCount);

	return GameEngineSoundPlayer(FindSound, PlayControl);
}

void GameEngineSound::SoundPlayOneShot(const std::string& _Name, int _LoopCount)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);
	GameEngineSound* FindSound = FindRessource(UpperName);

	if (nullptr == FindSound)
	{
		MsgBoxAssertString("존재하지 않는 사운드를 재생하려고 했습니다.\n 이름 : " + UpperName);
		return;
	}

	FMOD::Channel* PlayControl = nullptr;

	SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);
	PlayControl->setLoopCount(_LoopCount);
}

void GameEngineSound::Update()
{
	if (nullptr == SoundSystem_)
	{
		return;
	}

	SoundSystem_->update();
}


//========================= 리소스 매니지먼트 기능 =========================
std::map<std::string, GameEngineSound*> GameEngineSound::AllRes;

GameEngineSound* GameEngineSound::FindRessource(const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	std::map<std::string, GameEngineSound*>::iterator FindIter = AllRes.find(UpperName);

	if (FindIter == AllRes.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

GameEngineSound* GameEngineSound::LoadRessource(const GameEngineFile& _Path)
{
	return LoadRessource(_Path.GetFullPath());
}

GameEngineSound* GameEngineSound::LoadRessource(const std::string& _Path)
{
	GameEnginePath NewPath = GameEnginePath(_Path);
	return LoadRessource(_Path, NewPath.GetFileName());
}

GameEngineSound* GameEngineSound::LoadRessource(const std::string& _Path, const std::string& _Name)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name);

	GameEngineSound* NewRes = new GameEngineSound();

	if (false == NewRes->Load(_Path))
	{
		delete NewRes;
		NewRes = nullptr;

		return nullptr;
	}

	AllRes.insert(std::make_pair(UpperName, NewRes));
	return nullptr;
}

void GameEngineSound::AllResourcesDestroy()
{
	for (std::pair<std::string, GameEngineSound*> Res : AllRes)
	{
		delete Res.second;
		Res.second = nullptr;
	}

	AllRes.clear();

	if (nullptr != SoundSystem_)
	{
		SoundSystem_->release();
		SoundSystem_ = nullptr;
	}
}


//========================= 사운드 플레이어 =========================
void GameEngineSoundPlayer::Stop()
{
	if (nullptr == ControlHandle_)
	{
		return;
	}

	ControlHandle_->stop();
}

void GameEngineSoundPlayer::PlaySpeed(float _Speed)
{
	if (nullptr == ControlHandle_)
	{
		MsgBoxAssert("사운드 컨트롤 채널에 치명적인 문제가 있습니다.\n");
		return;
	}

	ControlHandle_->setPitch(_Speed);
}

void GameEngineSoundPlayer::Volume(float _Value)
{
	ControlHandle_->setVolume(_Value);
}

GameEngineSoundPlayer::GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other)
	: Sound_(_Other.Sound_)
	, ControlHandle_(_Other.ControlHandle_)
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSound* _Sound, FMOD::Channel* _ControlHandle)
	: Sound_(_Sound)
	, ControlHandle_(_ControlHandle)
{

}

GameEngineSoundPlayer::GameEngineSoundPlayer()
	: Sound_(nullptr)
	, ControlHandle_(nullptr)
{
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}
