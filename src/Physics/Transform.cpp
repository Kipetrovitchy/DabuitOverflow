#include "Transform.h"
#include <cmath>

namespace Physics
{
	#pragma region Constructors
    Transform::Transform():
        _position { Vec3::zero },
        _rotation { Vec3::zero },
        _scale    { Vec3::one },
        _collider { nullptr }
    {
        updateMatrix();
    }

    Transform::Transform(const Vec3& pos):
        _position { pos },
        _collider { nullptr }
    {
        updateMatrix();
    }

    Transform::Transform(const Vec3& pos, const Vec3& rot):
        _position  {pos},
        _rotation  {rot},
        _collider { nullptr }
    {
        updateMatrix();
    }

    Transform::Transform(const Vec3& pos, const Vec3& rot, const Vec3& scale):
        _position  {pos},
        _rotation  {rot},
        _scale     {scale},
        _collider  { nullptr }
    {
        updateMatrix();
    }

    Transform::Transform(const Transform& t):
        _position  {t._position},
        _rotation  {t._rotation},
        _scale     {t._scale},
        _transform {t._transform},
        _collider  { nullptr }
    {}
	#pragma endregion

	#pragma region Operators
    Transform& Transform::operator=(const Transform& t)
    {
        _position  = t._position;
        _rotation  = t._rotation;
        _scale     = t._scale;
        _transform = t._transform;

        return *this;
    }
	#pragma endregion

	#pragma region Functions
    void Transform::translate      (const Vec3& translation)   noexcept
    {
        // Translate the object by the vec3 given
        _position += translation;
    }

    void Transform::rotate         (const Vec3& rotation)      noexcept
    {
        // Rotate the object by the vec3 given
        _rotation += rotation;
    }

    void Transform::grow           (const Vec3& growth)        noexcept
    {
        // Grow the object by the vec3 given
        _scale += growth;
    }

     void Transform::translateUpdate(const Vec3& translation)   noexcept
    {
        // Translate the object by the vec3 given
        _position += translation;
        updateMatrix();
    }

    void Transform::rotateUpdate   (const Vec3& rotation)      noexcept
    {
        // Rotate the object by the vec3 given
        _rotation += rotation;
        updateMatrix();
    }

    void Transform::growUpdate     (const Vec3& growth)        noexcept
    {
        // Grow the object by the vec3 given
        _scale += growth;
        updateMatrix();
    }

    void Transform::setPosition    (const Vec3& position)      noexcept
    {
        // Set the position without updating the transform matrix
        _position = position;
    }

    void Transform::setRotation    (const Vec3& rotation)      noexcept
    {
        // Set the rotation without updating the transform matrix
        _rotation = rotation;
    }

    void Transform::setScale       (const Vec3& scale)         noexcept
    {
        // Set the scale without updating the transform matrix
        _scale = scale;
    }

    void Transform::updatePosition (const Vec3& pos) noexcept
    {
        // Update the position
        _position = pos;

        updateMatrix();
    }

    void Transform::updateRotation (const Vec3& rot) noexcept
    {
        // Update the rotation
        _rotation = rot;

        updateMatrix();
    }

    void Transform::updateScale    (const Vec3& scale) noexcept
    {
        // Update the scale
        _scale = scale;

        updateMatrix();
    }

    void Transform::updateTransform(const Vec3& pos, const Vec3& rot, const Vec3& scale)
    {
        // Update all the Vec3
        _position = pos;
        _rotation = rot;
        _scale    = scale;

        updateMatrix();
    }

    void Transform::updateMatrix() noexcept
    {
        _transform = createTransformMatrix(_rotation, _position, _scale);

        if (_collider)
            _collider->updateTransform(*this);
    }

    Mat Transform::worldToLocal() noexcept
    {
        // create the referential using the rotation
        Mat rotation = Transform::createEulerRotation(_rotation);
        Vec3 i = rotation * Vec3::right;
        Vec3 j = rotation * Vec3::up;
        Vec3 k = rotation * Vec3::forward;

        float* _elements = new float[16]
        {
            i.x,  j.x,  k.x,  _position.x,
            i.y,  j.y,  k.y,  _position.y,
            i.z,  j.z,  k.z,  _position.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(_elements, 4, 4).inverse();
    }

    Mat Transform::localToWorld() noexcept
    {
        // create the referential using the rotation
        Mat rotation = Transform::createEulerRotation(_rotation);
        Vec3 i = rotation * Vec3::right;
        Vec3 j = rotation * Vec3::up;
        Vec3 k = rotation * Vec3::forward;

        float* _elements = new float[16]
        {
            i.x,  j.x,  k.x,  _position.x,
            i.y,  j.y,  k.y,  _position.y,
            i.z,  j.z,  k.z,  _position.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(_elements, 4, 4);
    }
    
    void Transform::setCollider(Collider* collider) noexcept
    {
        _collider = collider;
    }

    Mat Transform::worldToLocal(const Referential& ref)
    {
        float* _elements = new float[16]
        {
            ref.i.x, ref.j.x, ref.k.x, ref.origin.x,
            ref.i.y, ref.j.y, ref.k.y, ref.origin.y,
            ref.i.z, ref.j.z, ref.k.z, ref.origin.z,
            0.0f,    0.0f,    0.0f,    1.0f
        };

        return Mat(_elements, 4, 4).inverse();
    }

    Mat Transform::localToWorld(const Referential& ref)
    {
        float* _elements = new float[16]
        {
            ref.i.x, ref.j.x, ref.k.x, ref.origin.x,
            ref.i.y, ref.j.y, ref.k.y, ref.origin.y,
            ref.i.z, ref.j.z, ref.k.z, ref.origin.z,
            0.0f,    0.0f,    0.0f,    1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Transform::createTranslationMatrix(const Vec3& translation)
    {
        float* _elements = new float[16]
        {
            1.0f, 0.0f, 0.0f, translation.x,
            0.0f, 1.0f, 0.0f, translation.y,
            0.0f, 0.0f, 1.0f, translation.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Transform::createScaleMatrix(const Vec3& scale)
    {
        float* _elements = new float[16]
        {
            scale.x, 0.0f,    0.0f,    0.0f,
            0.0f,    scale.y, 0.0f,    0.0f,
            0.0f,    0.0f,    scale.z, 0.0f,
            0.0f,    0.0f,    0.0f,    1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Transform::createXRotationMatrix(float angle)
    {
        float c = cosf(angle);
        float s = sinf(angle);

        float* _elements = new float[16]
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f,    c,   -s, 0.0f,
            0.0f,    s,    c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Transform::createYRotationMatrix(float angle)
    {
        float c = cosf(angle);
        float s = sinf(angle);

        float* _elements = new float[16]
        {
                c, 0.0f,    s, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
                -s, 0.0f,    c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Transform::createZRotationMatrix(float angle)
    {
        float c = cosf(angle);
        float s = sinf(angle);

        float* _elements = new float[16]
        {
                c,   -s, 0.0f, 0.0f,
                s,    c, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Transform::createEulerRotation(const Vec3& angle)
    {
        Mat res = createYRotationMatrix(angle.y)
            * createXRotationMatrix(angle.x)
            * createZRotationMatrix(angle.z);

        return res;
    }

    Mat Transform::createTransformMatrix(const Vec3& rotation, const Vec3& position,
                                        const Vec3& scale)
    {
        return createTranslationMatrix(position)
                * createYRotationMatrix(rotation.y)
                * createXRotationMatrix(rotation.x)
                * createZRotationMatrix(rotation.z)
                * createScaleMatrix    (scale);
    }
	#pragma endregion
} /* Physics */
