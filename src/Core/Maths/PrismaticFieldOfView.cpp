#include "PrismaticFieldOfView.h"

#include <cmath>

namespace Core::Maths
{
    #pragma region Constructors
    PrismaticFieldOfView::PrismaticFieldOfView():
        m_position  { Vec3::zero },
        m_front     { Vec3::forward },
        m_angle     { M_PI / 2.0f },
        m_distance  { 5.0f },
        m_height    { 2.0f }
    {
        computeUp();
    }

    PrismaticFieldOfView::PrismaticFieldOfView(
        const Vec3& position,
        const Vec3& front,
        float angle,
        float distance,
        float height):
        m_position  { position },
        m_front     { front.unit() },
        m_angle     { angle },
        m_distance  { distance },
        m_height    { height }
    {
        computeUp();
        computePlanes();
    }
    #pragma endregion

    #pragma region Functions
    void PrismaticFieldOfView::computeUp()
    {
        // Compute the right vector
        Vec3 right = m_front.cross(Vec3::up);

        // To get the up direction of the front
        m_up = right.cross(m_front).unit();
    }

    void PrismaticFieldOfView::computePlanes()
    {
        // The plane up is at height / 2 upper than the position and pointing downward
        m_planeUp    = Plane(m_position + m_up * (m_height / 2.0f), -m_up);
        // The plane down is at height / 2 lower than the position and pointing forward
        m_planeDown  = Plane(m_position - m_up * (m_height / 2.0f),  m_up);
        // The plane front is at the distance from the position pointing to the player
        m_planeFront = Plane(m_position + m_front * m_distance, -m_front);

        // Rotate the front to the right to get the normal of the left plane
        Vec3 leftNorm = Mat::createRotation(m_up, (M_PI / 2.0f - m_angle / 2.0f))
                        * m_front;
        m_planeLeft  = Plane(m_position, leftNorm);

        // Rotate the front to the left to get the normal of the right plane
        Vec3 rightNorm = Mat::createRotation(m_up,-(M_PI / 2.0f - m_angle / 2.0f))
                        * m_front;
        m_planeRight = Plane(m_position, rightNorm);
    }

    bool PrismaticFieldOfView::canSee(const Vec3& point) const
    {
        return  m_planeUp.getSide(point) &&
                m_planeDown.getSide(point) &&
                m_planeFront.getSide(point) &&
                m_planeRight.getSide(point) &&
                m_planeLeft.getSide(point);
    }

    void PrismaticFieldOfView::moveToPosition(const Vec3& point)
    {
        m_position = point;
        computePlanes();
    }

    void PrismaticFieldOfView::changeOrientation(const Vec3& front)
    {
        m_front = front;
        computeUp();
        computePlanes();
    }
    #pragma endregion
} /* Maths */
