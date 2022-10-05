#pragma once
#include <GameEngineCore/CoreMinimal.h>

enum class OWCupheadDir
{
	Left,
	LeftUp,
	LeftDown,
	Right,
	RightUp,
	RightDown,
	Up,
	Down,
};

// Ό³Έν :
class OverWorldCuphead : public GameEngineActor
{
public:
	// constrcuter destructer
	OverWorldCuphead();
	~OverWorldCuphead();

	// delete Function
	OverWorldCuphead(const OverWorldCuphead& _Other) = delete;
	OverWorldCuphead(OverWorldCuphead&& _Other) noexcept = delete;
	OverWorldCuphead& operator=(const OverWorldCuphead& _Other) = delete;
	OverWorldCuphead& operator=(OverWorldCuphead&& _Other) noexcept = delete;

	static OverWorldCuphead* OWCuphead;

	void SetColMap(GameEngineTextureRenderer* _Collision)
	{
		ColRenderer = _Collision;
	}

	GameEngineTextureRenderer* GetColMap()
	{
		return ColRenderer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	
	GameEngineTextureRenderer*	Renderer;
	GameEngineTextureRenderer*	ColRenderer;
	GameEngineTexture*			ColorCheck;
	GameEngineCollision*		Collision;

	void IdleStart(const StateInfo& _Info);
	void IdleUpdate(float _DeltaTime, const StateInfo& _Info);

	void WalkStart(const StateInfo& _Info);
	void WalkUpdate(float _DeltaTime, const StateInfo& _Info);

private:
	GameEngineStateManager	StateManager;
	std::string				CurStateName;
	std::string				CurUpDownName;
	OWCupheadDir			CurDir;
	
	float					Speed;
};

