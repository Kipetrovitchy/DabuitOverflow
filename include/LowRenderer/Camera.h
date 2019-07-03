#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>
#include "InputMgr.h"
#include "Transform.h"
#include "LibMaths.h"

#define FOV  80.f
#define FAR  10000.f
#define NEAR 0.01f
#define FAR_UI  10000.f
#define NEAR_UI 0.f

class CRenderWindow;
namespace LowRenderer
{
    #pragma region Typedefs
    typedef Physics::Transform      Transform;
    typedef Core::Maths::Vec3       Vec3;
    typedef Core::Maths::Mat        Mat;
    typedef Game::Inputs::InputMgr  InputMgr;
    #pragma endregion

    enum EProjectionType
    {
        PERSPECTIVE,
        ORTHOGRAPHIC,
        COUNT
    };

    class Camera
    {
    protected:
        #pragma region Attributes
        /* Matrix to draw using camera */
        Mat             _matrix;
        Mat             _projection;
        bool            _valueChanged;

        /* Camera attributes */
        Vec3    _pos;
        Vec3    _front;
        Vec3    _up;
        uint    _width;
        uint    _height;
        #pragma endregion

    public:
        #pragma region Constructors
        Camera();
        Camera(EProjectionType type);
        Camera(EProjectionType type, uint w, uint h);
        Camera(EProjectionType type, uint w, uint h, const Vec3& pos,
               const Vec3& front, const Vec3& up);
        virtual ~Camera() = default;
        #pragma endregion

        #pragma region Operators
        Camera& operator= (const Camera& c);
        #pragma endregion

        #pragma region Functions
        virtual void updateSize  (uint width, uint height);
        static Mat createPerspProjMatrix	(uint width, uint height, float near, float far, float fov);
        static Mat createOrthoProjMatrix	(uint width, uint height, float near, float far);
        static Mat createLookAtMatrix		(const Vec3& pos, const Vec3& dir, const Vec3& up);
        #pragma endregion

        #pragma region  Accessors
        inline Vec3&        position()  { return _pos; }
        inline Vec3&        front()     { return _front; }
        Mat&                getViewProj();
        Mat                 getView();
        #pragma endregion
    };
} /* Camera */

#endif//__CAMERA_H__
