#include "CameraUI.h"
#include "Window.h"

#include <cmath>

namespace LowRenderer
{
    #pragma region Constructors
    CameraUI::CameraUI():
        Camera(EProjectionType::ORTHOGRAPHIC)
    {}

    CameraUI::CameraUI(uint w, uint h):
        Camera(EProjectionType::ORTHOGRAPHIC, w, h)
    {}

    CameraUI::CameraUI(uint w, uint h, const Vec3& pos,
                       const Vec3& front, const Vec3& up) :
        Camera(EProjectionType::ORTHOGRAPHIC, w, h, pos, front, up)
    {}
    #pragma endregion

    #pragma region Operators
    CameraUI& CameraUI::operator= (const CameraUI& c)
    {
        Camera::operator=(c);

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    void CameraUI::updateSize(uint width, uint height)
    {
        // update the width and the height of the window
        _width  = width;
        _height = height;
        _projection = Camera::createOrthoProjMatrix(
                                        (float)width, (float)height, NEAR_UI, FAR_UI);
        _valueChanged = true;
    }
    #pragma endregion
} /* LowRenderer */
