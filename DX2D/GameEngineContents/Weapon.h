#pragma once

// Ό³Έν :
class Weapon : public GameEngineActor
{
public:
	// constrcuter destructer
	Weapon();
	~Weapon();

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	void Attacked();

	inline void SetStartPos(float4 _Pos)
	{
		StartPos = _Pos;
	}
	void SetWeaponDir(const std::string& _Dir)
	{
		WeaponDir = _Dir;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	GameEngineTextureRenderer*	StartRenderer;
	GameEngineTextureRenderer*	Renderer;
	GameEngineCollision*		Collision;

	std::string					WeaponDir;
	float4						StartPos;
};

