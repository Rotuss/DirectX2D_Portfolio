#pragma once
#include <map>

// Ό³Έν :
class GameEngineTime
{
private:
	static GameEngineTime* Inst_;

public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}


public:
	void Reset();
	void Update();

	static inline float GetDeltaTime() {}
	static inline float GetDeltaTime(int _Key) {}
	
	void SetTimeScale(int _Key, float _TimeScale)
	{
		TimeScale_[_Key] = _TimeScale;
	}

	float GetTimeScale(int _Key)
	{
		if (TimeScale_.end() == TimeScale_.find(_Key))
		{
			TimeScale_[_Key] = 1.0f;
		}

		return TimeScale_[_Key];
	}

protected:

private:
	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	std::map<int, float> TimeScale_;
};

