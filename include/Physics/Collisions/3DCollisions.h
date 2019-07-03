#ifndef __3D_COLLISIONS_H__
#define __3D_COLLISIONS_H__

#include "LibMaths.h"

namespace Physics::Collisions
{
    struct SegmentHit;
    struct Hit;

    typedef Core::Maths::Vec3 Vec3;
    typedef Core::Maths::Plane Plane;
    typedef Core::Maths::Segment Segment;
    typedef Core::Maths::OBox OBox;
    typedef Core::Maths::Quad Quad;
    typedef Core::Maths::Sphere Sphere;
    typedef Core::Maths::Cylinder Cylinder;
    typedef Core::Maths::Capsule Capsule;
    typedef Core::Maths::AABB AABB;

    bool sphereOBox   (const Sphere& sph,  const OBox& b) noexcept;
    bool sphereSphere (const Sphere& sph1,  const Sphere& sph2) noexcept;
    bool oBoxOBox     (const OBox& b1,     const OBox& b2) noexcept;
    bool isAxeSeperating(Vec3* p1, Vec3* p2, const Vec3& n) noexcept;
    
    bool segmentPlane (const Segment& seg, const Plane& p,    SegmentHit*& hit) noexcept;
    bool segmentQuad  (const Segment& seg, const Quad& q,     SegmentHit*& hit) noexcept;
    bool segmentSphere(const Segment& seg, const Sphere& sph, SegmentHit*& hit) noexcept;
    
    bool segmentInfiniteCylinder(const Segment& seg, const Cylinder& cyl, SegmentHit*& hit) noexcept;
    bool segmentFiniteCylinder  (const Segment& seg, const Cylinder& cyl, SegmentHit*& hit) noexcept;
    void segmentFiniteCylinderPlaneP(const Segment& seg, const Cylinder& cyl, const Plane& planeP, SegmentHit*& hit, float sqrRadius) noexcept;
    void segmentFiniteCylinderPlaneQ(const Segment& seg, const Cylinder& cyl, const Plane& planeQ, SegmentHit*& hit, float sqrRadius) noexcept;
    void segmentFiniteCylinderInfCyl(const Segment& seg, const Cylinder& cyl, SegmentHit*& hit, const Vec3& PQ) noexcept;

    bool segmentCapsule           (const Segment& seg, const Capsule& cap, SegmentHit*& hit) noexcept;
    bool segmentCapsuleInfiniteHit(const Segment& seg, const Capsule& cap, SegmentHit*& hit, SegmentHit*& currentHit) noexcept;
    bool segmentCapsuleOuterSphere(const Segment& seg, const Capsule& cap, SegmentHit*& hit) noexcept;

    bool segmentAABB(const Segment& seg, const AABB& aabb, SegmentHit*& hit) noexcept;
    void segmentAABBx(const Segment& seg, const AABB& aabb, SegmentHit*& hit, const Vec3& ab) noexcept;
    void segmentAABBy(const Segment& seg, const AABB& aabb, SegmentHit*& hit, const Vec3& ab) noexcept;
    void segmentAABBz(const Segment& seg, const AABB& aabb, SegmentHit*& hit, const Vec3& ab) noexcept;

    bool segmentOrientedBox(const Segment& seg, const OBox& b, SegmentHit*& hit) noexcept;
    void segmentOrientedBoxX(const Segment& seg, const OBox& b, SegmentHit*& hit, const Vec3& ab) noexcept;
    void segmentOrientedBoxY(const Segment& seg, const OBox& b, SegmentHit*& hit, const Vec3& ab) noexcept;
    void segmentOrientedBoxZ(const Segment& seg, const OBox& b, SegmentHit*& hit, const Vec3& ab) noexcept;

    float sqrDistanceFromPointToSegment(const Segment& s, const Vec3& point) noexcept;
    float sqrDistanceFromPointToLine   (const Vec3& l1, const Vec3& l2, const Vec3& point) noexcept;
    Vec3  closestPointOnSegment        (const Segment& s, const Vec3& point) noexcept;
    bool  quadraticSolver(float a, float b, float c, float& result) noexcept;
  
    bool movingSphereStaticBox(const OBox& box ,const Sphere& sph, const Vec3& speedSph, 
        float deltaTime, SegmentHit*& segmentHit) noexcept;
    void movingSphereStaticBoxUpdateOverplanes(const OBox& box, const Vec3& point, bool* overPlanes) noexcept;
    bool movingSphereStaticBoxCapsule(const OBox& box ,float sphRadius, SegmentHit*& hit,
        const Segment& ab, bool* overPlanes) noexcept;
    void findFirstHit(SegmentHit*& hit, SegmentHit*& currentHit) noexcept;
    Vec3 movingSphereStaticBox(bool* overPlanes,const OBox& box) noexcept;

    bool movingSphereStaticSphere(const Sphere& movingSph , Sphere staticSph, const Vec3& speed, 
        float deltaTime, SegmentHit*& segmentHit) noexcept;
} // namespace Core::Physics::Collisions

#endif //__3D_COLLISIONS_H__
