#ifndef __CAMERA_UI_H__
#define __CAMERA_UI_H__

#include <SDL2/SDL.h>
#include "InputMgr.h"
#include "Transform.h"
#include "LibMaths.h"
#include "Camera.h"



class CRenderWindow;
namespace LowRenderer
{
    #pragma region Typedefs
    typedef Physics::Transform      Transform;
    typedef Core::Maths::Vec3       Vec3;
    typedef Core::Maths::Mat        Mat;
    typedef Game::Inputs::InputMgr  InputMgr;
    #pragma endregion

    class CameraUI : public Camera
    {
    public:
        #pragma region Constructors
        CameraUI();
        CameraUI(uint w, uint h);
        CameraUI(uint w, uint h, const Vec3& pos, const Vec3& front, const Vec3& up);
        ~CameraUI() = default;
        #pragma endregion

        #pragma region Operators
        CameraUI& operator= (const CameraUI& c);
        #pragma endregion

        #pragma region Methods
        void updateSize  (uint width, uint height) override;
        #pragma endregion
    };
} /* Camera */

#endif//__CAMERA_UI_H__
