#pragma once
#include <cmath>

template<typename Scalar>
union Vector2
{
	struct { Scalar x, y; };
	Scalar raw[2];


	constexpr Vector2() noexcept: x(0), y(0){}
	constexpr Vector2(Scalar x, Scalar y) noexcept: x(x), y(y) {}
	constexpr Vector2(const Vector2& rhs) noexcept: x(rhs.x), y(rhs.y){}
	constexpr Vector2(Vector2&& rhs) noexcept: x(rhs.x), y(rhs.y) {}
	~Vector2() = default;

	constexpr Vector2& operator-() noexcept
	{
		x = -x;
		y = -y;
		return *this;
	}
	
	constexpr Vector2& operator=(const Vector2& rhs) noexcept
	{
		if(this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}
	constexpr Vector2& operator=(Vector2&& rhs) noexcept
	{
		if(this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}

	constexpr bool operator==(const Vector2& rhs) noexcept
	{
		return x == rhs.x && y == rhs.y;
	}
	constexpr bool operator!=(const Vector2& rhs) noexcept
	{
		return !(*this == rhs);
	}

	constexpr Vector2& operator+=(const Vector2& rhs) noexcept
	{
		x += rhs.x; y += rhs.y;
		return *this;
	}
	constexpr Vector2& operator-=(const Vector2& rhs) noexcept
	{
		x -= rhs.x; y -= rhs.y;
		return *this;
	}
	constexpr Vector2& operator*=(const Vector2& rhs) noexcept
	{
		x *= rhs.x; y *= rhs.y;
		return *this;
	}
	constexpr Vector2& operator/=(const Vector2& rhs) noexcept
	{
		x /= rhs.x; y /= rhs.y;
		return *this;
	}

	constexpr Vector2& operator+=(Scalar rhs) noexcept
	{
		x += rhs; y += rhs;
		return *this;
	}
	constexpr Vector2& operator-=(Scalar rhs) noexcept
	{
		x -= rhs; y -= rhs;
		return *this;
	}
	constexpr Vector2& operator*=(Scalar rhs) noexcept
	{
		x *= rhs; y *= rhs;
		return *this;
	}
	constexpr Vector2& operator/=(Scalar rhs) noexcept
	{ 
		x /= rhs; y /= rhs; 
		return *this;
	}
	
	constexpr Vector2 operator+(const Vector2& rhs) noexcept { return Vector2(*this) += rhs;}
	constexpr Vector2 operator-(const Vector2& rhs) noexcept { return Vector2(*this) -= rhs;}
	constexpr Vector2 operator*(const Vector2& rhs) noexcept { return Vector2(*this) *= rhs;}
	constexpr Vector2 operator/(const Vector2& rhs) noexcept { return Vector2(*this) /= rhs;}
	
	
	constexpr Vector2 operator+(Scalar rhs) noexcept { return Vector2(*this) += rhs;}
	constexpr Vector2 operator-(Scalar rhs) noexcept { return Vector2(*this) -= rhs;}
	constexpr Vector2 operator*(Scalar rhs) noexcept { return Vector2(*this) *= rhs;}
	constexpr Vector2 operator/(Scalar rhs) noexcept { return Vector2(*this) /= rhs;}

	[[nodiscard]] constexpr Scalar squaredLength() const 
	{
		return x * x + y * y;
	}
	Scalar length() const
	{
		return std::sqrt(static_cast<double>(squaredLength()));
	}

	Vector2& normalize()
	{
		const auto len = length();
		if(len != 0)
		{
			*this /= len;
		}
		return *this;
	}

	Vector2 normalized() const
	{
		return Vector2(*this).normalize();
	}
};
using Vec2 = Vector2<double>;
using Vec2f = Vector2<float>; 