#ifndef __CAMERA_3D_H__
#define __CAMERA_3D_H__

#include <SDL2/SDL.h>
#include "InputMgr.h"
#include "Transform.h"
#include "LibMaths.h"
#include "Camera.h"

#define CAMERA_BASE_DISTANCE        10.0f
#define CAMERA_BASE_THETA           0.0f
#define CAMERA_BASE_PHI             0.0f
#define CAMERA_BASE_PHI_MAX         (M_PI / 2.0f - 0.01f)
#define CAMERA_BASE_PHI_MIN         (-M_PI / 4.0f)
#define CAMERA_BASE_ROTATION_SPEED  M_PI

#define CAMERA_SENSIVITY 0.0025f

class CRenderWindow;
namespace LowRenderer
{
    #pragma region Typedefs
    typedef Physics::Transform      Transform;
    typedef Core::Maths::Vec3       Vec3;
    typedef Core::Maths::Mat        Mat;
    typedef Game::Inputs::InputMgr  InputMgr;
    #pragma endregion

    class Camera3D : public Camera
    {
    private:
        #pragma region Attributes
        /* Matrix to draw using camera */
        Transform*      _target;
        bool            _isPerspective;

        /* Camera attributes */
        Vec3    _localPosition;
        float   _mouseX;
        float   _mouseY;

        /* Euler angles */
        float   _distance;
        float   _theta;
        float   _phi;
        float   _phiMax;
        float   _phiMin;

        /* Camera Options */
        float   _rotationSpeed;
        #pragma endregion

        #pragma region Functions
        void        computeOffset(float x, float y) noexcept;
        Camera3D&   updateLocalPosition()           noexcept;
        Camera3D&   updatePositionToEntity()        noexcept;
        void        warpMouse(SDL_Window* win)      noexcept;
        #pragma endregion

    public:
        #pragma region Constructors
        Camera3D();
        Camera3D(uint w, uint h, float yaw = 0.0f, float pitch = 0.0f);
        ~Camera3D() = default;
        #pragma endregion

        #pragma region Operators
        Camera3D& operator= (const Camera3D& c);
        #pragma endregion

        #pragma region  Accessors
        inline Transform*&  target()    { return _target; }
        inline float& distance()        { return _distance; };
        inline float  distance()  const { return _distance; };
        inline float& theta()           { return _theta; };
        inline float  theta()     const { return _theta; };
        inline float& phi()             { return _phi; };
        inline float  phi()       const { return _phi; };
        #pragma endregion

        #pragma region Functions
        void        updateSize  (uint width, uint height) override;
        Camera3D&   update(float x, float y, SDL_Window* win) noexcept;
        /* Change the projection between perspective and orthogonal */
        void	changeProjection();

        void    updateFov(float fov) noexcept;
        #pragma endregion
    };
} /* Camera */

#endif//__CAMERA_3D_H__
