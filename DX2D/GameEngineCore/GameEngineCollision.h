#pragma once
#include <GameEngineBase/GameEngineTransform.h>
#include "GameEngineTransformComponent.h"

enum class CollisionMode
{
	Normal,
	Ex,
};

enum class CollisionReturn
{
	ContinueCheck,
	Break,
};

// Ό³Έν :
class GameEngineCollisionFunctionInit;
class GameEngineCollision : public GameEngineTransformComponent
{
	friend GameEngineCollisionFunctionInit;

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	template<typename EnumType>
	void ChangeOrder(EnumType _Order)
	{
		ChangeOrder(static_cast<int>(_Order));
	}

	void ChangeOrder(int _Order);

	template<typename EnumType>
	bool IsCollision(CollisionType _ThisType, EnumType _GroupOrder, CollisionType _OtherCollision, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Function = nullptr)
	{
		return IsCollision(_ThisType, static_cast<int>(_GroupOrder), _OtherCollision, _Function);
	}

	bool IsCollision(CollisionType _ThisType, int _GroupOrder, CollisionType _OtherType
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Update = nullptr
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Enter = nullptr
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Exit = nullptr);

	bool IsCollisionEnterBase(CollisionType _ThisType, int _GroupOrder
		, CollisionType _OtherType
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Enter = nullptr
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Update = nullptr
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Exit = nullptr
	)
	{
		return IsCollision(_ThisType, _GroupOrder, _OtherType, _Update, _Enter, _Exit);
	}

	bool IsCollisionExitBase(CollisionType _ThisType, int _GroupOrder
		, CollisionType _OtherType
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Enter = nullptr
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Update = nullptr
		, std::function<CollisionReturn(GameEngineCollision* _This, GameEngineCollision* _Other)> _Exit = nullptr
	)
	{
		return IsCollision(_ThisType, _GroupOrder, _OtherType, _Update, _Enter, _Exit);
	}

	void SetDebugSetting(CollisionType _DebugType, float4 _Color)
	{
		DebugType = _DebugType;
		Color = _Color;
	}

	void SetDebugCamera(CAMERAORDER _Order)
	{
		DebugCameraOrder = _Order;
	}

	void OffEvent() override
	{
		ResetExData();
	}

	void SetCollisionMode(CollisionMode _Mode)
	{
		E_CollisionMode = _Mode;
	}

	void ResetExData()
	{
		CollisionCheck.clear();
	}

	void SetUIDebugCamera();

	virtual void DebugRender();

protected:

private:
	static bool (*CollisionFunction[static_cast<int>(CollisionType::CT_MAX)][static_cast<int>(CollisionType::CT_MAX)])(const GameEngineTransform& _Left, const GameEngineTransform& _Right);

	void Start() override;

	CAMERAORDER		DebugCameraOrder;
	CollisionType	DebugType;
	CollisionMode	E_CollisionMode;
	float4			Color;

	std::set<GameEngineCollision*> CollisionCheck;
};

