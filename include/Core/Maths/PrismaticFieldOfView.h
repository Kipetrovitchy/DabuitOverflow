#ifndef __PRISMATIC_FIELD_OF_VIEW_H__
#define __PRISMATIC_FIELD_OF_VIEW_H__

#include "FieldOfView.h"
#include "Plane.h"
#include "Vec3.h"

namespace Core::Maths
{
    class PrismaticFieldOfView : public FieldOfView
    {
    private:
        #pragma region Attributes
        Vec3    m_position;
        Vec3    m_front;
        float   m_angle;
        float   m_distance;
        float   m_height;
        
        Vec3    m_up;
        Plane   m_planeUp;
        Plane   m_planeDown;
        Plane   m_planeFront;
        Plane   m_planeRight;
        Plane   m_planeLeft;
        #pragma endregion

        #pragma region Functions
        void computeUp();
        void computePlanes();
        #pragma endregion

    public:
        #pragma region Constructors
        PrismaticFieldOfView();
        PrismaticFieldOfView(
            const Vec3& position,
            const Vec3& front,
            float angle,
            float distance,
            float height);
        ~PrismaticFieldOfView() = default;
        #pragma endregion

        #pragma region Functions
        bool canSee(const Vec3& point) const override;
        void moveToPosition(const Vec3& point);
        void changeOrientation(const Vec3& front);
        #pragma endregion

        #pragma region Accessors
        inline  Vec3&   getPosition()   { return m_position; };
        inline  Vec3&   getFront()      { return m_front; };
        inline  float&  getAngle()      { return m_angle; };
        inline  float&  getDistance()   { return m_distance; };
        inline  float&  getHeight()     { return m_height; };
        inline  Vec3&   getUp()         { return m_up; };
        inline  Plane&  getPlaneUp()    { return m_planeUp; };        
        inline  Plane&  getPlaneDown()  { return m_planeDown; };        
        inline  Plane&  getPlaneFront() { return m_planeFront; };        
        inline  Plane&  getPlaneRight() { return m_planeRight; };        
        inline  Plane&  getPlaneLeft()  { return m_planeLeft; };        
        #pragma endregion
    };
} /* Maths */

#endif
