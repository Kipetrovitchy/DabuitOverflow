#include "Camera3D.h"
#include "Window.h"

#include <cmath>

namespace LowRenderer
{
    #pragma region Constructors
    Camera3D::Camera3D():
        Camera(EProjectionType::PERSPECTIVE),
        _target         { nullptr },
        _isPerspective  { true },
        _localPosition  { Vec3::zero },
        _mouseX         { 0.0f },
        _mouseY         { 0.0f },
        _distance       { CAMERA_BASE_DISTANCE },
        _theta          { CAMERA_BASE_THETA },
        _phi            { CAMERA_BASE_PHI },
        _phiMax         { CAMERA_BASE_PHI_MAX },
        _phiMin         { CAMERA_BASE_PHI_MIN },
        _rotationSpeed  { CAMERA_BASE_ROTATION_SPEED }
    {}

    Camera3D::Camera3D(uint w, uint h, float theta, float phi):
        Camera(EProjectionType::PERSPECTIVE, w, h),
        _target         { nullptr },
        _isPerspective  { true },
        _localPosition  { Vec3::zero },
        _mouseX         { w / 2.0f },
        _mouseY         { h / 2.0f },
        _distance       { CAMERA_BASE_DISTANCE },
        _theta          { theta },
        _phi            { phi },
        _phiMax         { CAMERA_BASE_PHI_MAX },
        _phiMin         { CAMERA_BASE_PHI_MIN },
        _rotationSpeed  { CAMERA_BASE_ROTATION_SPEED }
    {}
    #pragma endregion

    #pragma region Operators
    Camera3D& Camera3D::operator= (const Camera3D& c)
    {
        Camera::operator=(c);
        _target         = c._target;
        _valueChanged   = c._valueChanged;
        _isPerspective  = c._isPerspective;
        _localPosition  = c._localPosition;
        _mouseX         = c._mouseX;
        _mouseY         = c._mouseY;
        _distance       = c._distance;
        _theta          = c._theta;
        _phi            = c._phi;
        _phiMax         = c._phiMax;
        _phiMin         = c._phiMin;
        _rotationSpeed  = c._rotationSpeed;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    void Camera3D::updateSize(uint width, uint height)
    {
        // update the width and the height of the window
        _width  = width;
        _height = height;
        _projection = Camera::createPerspProjMatrix(
                                        (float)width, (float)height, NEAR, FAR, FOV);
        _valueChanged = true;
    }

    Camera3D& Camera3D::update(float x, float y, SDL_Window* win) noexcept
    {
        if (x == 0 && y == 0)
            return *this;
        computeOffset(x, y);

        // Clamp phi between it's max and it's minimal value
        _phi = (_phi < _phiMin) ? _phiMin : (_phiMax < _phi) ? _phiMax : _phi;

        updateLocalPosition();
        updatePositionToEntity();

        warpMouse(win);

        return *this;
    }

    void Camera3D::computeOffset(float x, float y) noexcept
    {
        float xoffset {float(x - _mouseX)};
        float yoffset {float(y - _mouseY)};

        _mouseX = x;
        _mouseY = y;

        xoffset *= CAMERA_SENSIVITY;
        yoffset *= CAMERA_SENSIVITY;

        _theta  += xoffset;
        _phi    -= yoffset;
    }

    Camera3D& Camera3D::updateLocalPosition() noexcept
    {
        float cosPhi = cosf(_phi);
        // Compute the new local position of the camera
        _front.x = cosPhi     * cosf(_theta);
        _front.y = sinf(_phi);
        _front.z = cosPhi     * sinf(_theta);

        _front.unit();

        return *this;
    }

    Camera3D& Camera3D::updatePositionToEntity() noexcept
    {
        Vec3 entityPos { 0.0f };
        
        // Change the look at of the camera
        if (_target)
            entityPos = _target->position();
        
        // Update the position and the front of the camera
        _pos = entityPos;
        _pos.y += _target->scale().y / 2.0f;

        // Set that the value changed
        _valueChanged = true;

        return *this;
    }

    void Camera3D::warpMouse(SDL_Window* win) noexcept
    {
        int centerW {(int)_width / 2};
        int centerH {(int)_height / 2};

        int halfboxW {(int)_width / 8};
        int halfboxH {(int)_height / 8};

        if (_mouseX < centerW - halfboxW ||
            _mouseX > centerW + halfboxW ||
            _mouseY < centerH - halfboxH ||
            _mouseY > centerH + halfboxH)
        {
            SDL_WarpMouseInWindow(win, centerW, centerH);
            _mouseX = centerW;
            _mouseY = centerH;
        }
    }

    void Camera3D::changeProjection()
    {
        _isPerspective = !_isPerspective;
        if (_isPerspective)
        {
            _projection = createPerspProjMatrix(
                (float)_width, (float)_height, NEAR, FAR, FOV
            );
        }
        else
        {
            _projection = createOrthoProjMatrix(
                (float)_width, (float)_height, NEAR_UI, FAR_UI);
        }
        _valueChanged = true;
    }

    void Camera3D::updateFov(float fov) noexcept
    {
        _projection = createPerspProjMatrix(
                (float)_width, (float)_height, NEAR, FAR, fov);
    }
    #pragma endregion
} /* LowRenderer */
