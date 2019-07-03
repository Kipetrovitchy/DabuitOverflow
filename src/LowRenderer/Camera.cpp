#include "Camera.h"
#include "Window.h"

#include <cmath>

namespace LowRenderer
{
    #pragma region Constructors
    Camera::Camera():
        _projection     { createPerspProjMatrix(1024.0f, 600.0f, NEAR, FAR, FOV) },
        _valueChanged   { true },
        _pos            { Vec3::zero },
        _front          { Vec3::forward },
        _up             { Vec3::up },
        _width          { 1024 },
        _height         { 600 }
    {}

    Camera::Camera(EProjectionType type) :
        _valueChanged   { true },
        _pos            { Vec3::zero },
        _front          { Vec3::forward },
        _up             { Vec3::up },
        _width          { 1024 },
        _height         { 600 }
    {
        if (type == EProjectionType::PERSPECTIVE)
            _projection = createPerspProjMatrix(_width, _height, NEAR, FAR, FOV);
        else
            _projection = createOrthoProjMatrix(_width, _height, NEAR_UI, FAR_UI);
    }

    Camera::Camera(EProjectionType type, uint w, uint h):
        _valueChanged   { true },
        _pos            { Vec3::zero },
        _front          { Vec3::forward },
        _up             { Vec3::up },
        _width          { w },
        _height         { h }
    {
        if (type == EProjectionType::PERSPECTIVE)
            _projection = createPerspProjMatrix(_width, _height, NEAR, FAR, FOV);
        else
            _projection = createOrthoProjMatrix(_width, _height, NEAR_UI, FAR_UI);
    }

    Camera::Camera(EProjectionType type, uint w, uint h, const Vec3& pos,
           const Vec3& front, const Vec3& up) :
        _valueChanged   { true },
        _pos            { pos },
        _front          { front },
        _up             { up },
        _width          { w },
        _height         { h }
    {
        if (type == EProjectionType::PERSPECTIVE)
            _projection = createPerspProjMatrix(_width, _height, NEAR, FAR, FOV);
        else
            _projection = createOrthoProjMatrix(_width, _height, NEAR_UI, FAR_UI);
    }
    #pragma endregion

    #pragma region Operators
    Camera& Camera::operator= (const Camera& c)
    {
        _projection     = c._projection;
        _valueChanged   = c._valueChanged;
        _pos            = c._pos;
        _front          = c._front;
        _up             = c._up;
        _width          = c._width;
        _height         = c._height;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    
    void Camera::updateSize  (uint width, uint height)
    {
        // update the width and the height of the window
        _width  = width;
        _height = height;
    }

    Mat Camera::createPerspProjMatrix(uint width, uint height, float near,
                                    float far, float fov)
    {
        float ratio  =  (float)width / (float)height;
        float top    =  near * tanf(fov * 0.5f * (float)(M_PI / 180.0f));
        float right  =  top * ratio;

        float* _elements = new float[16]
        {
        /* 0-0 */  near / right,
        /* 0-1 */  0.0f,
        /* 0-2 */  0.0f,
        /* 0-3 */  0.0f,
        /* 1-0 */  0.0f,
        /* 1-1 */  near / top,
        /* 1-2 */  0.0f,
        /* 1-3 */  0.0f,
        /* 2-0 */  0.0f,
        /* 2-1 */  0.0f,
        /* 2-2 */ -(far + near) / (far - near),
        /* 2-3 */ -(2 * far * near) / (far - near),
        /* 3-0 */  0.0f,
        /* 3-1 */  0.0f,
        /* 3-2 */ -1.0f,
        /* 3-3 */  0.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Camera::createOrthoProjMatrix(uint width, uint height, float near, float far)
    {
        float top    =  -(height / 2.f);
        float right  =  -(width / 2.f);

        float* _elements = new float[16]
        {
        /* 0-0 */  1 / right,
        /* 0-1 */  0.0f,
        /* 0-2 */  0.0f,
        /* 0-3 */  0.0f,
        /* 1-0 */  0.0f,
        /* 1-1 */  1 / top,
        /* 1-2 */  0.0f,
        /* 1-3 */  0.0f,
        /* 2-0 */  0.0f,
        /* 2-1 */  0.0f,
        /* 2-2 */ (-2) / (far - near),
        /* 2-3 */ -(far + near) / (far - near),
        /* 3-0 */  0.0f,
        /* 3-1 */  0.0f,
        /* 3-2 */  0.0f,
        /* 3-3 */  1.0f
        };

        return Mat(_elements, 4, 4);
    }

    Mat Camera::createLookAtMatrix   (const Vec3& eye, const Vec3& center,
                                        const Vec3& up)
    {
        Vec3 Z ((eye - center).unit());
        Vec3 Y (up);
        Vec3 X (Y.cross(Z));

        Y = Z.cross(X).unit();
        X.unit();

        // Get the left matrix of the lookAt matrix
        float* _elements = new float[16]
        {
            X.x,  X.y,  X.z,  -X.dot(eye),
            Y.x,  Y.y,  Y.z,  -Y.dot(eye),
            Z.x,  Z.y,  Z.z,  -Z.dot(eye),
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // Multiply the left matrix with the right matrix
        return Mat(_elements, 4, 4);
    }
    #pragma endregion

    #pragma region Accessors
    Mat& Camera::getViewProj()
    {
        // If the values of the camera has changed update the matrix
        if (_valueChanged)
        {
            _matrix = _projection *
                createLookAtMatrix(_pos, _pos + _front, _up);
            _valueChanged = false;
        }

        return _matrix;
    }

    Mat Camera::getView()
    {
        Mat res = createLookAtMatrix(_pos, _pos + _front, _up);
        return res;
    }
    #pragma endregion
} /* LowRenderer */
