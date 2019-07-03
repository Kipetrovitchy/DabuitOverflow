#include "3DCollisions.h"
#include "SegmentHit.h"
#include "Transform.h"
#include "Hit.h"

#include <algorithm>
#include <cmath>
#include <cfloat>

namespace Physics::Collisions
{
    typedef Core::Maths::Mat Mat;
    typedef Core::Maths::Range Range;

    bool sphereOBox (const Sphere& sph,  const OBox& b) noexcept
    {
        // Get the local position of the sphere in the box referential
        Vec3 sphLocal { Transform::worldToLocal(b.origin) * sph.origin };

        // If the Box and the AABB of the sphere aren't colliding there's no intersection
        if (std::abs(sphLocal.x) > b.halfW + sph.radius ||
            std::abs(sphLocal.y) > b.halfH + sph.radius ||
            std::abs(sphLocal.z) > b.halfD + sph.radius)
            return false;

        // Get the closest point on the Box to the sphere
        Vec3 closestPoint {
            std::clamp(sphLocal.x, -b.halfW, b.halfW),
            std::clamp(sphLocal.y, -b.halfH, b.halfH),
            std::clamp(sphLocal.z, -b.halfD, b.halfD)
        };

        return (sphLocal - closestPoint).squaredLength() < sph.radius * sph.radius;
    }

    bool sphereSphere (const Sphere& sph1,  const Sphere& sph2) noexcept
    {
        Vec3 sph1ToSph2 {sph1.origin, sph2.origin};
        float sqrtDistance {sph1ToSph2.squaredLength()};
        float collisionDistance {sph1.radius + sph2.radius};
        
        if (sqrtDistance <= collisionDistance * collisionDistance)
            return true;
        return false;
    }

    bool oBoxOBox (const OBox& b1, const OBox& b2) noexcept
    {
        // Get all the points of the boxes
        Vec3* p1 = b1.getAllPoints();
        Vec3* p2 = b2.getAllPoints();
        AABB aabb1 = b1.getAABBFromPoints(p1);
        AABB aabb2 = b2.getAABBFromPoints(p2);

        if (std::abs(aabb1.origin.x - aabb2.origin.x) > aabb1.halfW + aabb2.halfW ||
            std::abs(aabb1.origin.y - aabb2.origin.y) > aabb1.halfH + aabb2.halfH ||
            std::abs(aabb1.origin.z - aabb2.origin.z) > aabb1.halfD + aabb2.halfD)
        {
            delete p1;
            delete p2;

            return false;
        }

        bool res = !(isAxeSeperating(p1, p2, b1.origin.i) ||
                     isAxeSeperating(p1, p2, b1.origin.j) ||
                     isAxeSeperating(p1, p2, b1.origin.k) ||
                     isAxeSeperating(p1, p2, b2.origin.i) ||
                     isAxeSeperating(p1, p2, b2.origin.j) ||
                     isAxeSeperating(p1, p2, b2.origin.k) ||
                     isAxeSeperating(p1, p2, b1.origin.i.cross(b2.origin.i)) ||
                     isAxeSeperating(p1, p2, b1.origin.i.cross(b2.origin.j)) ||
                     isAxeSeperating(p1, p2, b1.origin.i.cross(b2.origin.k)) ||
                     isAxeSeperating(p1, p2, b1.origin.j.cross(b2.origin.i)) ||
                     isAxeSeperating(p1, p2, b1.origin.j.cross(b2.origin.j)) ||
                     isAxeSeperating(p1, p2, b1.origin.j.cross(b2.origin.k)) ||
                     isAxeSeperating(p1, p2, b1.origin.k.cross(b2.origin.i)) ||
                     isAxeSeperating(p1, p2, b1.origin.k.cross(b2.origin.j)) ||
                     isAxeSeperating(p1, p2, b1.origin.k.cross(b2.origin.k)));
        delete p1;
        delete p2;
        return res;
    }

    bool isAxeSeperating(Vec3* p1, Vec3* p2, const Vec3& n) noexcept
    {
        // Create the ranges of the boxes
        Range r1, r2;

        // Go through all the points and update the ranges
        for (int idx = 0; idx < 8; ++idx)
        {
            r1.update(p1[idx].dot(n));
            r2.update(p2[idx].dot(n));
        }

        // Check if the ranges are overlapping
        return !r1.isOverlapping(r2);
    }

    bool segmentPlane (const Segment& seg, const Plane& p, SegmentHit*& hit) noexcept
    {
        // Get the vector of the segment
        Vec3 AB      { seg.b - seg.a };
        float ABdotN { AB.dot(p.n) };

        // If AB is colinear to the plane there is no collision
        if (ABdotN <= FLT_EPSILON && ABdotN >= -FLT_EPSILON)
            return false;

        float t { (p.d - seg.a.dot(p.n)) / ABdotN };
        // If the segment doesn't touch the plane
        if (t < 0.0f || t > 1.0f)
            return false;

        // Get the hit
        hit = new SegmentHit();
        // If the segment is in the same direction as the plane normal
        if (ABdotN > 0.0f)
            hit->normal = -p.normal;
        else
            hit->normal = p.normal;

        // Get the intersection
        hit->intersection = seg.a + AB * t;
        hit->t = t;
        return true;
    }

    bool segmentQuad (const Segment& seg, const Quad& q, SegmentHit*& hit) noexcept
    {
        // Create the plane from the quad
        Plane p(q.origin.origin, q.origin.j);

        // Get the intersection between the plane and the segment
        SegmentHit* h { nullptr };
        if (!segmentPlane(seg, p, h))
            return false;

        // Get the matrix world to local
        Mat wToLocMat { Physics::Transform::worldToLocal(q.origin) };
        // Get the local intersection
        Vec3 lInt     { wToLocMat * h->intersection };
        // Check if the point is in the quad
        if (lInt.x < -q.hWidth  || lInt.x > q.hWidth ||
            lInt.z < -q.hHeight || lInt.z > q.hHeight)
        {
            // delete the hit got
            delete h;
            return false;
        }

        hit = h;
        return true;
    }

    bool segmentSphere(const Segment& seg, const Sphere& sph, SegmentHit*& hit) noexcept
    {
        Vec3 AB { seg.b - seg.a };
        Vec3 CA { seg.a - sph.origin };

        float ABdotCA { AB.dot(CA) };
        // If AB is is going away from the sphere
        if (ABdotCA > 0.0f)
            return false;

        float sqrRadius { sph.radius * sph.radius };
        float sqrLenCA  { CA.squaredLength() };
        // If A is within the sphere
        if (sqrLenCA < sqrRadius)
            return false;

        // Get the t for the intersection
        float t, a { AB.squaredLength() },
                 b { 2.0f * ABdotCA },
                 c { sqrLenCA - sqrRadius };
        // If there's a solution to the equation
        if (!quadraticSolver(a, b, c, t))
            return false;
        // Check if the point is on the segment
        if (t < 0.0f || t > 1.0f)
            return false;

        hit = new SegmentHit();
        hit->intersection = seg.a + AB * t;
        hit->normal = (hit->intersection - sph.origin).unit();
        hit->t = t;
        return true;
    }

    bool segmentInfiniteCylinder(const Segment& seg, const Cylinder& cyl, SegmentHit*& hit) noexcept
    {
        Vec3 PQ { cyl.q - cyl.p }, PA { seg.a - cyl.p };

        // Get the projection of A on the line PQ
        PQ.unit();
        Vec3  ProjA       { cyl.p + PQ * PQ.dot(PA) };
        float sqrRadius   { cyl.radius * cyl.radius };
        // Check if A is within the cylinder
        if ((ProjA - seg.a).squaredLength() < sqrRadius)
            return false;

        Vec3 AB    { seg.b - seg.a };
        Vec3 PAxPQ { PA.cross(PQ) };
        Vec3 ABxPQ { AB.cross(PQ) };
        // If AB is colinear to PQ
        if (ABxPQ.equals(Vec3::zero, std::numeric_limits<float>::epsilon()))
            return false;

        float t, a { ABxPQ.squaredLength() },
                 b { 2.0f * PAxPQ.dot(ABxPQ) },
                 c { PAxPQ.squaredLength() - sqrRadius };
        // If there's a solution to the equation
        if (!quadraticSolver(a, b, c, t))
            return false;
        // Check that the point belongs to the segment
        if (t < 0.0f || t > 1.0f)
            return false;

        hit = new SegmentHit();
        hit->intersection = seg.a + AB * t;
        // Project the point on PQ and get the direction from the line to the intersection
        hit->normal = (hit->intersection - PQ * PQ.dot(hit->intersection)).unit();
        hit->t = t;
        return true;
    }

    bool segmentFiniteCylinder  (const Segment& seg, const Cylinder& cyl, SegmentHit*& hit) noexcept
    {
        Vec3 PQ { cyl.q - cyl.p };
        Vec3 PA { seg.a - cyl.p };
        float ta        { PQ.dot(PA) / PQ.squaredLength() };
        float sqrRadius { cyl.radius * cyl.radius };
        // Check that the projection of A isn't within bounderies of P and Q
        if (ta >= 0.0f && ta <= 1.0f)
        {
            // Check that A is not inside the finite cylinder
            Vec3 projA { cyl.p + PQ * ta };
            if ((projA - seg.a).squaredLength() < sqrRadius)
                return false;
        }

        // If A and B are on the top side of the plane P
        Plane planeP(cyl.p, -PQ);
        if (planeP.getSide(seg.a) > 0.0f && planeP.getSide(seg.b) > 0.0f)
            return false;
        // If A and B are on the top side of the plane Q
        Plane planeQ(cyl.q,  PQ);
        if (planeQ.getSide(seg.a) > 0.0f && planeQ.getSide(seg.b) > 0.0f)
            return false;

        segmentFiniteCylinderPlaneP(seg, cyl, planeP, hit, sqrRadius);
        segmentFiniteCylinderPlaneQ(seg, cyl, planeQ, hit, sqrRadius);
        segmentFiniteCylinderInfCyl(seg, cyl, hit, PQ);

        return hit != nullptr;
    }

    void segmentFiniteCylinderPlaneP(const Segment& seg, const Cylinder& cyl, 
        const Plane& planeP, SegmentHit*& hit, float sqrRadius) noexcept
    {
        SegmentHit* currentHit { nullptr };
        // Get the intersection between the plane and the segment
        if (segmentPlane(seg, planeP, currentHit))
        {
            // If the intersection is in the circle described by the cylinder
            if ((currentHit->intersection - cyl.p).squaredLength() < sqrRadius)
                hit = currentHit;
            // If not we don't need the current hit
            else
                delete currentHit;
        }
    }

    void segmentFiniteCylinderPlaneQ(const Segment& seg, const Cylinder& cyl, 
        const Plane& planeQ, SegmentHit*& hit, float sqrRadius) noexcept
    {
        SegmentHit* currentHit { nullptr };
        if (segmentPlane(seg, planeQ, currentHit))
        {
            if ((currentHit->intersection - cyl.q).squaredLength() < sqrRadius)
            {
                if (hit)
                {
                    // Get the t with the lowest t
                    if (currentHit->t < hit->t)
                    {
                        delete hit;
                        hit = currentHit;
                    }
                    else
                        delete currentHit;
                }
                else
                    hit = currentHit;
            }
            else
                delete currentHit;
        }
    }

    void segmentFiniteCylinderInfCyl(const Segment& seg, const Cylinder& cyl, 
        SegmentHit*& hit, const Vec3& PQ) noexcept
    {
        SegmentHit* currentHit { nullptr };
        if (segmentInfiniteCylinder(seg, cyl, currentHit))
        {
            // Check if the point is within the cylinder
            float PQdotPM { PQ.dot(currentHit->intersection - cyl.p) };
            if (PQdotPM >= 0.0f && PQdotPM <= 1.0f)
            {
                if (hit)
                {
                    // Get the t with the lowest t
                    if (currentHit->t < hit->t)
                    {
                        delete hit;
                        hit = currentHit;
                    }
                    else
                        delete currentHit;
                }
                else
                    hit = currentHit;
            }
            else
                delete currentHit;
        }
    }

    bool segmentCapsule(const Segment& seg, const Capsule& cap, SegmentHit*& hit) noexcept
    {
        Segment segPQ(cap.p, cap.q);
        float sqrRadius { cap.radius * cap.radius };
        // If A is inside the capsule return
        if (sqrDistanceFromPointToSegment(segPQ, seg.a) < sqrRadius)
            return false;

        SegmentHit* currentHit = nullptr;
        // Get the intersection between the infinite cylinder and the segment
        if (segmentInfiniteCylinder(seg, {cap.p, cap.q, cap.radius}, currentHit))
            return segmentCapsuleInfiniteHit(seg, cap, hit, currentHit);
        else
            return segmentCapsuleOuterSphere(seg, cap, hit);
    }

    bool segmentCapsuleInfiniteHit(const Segment& seg, const Capsule& cap, 
        SegmentHit*& hit, SegmentHit*& currentHit) noexcept
    {
        Vec3 PQ { cap.q - cap.p };

        // Get the quantity of projection of the intersection on PQ
        float tm = PQ.dot(currentHit->intersection - cap.p) / PQ.squaredLength();
        // If it is at the bottom of the capsule do collision with the sphere P
        if (tm < 0.0f)
        {
            delete currentHit;
            return segmentSphere(seg, { cap.p, cap.radius }, hit);
        }
        // If it is at the top of the capsule do collision with the sphere Q
        else if (tm > 1.0f)
        {
            delete currentHit;
            return segmentSphere(seg, { cap.q, cap.radius }, hit);
        }
        else
        {
            hit = currentHit;
            return true;
        }

        return false;
    }

    bool segmentCapsuleOuterSphere (const Segment& seg, const Capsule& cap, SegmentHit*& hit) noexcept
    {
        // We do the intersection with the closest sphere
        if ((cap.p - seg.a).squaredLength() < (cap.q - seg.a).squaredLength())
        {
            // P is the closest
            return segmentSphere(seg, { cap.p, cap.radius }, hit);
        }
        else
        {
            // Q is the closest
            return segmentSphere(seg, { cap.q, cap.radius }, hit);
        }
    }

    bool quadraticSolver(float a, float b, float c, float& result) noexcept
    {
        float delta { b*b - 4.0f * a * c };

        if      (delta < -std::numeric_limits<float>::epsilon()) // delta < 0
        {
            return false;
        }
        else if (delta <= std::numeric_limits<float>::epsilon()) // delta = 0
        {
            result = (-b) / (2.0f * a);
        }
        else                                                     // delta > 0
        {
            result = std::min<float>((-b + std::sqrt(delta)) / (2.0f * a),
                                     (-b - std::sqrt(delta)) / (2.0f * a));
        }

        return true;
    }

    Vec3  closestPointOnSegment (const Segment& s, const Vec3& point)  noexcept
    {
        Vec3 AB = s.b - s.a;
        Vec3 AP = point - s.a;

        // Get the projection of the point on the segment
        float t = AB.dot(AP) / AB.squaredLength();

        // If the projection is lower than the segment return start of the segment
        if (t < 0.f)
            return s.a;
        // If the projection is higher than the segment return start of the segment
        else if (t > 1.f)
            return s.b;
        // Get the point on the segment using the projection
        else
            return s.a + AB * t;
    }

    float sqrDistanceFromPointToSegment(const Segment& s, const Vec3& point) noexcept
    {
        // Get the vectors
        Vec3 AB = s.b - s.a;
        Vec3 AP = point - s.a;

        // Get the projection of the point on the segment
        float t = AB.dot(AP) / AB.squaredLength();

        Vec3 P;
        // If the projection is lower than the segment return start of the segment
        if (t < 0.f)
            P = s.a;
        // If the projection is higher than the segment return start of the segment
        else if (t > 1.f)
            P = s.b;
        // Get the point on the segment using the projection
        else
            P = s.a + AB * t;

        return (P - point).squaredLength();
    }

    float sqrDistanceFromPointToLine(const Vec3& l1, const Vec3& l2, const Vec3& point) noexcept
    {
        Vec3 AB = l2 - l1;
        AB.unit();
        Vec3 AP = point - l1;

        return (AB.cross(AP)).squaredLength();
    }

    bool segmentOrientedBox(const Segment& seg, const OBox& box, SegmentHit*& hit) noexcept
    {
        if (box.pointIsIn(seg.a))
            return false;

        Mat worldToLocal { Physics::Transform::worldToLocal(box.origin) };
        Segment segLoc   { worldToLocal * seg.a , worldToLocal * seg.b };

        //The AB vector
        Vec3 ab {segLoc.b - segLoc.a};

        if (segmentAABB(segLoc, box.getLocalAABB(), hit))
        {
            Mat localToWorld { Physics::Transform::localToWorld(box.origin) };
            hit->intersection = localToWorld * hit->intersection;
            hit->normal = localToWorld * hit->normal - box.origin.origin;
            return true;
        }
        return false;
    }

    bool segmentAABB(const Segment& seg, const AABB& aabb, SegmentHit*& hit) noexcept
    {
        if (aabb.pointIsIn(seg.a))
            return false;
        
        //The AB vector        
        Vec3 ab {seg.b - seg.a};

        //We study the direction of AB of each axis to determined the quads that could collide with the segment
        segmentAABBx(seg, aabb, hit, ab);
        segmentAABBy(seg, aabb, hit, ab);
        segmentAABBz(seg, aabb, hit, ab);

        return hit != nullptr;
    }

    void segmentAABBx(const Segment& seg, const AABB& aabb, SegmentHit*& hit, const Vec3& ab) noexcept
    {
        SegmentHit* currentHit {nullptr};
        if (ab.x < 0)
        //If the segment is heading towards negative x then it can't collide with the left quad first
        {
            if (segmentQuad(seg, aabb.quadRight(), currentHit))
            {
                hit = currentHit;
            }
        }
        else if (ab.x > 0)
        {
            if (segmentQuad(seg, aabb.quadLeft(), currentHit))
            {
                hit = currentHit;
            }
        }
    }

    void segmentAABBy(const Segment& seg, const AABB& aabb, SegmentHit*& hit, const Vec3& ab) noexcept
    {
        SegmentHit* currentHit {nullptr};
        //If the segment is heading towards negative x then it can't collide with the bottom quad first
        if (ab.y < 0)
        {
            if (segmentQuad(seg, aabb.quadTop(), currentHit))
                findFirstHit(hit, currentHit);
        }
        else if (ab.y > 0)
        {
            if (segmentQuad(seg, aabb.quadBottom(), currentHit))
                findFirstHit(hit, currentHit);
        }
    }

    void segmentAABBz(const Segment& seg, const AABB& aabb, SegmentHit*& hit, const Vec3& ab) noexcept
    {
        SegmentHit* currentHit {nullptr};
        //If the segment is heading towards negative x then it can't collide with the back quad first
        if (ab.z < 0)
        {
            if (segmentQuad(seg, aabb.quadFront(), currentHit))
                findFirstHit(hit, currentHit);
        }
        else if (ab.z > 0)
        {
            if (segmentQuad(seg, aabb.quadBack(), currentHit))
                findFirstHit(hit, currentHit);
        }
    }

    bool movingSphereStaticBox(const OBox& box ,const Sphere& sph, const Vec3& speedSph,
        float deltaTime, SegmentHit*& segmentHit) noexcept
    {
        //Calulus of B and creation of the vector AB
        Vec3 b {sph.origin + (speedSph * deltaTime)};
        Segment ab {sph.origin, b};

        //Creation of the OBB
        OBox obb {box};
        obb.halfD += sph.r;
        obb.halfH += sph.r;
        obb.halfW += sph.r;

        if (!segmentOrientedBox(ab, obb, segmentHit) && !obb.pointIsIn(sph.origin))
            return false;

        //Front - Back - Top - Bottom - Left - Right
        bool overPlanes[6] {false, false, false, false, false, false};
        int count {0};
        
        //If the segment doesn't collide with the OBB it will not collide with the cube
        const Vec3& point = (segmentHit == nullptr) ? sph.origin : segmentHit->intersection;
        movingSphereStaticBoxUpdateOverplanes(box, point, overPlanes);

        //Look how much planes are under the point
        for (bool b : overPlanes)
            if (b)
                count++;


        if (segmentHit)
        {
            //collides with only one of the faces
            if (count == 1)
                return true;

            delete segmentHit;
            segmentHit = nullptr;
        }

        //test collision with the needed capsules
        if (movingSphereStaticBoxCapsule(box, sph.radius, segmentHit, ab, overPlanes))
            return true;

        //The sphere at its next step position
        Sphere sphPlusOne {sph};
        sphPlusOne.origin = b;
        
        //Takes care of the case were the sphere is in the OBB but collides with the box
        if (sphereOBox(sphPlusOne, box))
        {
            segmentHit = new SegmentHit;
            segmentHit->intersection = sph.origin;
            segmentHit->normal = movingSphereStaticBox(overPlanes, box);
            segmentHit->t = 1.0f;

            return true;
        }
        return false;
    }

    Vec3 movingSphereStaticBox(bool* overPlanes, const OBox& box) noexcept
    {
        Vec3 norm {0.f};

        if (overPlanes[0])
            norm += box.planeFront().normal;
        if (overPlanes[1])
            norm += box.planeBack().normal;
        if (overPlanes[2])
            norm += box.planeTop().normal;
        if (overPlanes[3])
            norm += box.planeBottom().normal;
        if (overPlanes[4])
            norm += box.planeLeft().normal;
        if (overPlanes[5])
            norm += box.planeRight().normal;

        return norm.unit();
    }

    void movingSphereStaticBoxUpdateOverplanes(const OBox& box, const Vec3& point, bool* overPlanes) noexcept
    {
        //Calculate for each plane of the box if the point of intersection found is over it
        if (box.planeFront().getSide(point) > 0)
            overPlanes[0] = true;
        if (box.planeBack().getSide(point) > 0)
            overPlanes[1] = true;
        if (box.planeTop().getSide(point) > 0)
            overPlanes[2] = true;
        if (box.planeBottom().getSide(point) > 0)
            overPlanes[3] = true;
        if (box.planeLeft().getSide(point) > 0)
            overPlanes[4] = true;
        if (box.planeRight().getSide(point) > 0)
            overPlanes[5] = true;
    }

    bool movingSphereStaticBoxCapsule(const OBox& box ,float sphRadius, SegmentHit*& hit,
        const Segment& ab, bool* overPlanes) noexcept
    {
        Capsule caps;
        caps.radius = sphRadius;

        SegmentHit* currentHit = nullptr;

        if (overPlanes[0] && overPlanes[5]) //Over the FRONT and RIGHT planes
        {
            caps.p = box.origin.origin + box.origin.i * box.halfW - box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW + box.origin.j * box.halfH + box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                hit = currentHit;
        }
        if (overPlanes[0] && overPlanes[4]) //Over the FRONT and LEFT planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW - box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin - box.origin.i * box.halfW + box.origin.j * box.halfH + box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[0] && overPlanes[3]) //Over the FRONT and BOTTOM planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW - box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW - box.origin.j * box.halfH + box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[0] && overPlanes[2]) //Over the FRONT and TOP planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW + box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW + box.origin.j * box.halfH + box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[1] && overPlanes[5]) //Over the BACK and RIGHT planes
        {
            caps.p = box.origin.origin + box.origin.i * box.halfW - box.origin.j * box.halfH - box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW + box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[1] && overPlanes[4]) //Over the BACK and LEFT planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW - box.origin.j * box.halfH - box.origin.k * box.halfD;
            caps.q = box.origin.origin - box.origin.i * box.halfW + box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[1] && overPlanes[3]) //Over the BACK and BOTTOM planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW - box.origin.j * box.halfH - box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW - box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[1] && overPlanes[2]) //Over the BACK and TOP planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW + box.origin.j * box.halfH - box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW + box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[3] && overPlanes[5]) //Over the BOTTOM and RIGHT planes
        {
            caps.p = box.origin.origin + box.origin.i * box.halfW - box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW - box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[3] && overPlanes[4]) //Over the BOTTOM and LEFT planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW - box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin - box.origin.i * box.halfW - box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[2] && overPlanes[5]) //Over the TOP and RIGHT planes
        {
            caps.p = box.origin.origin + box.origin.i * box.halfW + box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin + box.origin.i * box.halfW + box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        if (overPlanes[2] && overPlanes[4]) //Over the TOP and LEFT planes
        {
            caps.p = box.origin.origin - box.origin.i * box.halfW + box.origin.j * box.halfH + box.origin.k * box.halfD;
            caps.q = box.origin.origin - box.origin.i * box.halfW + box.origin.j * box.halfH - box.origin.k * box.halfD;
            if (segmentCapsule(ab, caps, currentHit))
                findFirstHit(hit, currentHit);
        }
        return (hit != nullptr);
    }


    void findFirstHit(SegmentHit*& hit, SegmentHit*& currentHit) noexcept
    {
        if (hit)
        {
            if (currentHit->t < hit->t)
            {
                delete hit;
                hit = currentHit;
            }
            else
                delete currentHit;
        }
        else
            hit = currentHit;
    }

    bool movingSphereStaticSphere(const Sphere& movingSph, Sphere staticSph, const Vec3& speed, 
        float deltaTime, SegmentHit*& hit) noexcept
    {
        if (sphereSphere(movingSph, staticSph))
        {
            hit = new SegmentHit();
            hit->normal = (movingSph.o - staticSph.o).unit();
            hit->intersection = staticSph.o + hit->n * (staticSph.radius + movingSph.radius);
            hit->t = 0.0f;

            return true; 
        }
        // Increase the radius of the other sphere
        staticSph.radius += movingSph.radius;

        // Create the segment from the center of the moving sphere to the next frame position
        Segment seg { movingSph.origin, movingSph.origin + speed * deltaTime };

        return segmentSphere(seg, staticSph, hit);
    }

} // Core::Physics::Collisions
