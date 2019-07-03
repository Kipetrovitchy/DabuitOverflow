#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "LibMaths.h"
#include "Collider.h"

namespace Physics
{
	#pragma region typedefs
    typedef Core::Maths::Vec3 Vec3;
    typedef Core::Maths::Referential Referential;
    typedef Core::Maths::Mat Mat;
    typedef Physics::Collisions::Collider Collider;
	#pragma endregion

    class Transform
    {
    private:
		#pragma region Attributes
        Vec3 _position;
        Vec3 _rotation;
        Vec3 _scale;
        Mat  _transform;

        Collider* _collider;
		#pragma endregion

    public:
		#pragma region Constructors
        Transform();
        Transform(const Vec3& pos);
        Transform(const Vec3& pos, const Vec3& rot);
        Transform(const Vec3& pos, const Vec3& rot, const Vec3& scale);
        Transform(const Transform& t);
        ~Transform() = default;
		#pragma endregion

		#pragma region Operators
        Transform& operator=(const Transform& t);
		#pragma endregion

		#pragma region Functions
        /* Translate the current position */
        void	translate      (const Vec3& translation)   noexcept;
        /* Rotate the current rotation */
        void	rotate         (const Vec3& rotation)      noexcept;
        /* Grow the current scale */
        void	grow           (const Vec3& growth)        noexcept;
        /* Translate the current position */
        void	translateUpdate(const Vec3& translation)   noexcept;
        /* Rotate the current rotation */
        void	rotateUpdate   (const Vec3& rotation)      noexcept;
        /* Grow the current scale */
        void	growUpdate     (const Vec3& growth)        noexcept;
        void	setPosition    (const Vec3& position)      noexcept;
        void	setRotation    (const Vec3& rotation)      noexcept;
        void	setScale       (const Vec3& scale)         noexcept;
        /* Update the position and the transform matrix */
        void    updatePosition (const Vec3& pos)           noexcept;
        /* Update the rotation and the transform matrix */
        void    updateRotation (const Vec3& rot)           noexcept;
        /* Update the scale and the transform matrix */
        void    updateScale    (const Vec3& scale)         noexcept;
        /* Update the entire matrix with the three vectors */
        void    updateTransform(const Vec3& pos, const Vec3& rot, const Vec3& scale);
        /* Update the transform */
        void    updateMatrix() noexcept;
        Mat worldToLocal() noexcept;
        Mat localToWorld() noexcept;

        void    setCollider(Collider* collider) noexcept;
        /*Compute the TRS matrix*/
        static Mat worldToLocal             (const Referential& ref);
        static Mat localToWorld             (const Referential& ref);
        static Mat createTranslationMatrix	(const Vec3& translation);
        static Mat createScaleMatrix		(const Vec3& scale);
        static Mat createXRotationMatrix	(float angle);
        static Mat createYRotationMatrix	(float angle);
        static Mat createZRotationMatrix	(float angle);
        static Mat createEulerRotation		(const Vec3& angle);
        static Mat createTransformMatrix	(const Vec3& rotation,
                                             const Vec3& position, const Vec3& scale);
		#pragma endregion

		#pragma region Accessors
        Vec3& position()        { return _position; };
        Vec3  position()  const { return _position; };
        Vec3& rotation()        { return _rotation; };
        Vec3  rotation()  const { return _rotation; };
        Vec3& scale()           { return _scale; };
        Vec3  scale()     const { return _scale; };
        Mat& transform()       { return _transform; };
        Mat  transform() const { return _transform; };
		#pragma endregion
    };
} /* Physics */

#endif//__TRANSFORM_H__
