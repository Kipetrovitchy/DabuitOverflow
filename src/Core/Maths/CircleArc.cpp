#include "CircleArc.h"
#include "Plane.h"
#include "Vec3.h"
#include <cmath>

namespace Core::Maths
{
	#pragma region Constructors
	CircleArc::CircleArc():
		_angle { 0.0f }
	{}

	CircleArc::CircleArc(const Vec3& s, const Vec3& e, const Vec3& w):
		_center	{ Vec3::zero },
		_start   { s },
		_normal  { Vec3::zero },
		_angle	{ 0.0f }
	{
		Vec3 centerStartEnd = Vec3::center(s, e);
		// Get the 3 planes of the circles
		Plane planeCircle			(s, w, e);
		Plane planeMediatorStartEnd	(centerStartEnd, Vec3::vec3FromPoints(s, e));
		Plane planeMediatorStartway { Plane::mediatorPlane(s, w) };

		// Get the center of the plane
		_center = Plane::planeIntersection(
			planeCircle,
			planeMediatorStartEnd,
			planeMediatorStartway
		);
		_normal = planeCircle.normal;

		// Get the way _angle
		Vec3 CS { Vec3::vec3FromPoints(_center, s) };
		Vec3 CE { Vec3::vec3FromPoints(_center, e) };
		_angle = CS.angle(CE);

		// If the way and the center are of the same side of the plane start end revert
		Plane planeStartEnd (s, Vec3::vec3FromPoints(centerStartEnd, _center));
		if (planeStartEnd.sameSide(_center, w))
			_angle = 2.0f * M_PI - _angle;
	}

	CircleArc::CircleArc(const CircleArc& c):
		_center	{ c._center },
		_start	{ c._start },
		_normal	{ c._normal },
		_angle	{ c._angle }
	{}
	#pragma endregion 

	#pragma region Operator
	CircleArc& CircleArc::operator= (const CircleArc& c)
	{
		_start	= c._start;
		_normal	= c._normal;
		_center	= c._center;
		_angle	= c._angle;

		return *this;
	}
	#pragma endregion

	#pragma region Fonction
	Vec3 CircleArc::getPosition(float progress) const
	{
		// Rotate the start around the center, first set the start to the local
		// of the world. Rotate the start. Re-set the new computed point to the
		// local of the circlearc.
		return
			Mat::createRotation(_normal, progress * _angle) * (_start - _center)
			+ _center;
	}
	#pragma endregion
} /* Maths */
