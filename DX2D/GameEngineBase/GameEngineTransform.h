#pragma once
#include <list>
#include <DirectXCollision.h>
#include <GameEngineBase/GameEngineDebugObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include "GameEngineMath.h"

enum CollisionType
{
	CT_POINT,
	CT_SPHERE,	// 정방원
	CT_AABB,	// 회전하지 않은 박스
	CT_OBB,		// 회전한 박스
};

class CollisionData
{
	friend class GameEngineTransform;

	union
	{
		DirectX::BoundingSphere SPHERE;
		DirectX::BoundingBox AABB;
		DirectX::BoundingOrientedBox OBB;
	};

	CollisionData()
		: OBB()
	{
	}
};

struct TransformData
{
	float4 LocalPosition;
	float4 LocalRotation;
	float4 LocalScaling;

	float4 WorldPosition;
	float4 WorldRotation;
	float4 WorldScaling;

	float4x4 LocalPositionMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalScalingMatrix;

	float4x4 LocalWorldMatrix;
	float4x4 WorldWorldMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;

	float4x4 WorldViewMatrix;
	float4x4 WorldViewProjectionMatrix;

public:
	TransformData() 
		: LocalScaling(float4::ONE)
		, LocalPosition(float4::ZERO)
		, LocalRotation(float4::ZERO)
		, WorldScaling(float4::ONE)
		, WorldPosition(float4::ZERO)
		, WorldRotation(float4::ZERO)
	{}
};

// 설명 :
class GameEngineTransform : public GameEngineDebugObject
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

public:
	inline void SetLocalScale(const float4& _Value)
	{
		CalculateWorldScale(_Value);
		CalculateWorld();
	}

	inline void SetLocalRotation(const float4& _Value)
	{
		CalculateWorldRotation(_Value);
		CalculateWorld();
	}

	inline void SetLocalPosition(const float4& _Value)
	{
		CalculateWorldPosition(_Value);
		CalculateWorld();
	}

	inline void SetLocalRotate(const float4& _Value)
	{
		SetLocalRotation(Data.LocalRotation + _Value);
	}

	inline void SetLocalMove(const float4& _Value)
	{
		SetLocalPosition(Data.LocalPosition + _Value);
	}

	inline void SetWorldScale(const float4& _World)
	{
		float4 Local = _World;

		if (nullptr != Parent)
		{
			Local = _World / Parent->Data.WorldScaling;
		}

		CalculateWorldScale(Local);
		CalculateWorld();
	}

	inline void SetWorldRotation(const float4& _World)
	{
		float4 Local = _World;

		if (nullptr != Parent)
		{
			Local = _World - Parent->Data.WorldRotation;
		}

		CalculateWorldRotation(Local);
		CalculateWorld();
	}

	inline void SetWorldPosition(const float4& _World)
	{
		float4 Local = _World;

		if (nullptr != Parent)
		{
			Local = _World * Parent->Data.WorldWorldMatrix.InverseReturn();
		}

		CalculateWorldPosition(Local);
		CalculateWorld();
	}

	inline void SetWorldMove(const float4& _Value)
	{
		SetWorldPosition(Data.WorldPosition + _Value);
	}

	void SetView(const float4x4& _Mat)
	{
		Data.ViewMatrix = _Mat;
	}

	void SetProjection(const float4x4& _Mat)
	{
		Data.ProjectionMatrix = _Mat;
	}


	inline float4 GetLocalScale() const
	{
		return Data.LocalScaling;
	}

	inline float4 GetLocalRotation() const
	{
		return Data.LocalRotation;
	}

	inline float4 GetLocalPosition() const
	{
		return Data.LocalPosition;
	}

	inline float4x4 GetLocalWorld() const
	{
		return Data.LocalWorldMatrix;
	}

	inline float4x4 GetWorldWorld() const
	{
		return Data.WorldWorldMatrix;
	}

	inline float4x4 GetWorldViewProjection() const
	{
		return Data.WorldViewProjectionMatrix;
	}

	inline float4 GetForwardVector() const
	{
		return Data.WorldWorldMatrix.ArrV[2].NormalizeReturn();
	}

	inline float4 GetBackVector() const
	{
		return -(Data.WorldWorldMatrix.ArrV[2].NormalizeReturn());
	}

	inline float4 GetUpVector() const
	{
		return Data.WorldWorldMatrix.ArrV[1].NormalizeReturn();
	}

	inline float4 GetDownVector() const
	{
		return -(Data.WorldWorldMatrix.ArrV[1].NormalizeReturn());
	}

	inline float4 GetRightVector() const
	{
		return Data.WorldWorldMatrix.ArrV[0].NormalizeReturn();
	}

	inline float4 GetLeftVector() const
	{
		return -(Data.WorldWorldMatrix.ArrV[0].NormalizeReturn());
	}

	inline const TransformData& GetTransformData()
	{
		return Data;
	}

	void CalculateWorld();
	void CalculateWorldViewProjection();
	void DetachTransform();
	void SetParentTransform(GameEngineTransform& _Parent);
	void PixLocalNegativeX();
	void PixLocalPositiveX();

protected:

private:
	GameEngineTransform* Parent;
	std::list<GameEngineTransform*> Childs;

	TransformData Data;

	void CalculateWorldScale(const float4& _Local)
	{
		Data.LocalScaling = _Local;
		Data.LocalScaling.w = 0.0f;

		if (nullptr != Parent)
		{
			Data.WorldScaling = Data.LocalScaling * Parent->Data.WorldScaling;
		}
		else
		{
			Data.WorldScaling = Data.LocalScaling;
		}

		CollisionScaleSetting();
		Data.LocalScalingMatrix.Scale(Data.LocalScaling);

		for (GameEngineTransform* Child : Childs)
		{
			Child->CalculateWorldScale(Child->Data.LocalScaling);
			Child->CalculateWorldPosition(Child->Data.LocalPosition);
		}
	}

	void CalculateWorldRotation(const float4& _Local)
	{
		Data.LocalRotation = _Local;
		Data.LocalRotation.w = 0.0f;

		if (nullptr != Parent)
		{
			Data.WorldRotation = Data.LocalRotation + Parent->Data.WorldRotation;
		}
		else
		{
			Data.WorldRotation = Data.LocalRotation;
		}

		CollisionRotationSetting();
		Data.LocalRotationMatrix.RotationDegree(Data.LocalRotation);

		for (GameEngineTransform* Child : Childs)
		{
			Child->CalculateWorldRotation(Child->Data.LocalRotation);
			Child->CalculateWorldPosition(Child->Data.LocalPosition);
		}
	}

	void CalculateWorldPosition(const float4& _Local)
	{
		Data.LocalPosition = _Local;
		Data.LocalPosition.w = 1.0f;

		if (nullptr != Parent)
		{
			Data.WorldPosition = Data.LocalPosition * Parent->Data.WorldWorldMatrix;
		}
		else
		{
			Data.WorldPosition = Data.LocalPosition;
		}

		CollisionPositionSetting();
		Data.LocalPositionMatrix.Position(Data.LocalPosition);

		for (GameEngineTransform* Child : Childs)
		{
			Child->CalculateWorldPosition(Child->Data.LocalPosition);
		}
	}

	CollisionData CollisionDataObject;

	void CollisionScaleSetting();
	void CollisionRotationSetting();
	void CollisionPositionSetting();
	void CollisionDataSetting();

	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

//========================= 충돌 =========================
public:
	static bool SphereToSphere(const GameEngineTransform& _Left, const GameEngineTransform& _Right);
	static bool AABBToAABB(const GameEngineTransform& _Left, const GameEngineTransform& _Right);
	static bool OBBToOBB(const GameEngineTransform& _Left, const GameEngineTransform& _Right);
};

