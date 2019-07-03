#ifndef __VEC2_H__
#define __VEC2_H__

#include <iostream>
#include <string>

namespace Core::Maths
{
	typedef unsigned int uint;

	struct Vec2
	{
		#pragma region Attributes
		union 
		{
			float _x;
			float x;
		};
		union
		{
			float _y;
			float y;
		};
		#pragma endregion

		#pragma region Contructors
		Vec2() = default;
		Vec2(float x, float y);
		Vec2(const Vec2& vec);
		~Vec2() = default;
		#pragma endregion

		#pragma region Operators
		Vec2& operator= (const Vec2& vec);
		Vec2  operator+ (const Vec2& vec) const;
		Vec2& operator+=(const Vec2& vec);
		Vec2  operator- (const Vec2& vec) const;
		Vec2& operator-=(const Vec2& vec);
		Vec2  operator- ()                const;
		Vec2  operator* (float scale)     const;
		Vec2& operator*=(float scale);
		Vec2  operator/ (float scale)     const;
		Vec2& operator/=(float scale);

		float  operator, (const Vec2& vec) const;
		float& operator[](uint i);
		#pragma endregion

		#pragma region Functions
		float length       () const;
		float squaredLength() const;
		void  unit();
		Vec2  unit() const;
		float dot  (const Vec2& vec) const;
		float cross(const Vec2& vec) const;

		float distance(const Vec2& vec) const;
		float angle   (const Vec2& vec) const;

		void rotation(float angle);
		Vec2 rotation(float angle) const;
		void pointRotation(const Vec2& origin, float angle);
		Vec2 pointRotation(const Vec2& origin, float angle) const;
		void normal();
		Vec2 normal() const;

		bool equals  (const Vec2& vec, float epsilon) const;
		bool colinear(const Vec2& vec, float epsilon) const;

		std::string to_string() const;
		#pragma endregion

		static Vec2 zero;
		static Vec2 up;
		static Vec2 down;
		static Vec2 left;
		static Vec2 right;
	};

	std::ostream& operator<<(std::ostream& os, const Vec2 vec);
}

#endif//__VECTOR2_H__
