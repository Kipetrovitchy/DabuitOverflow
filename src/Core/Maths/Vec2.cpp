#include "Vec2.h"

#include <cmath>

namespace Core::Maths
{
	Vec2 Vec2::zero  = Vec2( 0.f,  0.f);
	Vec2 Vec2::up    = Vec2( 0.f,  1.f);
	Vec2 Vec2::down  = Vec2( 0.f, -1.f);
	Vec2 Vec2::left  = Vec2(-1.f,  0.f);
	Vec2 Vec2::right = Vec2( 1.f,  0.f);

	#pragma region Contructors
	Vec2::Vec2(float x, float y):
		_x {x},
		_y {y}
	{}

	Vec2::Vec2(const Vec2& vec):
		_x {vec._x},
		_y {vec._y}
	{}
	#pragma endregion

	#pragma region Operators
	Vec2& Vec2::operator=(const Vec2& vec)
	{
		_x = vec._x;
		_y = vec._y;

		return *this;
	}

	Vec2 Vec2::operator+(const Vec2& vec) const
	{
		return Vec2(_x + vec._x, _y + vec._y);
	}

	Vec2& Vec2::operator+=(const Vec2& vec)
	{
		_x += vec._x;
		_y += vec._y;

		return *this;
	}

	Vec2 Vec2::operator-(const Vec2& vec) const
	{
		return Vec2(_x - vec._x, _y - vec._y);
	}

	Vec2& Vec2::operator-=(const Vec2& vec)
	{
		_x -= vec._x;
		_y -= vec._y;

		return *this;
	}

	Vec2 Vec2::operator-() const
	{
		return Vec2(-_x, -_y);
	}

	Vec2 Vec2::operator*(float scale) const
	{
		return Vec2(_x * scale, _y * scale);
	}

	Vec2& Vec2::operator*=(float scale)
	{
		_x *= scale;
		_y *= scale;

		return *this;
	}

	Vec2 Vec2::operator/(float scale) const
	{
		return Vec2(_x / scale, _y / scale);
	}

	Vec2& Vec2::operator/=(float scale)
	{
		_x /= scale;
		_y /= scale;

		return *this;
	}

	float Vec2::operator,(const Vec2& vec) const
	{
		return dot(vec);
	}

	float& Vec2::operator[](uint i)
	{
		if (i % 2)
			return _y;

		return _x;
	}
	#pragma endregion

	#pragma region Functions
	float Vec2::length() const
	{
		return sqrt(_x*_x + _y*_y);
	}

	float Vec2::squaredLength() const
	{
		return _x*_x + _y*_y;
	}

	void Vec2::unit()
	{
		float len = length();
		if (len == 0.0f)
			return;

		_x /= len;
		_y /= len;
	}

	Vec2 Vec2::unit() const
	{
		float len = length();
		if (len == 0.f)
			return Vec2::zero;

		Vec2 vec;
		vec._x = _x / len;
		vec._y = _y / len;

		return vec;
	}

	float Vec2::dot(const Vec2& vec) const
	{
		return (_x * vec._x) + (_y * vec._y);
	}

	float Vec2::cross(const Vec2& vec) const
	{
		return (_x * vec._y) - (_y * vec._x);
	}

	float Vec2::angle(const Vec2& vec) const
	{
		float len = length() * vec.length();
		if (len == 0)
			return 0.f;

		return acos(
			dot(vec) / len
		);
	}

	float Vec2::distance(const Vec2& vec) const
	{
		return (*this - vec).length();
	}

	void Vec2::rotation(float angle)
	{
		Vec2 vec;
		vec._x = _x * cosf(angle) - _y * sinf(angle);
		vec._y = _x * sinf(angle) + _y * cosf(angle);

		*this = vec;
	}

	Vec2 Vec2::rotation(float angle) const
	{
		Vec2 vec;
		vec._x = _x * cos(angle) - _y * sin(angle);
		vec._y = _x * sin(angle) + _y * cos(angle);

		return vec;
	}

	void Vec2::pointRotation(const Vec2& origin, float angle)
	{
		// Change the origin of of the plan using the new point as an origin
		*this -= origin;
		// Rotate the point
		rotation(angle);
		// Change it back basic origin
		*this += origin;
	}

	Vec2 Vec2::pointRotation(const Vec2& origin, float angle) const
	{
		// Change the origin of of the plan using the new point as an origin
		Vec2 point_to_origin = *this - origin;
		// Rotate the point
		Vec2 point_rot = ((const Vec2&)point_to_origin).rotation(angle);
		// Change it back basic origin
		Vec2 point_ans = point_rot + origin;

		return point_ans;
	}

	void Vec2::normal()
	{
		Vec2 vec(-_y, _x);

		*this = vec;
	}

	Vec2 Vec2::normal() const
	{
		Vec2 vec(-_y, _x);

		return vec;
	}

	bool Vec2::equals(const Vec2& vec, float epsilon) const
	{
		return 	fabs(_x - vec._x) < epsilon &&
				fabs(_y - vec._y) < epsilon;
	}

	bool Vec2::colinear(const Vec2& vec, float epsilon) const
	{
		Vec2 n = normal();

		return fabs((n,vec)) < epsilon;
	}

	std::string Vec2::to_string() const
	{
		return std::to_string(_x) + "," + std::to_string(_y);
	}

	std::ostream& operator<<(std::ostream& os, const Vec2 vec)
	{
		os << vec._x << ',' << vec._y;
		return os;
	}
	#pragma endregion
} /* Maths */