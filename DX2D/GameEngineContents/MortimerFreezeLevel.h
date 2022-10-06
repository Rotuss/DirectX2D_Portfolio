#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MortimerFreezeLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MortimerFreezeLevel();
	~MortimerFreezeLevel();

	// delete Function
	MortimerFreezeLevel(const MortimerFreezeLevel& _Other) = delete;
	MortimerFreezeLevel(MortimerFreezeLevel&& _Other) noexcept = delete;
	MortimerFreezeLevel& operator=(const MortimerFreezeLevel& _Other) = delete;
	MortimerFreezeLevel& operator=(MortimerFreezeLevel&& _Other) noexcept = delete;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

	inline void SetPh3MovePos(GameEngineTransform* _Transform, float4 _StartValue, float4 _GoalValue)
	{
		MoveVec.push_back(_Transform);
		StartPosVec.push_back(_StartValue);
		GoalPosVec.push_back(_GoalValue);
	}

	inline void SetPh3MoveValue(GameEngineTransform* _Transform, float4 _AddValue)
	{
		MoveVec.push_back(_Transform);
		StartPosVec.push_back(_Transform->GetWorldPosition());
		GoalPosVec.push_back(_Transform->GetWorldPosition() + _AddValue);
	}

	inline float GetMoveTImer()
	{
		return MoveTimer;
	}

	inline bool GetIsMove()
	{
		return IsMove;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void Ph3MoveCheck();
	void Ph3MoveCheckUpdate(float _DeltaTime);

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* PPtr;
	GameEngineSound StartSound;
	std::vector<GameEngineTransform*> MoveVec;
	std::vector<float4> StartPosVec;
	std::vector<float4> GoalPosVec;

	float MoveTimer;
	int SoundNum;
	bool IsMove;
};

