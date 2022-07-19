#pragma once
#include <math.h>
#include <Windows.h>

// ���� :
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float DEG;
	static const float DegreeToRadian;
	static const float RadianToDegree;

	static float Lerp(float _P1, float _P2, float _Time)
	{
		return (1.0f - _Time) * _P1 + _Time * _P2;
	}

	static float LerpLimit(float _P1, float _P2, float _Time)
	{
		if (1.0f <= _Time)
		{
			_Time = 1.0f;
		}

		return Lerp(_P1, _P2, _Time);
	}

protected:

private:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;
};

class float4
{
public:
	static float VectorXYtoDegree(const float4& _Postion, const float4& _Target)
	{
		return VectorXYtoRadian(_Postion, _Target) * GameEngineMath::RadianToDegree;
	}

	static float VectorXYtoRadian(const float4& _Postion, const float4& _Target)
	{
		float4 Dir = _Target - _Postion;
		Dir.Normal2D();

		float Angle = acosf(Dir.x);

		if (_Postion.y > _Target.y)
		{
			Angle = GameEngineMath::PI2 - Angle;
		}

		return Angle;
	}


	static float4 DegreeToDirection2D(float _Degree)
	{
		return RadianToDirection2D(_Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RadianToDirection2D(float _Radian)
	{
		return { cosf(_Radian), sinf(_Radian) };
	}


	static float4 VectorRotationToDegreeZAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianZAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianZAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		
		Rot.x = _Value.x * cosf(_Radian) - _Value.y * sinf(_Radian);
		Rot.y = _Value.x * sinf(_Radian) + _Value.y * cosf(_Radian);
		Rot.z = _Value.z;

		return Rot;
	}

	static float4 VectorRotationToDegreeYAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianYAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianYAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		
		Rot.x = _Value.x * cosf(_Radian) - _Value.z * sinf(_Radian);
		Rot.z = _Value.x * sinf(_Radian) + _Value.z * cosf(_Radian);
		Rot.y = _Value.y;

		return Rot;
	}

	static float4 VectorRotationToDegreeXAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianXAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianXAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;

		Rot.z = _Value.z * cosf(_Radian) - _Value.y * sinf(_Radian);
		Rot.y = _Value.z * sinf(_Radian) + _Value.y * cosf(_Radian);
		Rot.x = _Value.x;

		return Rot;
	}

	static float4 Lerp(float4 _P1, float4 _P2, float _Time)
	{
		return _P1 * (1.0f - _Time) + _P2 * _Time;
	}

	static float4 LerpLimit(float4 _P1, float4 _P2, float _Time)
	{
		if (1.0f <= _Time)
		{
			_Time = 1.0f;
		}

		return Lerp(_P1, _P2, _Time);
	}

public:
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;
	static const float4 ZERO;
	static const float4 ONE;

public:
	float x;
	float y;
	float z;
	float w;

public:
	bool IsZero2D() const
	{
		return x == 0.0f && y == 0.0f;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	POINT GetConvertWindowPOINT()
	{
		return POINT(ix(), iy());
	}
	
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.5f, 1.0f };
	}

	float Len2D() const
	{
		return sqrtf((x * x) + (y * y));
	}

	float Len3D() const
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	
	void Normal2D()
	{
		float Len = Len2D();
		if (0 == Len)
		{
			return;
		}

		x /= Len;
		y /= Len;

		return;
	}

	void Range2D(float _Max)
	{
		Normal2D();

		x *= _Max;
		y *= _Max;

		return;
	}


	float4 operator+(const float4& _Other) const
	{
		return { x + _Other.x, y + _Other.y, z + _Other.z, 1.0f };
	}
	
	float4 operator-(const float4& _Other) const
	{
		return { x - _Other.x, y - _Other.y, z - _Other.z, 1.0f };
	}

	float4 operator-() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4 operator*(const float _Value) const
	{
		return { x * _Value, y * _Value, z * _Value, 1.0f };
	}

	float4& operator+=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

	float4& operator-=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;

		return *this;
	}

	float4& operator*=(const float _Other)
	{
		x *= _Other;
		y *= _Other;
		z *= _Other;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;

		return *this;
	}

	bool CompareInt2D(const float4& _Value) const
	{
		return ix() == _Value.ix() && iy() == _Value.iy();
	}

	bool CompareInt3D(const float4& _Value) const
	{
		return ix() == _Value.ix() && iy() == _Value.iy() && iz() == _Value.iz();
	}

	float4 RotationToDegreeZ(float _Degree)
	{
		return RotationToRadianZAXis(_Degree * GameEngineMath::DegreeToRadian);
	}

	float4 RotationToRadianZAXis(float _Radian)
	{
		*this = VectorRotationToRadianZAxis(*this, _Radian);
		return *this;
	}

	POINT ToWinAPIPOINT() const
	{
		POINT NewPoint;
		NewPoint.x = ix();
		NewPoint.y = iy();
		return NewPoint;
	}

public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{
	}
	float4(float _x, float _y)
		: x(_x), y(_y), z(1.0f), w(1.0f)
	{
	}
	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{
	}
	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}
};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	float4 CenterLeftTopPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterTop()) };
	}

	float4 CenterLeftBotPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterBot()) };
	}

	float4 CenterRightTopPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterTop()) };
	}

	float4 CenterRightBotPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterBot()) };
	}

	int CenterLeft() const
	{
		return Pos.ix() - Scale.hix();
	}

	int CenterRight() const
	{
		return Pos.ix() + Scale.hix();
	}

	int CenterTop() const
	{
		return Pos.iy() - Scale.hiy();
	}

	int CenterBot() const
	{
		return Pos.iy() + Scale.hiy();
	}

	bool OverLap(const GameEngineRect& _Other)
	{
		if (CenterBot() < _Other.CenterTop())
		{
			return false;
		}

		if (CenterTop() > _Other.CenterBot())
		{
			return false;
		}

		if (CenterRight() < _Other.CenterLeft())
		{
			return false;
		}

		if (CenterLeft() > _Other.CenterRight())
		{
			return false;
		}

		return true;
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{
	}
};

class float4x4
{
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
	};
};