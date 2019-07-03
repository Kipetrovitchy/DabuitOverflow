#include "BulletFactory.h"

#include "LibMaths.h"

namespace Game
{
    Bullet* createBullet(Scene& scn, const BulletType& type, Entity* owner,
                         float damage) noexcept
    {
        switch (type)
        {
            case BulletType::RIFLE:
            {
                return new Bullet(
                    scn.resourcesManager()->getModel("resources/Bullet/bullet.obj"),
			        scn.resourcesManager()->getShader(PATH_VERTEX, PATH_FRAGMENT),
			        {Vec3::zero, Vec3::zero, {0.1f, 0.1f, 0.1f}},
                    owner, damage);
            }
            case BulletType::PISTOL:
            {
                return new Bullet(
                    scn.resourcesManager()->getModel("resources/Bullet/bullet.obj"),
			        scn.resourcesManager()->getShader(PATH_VERTEX, PATH_FRAGMENT),
			        {Vec3::zero, Vec3::zero, {0.1f, 0.1f, 0.1f}},
                    owner, damage);
            }
            case BulletType::SHOTGUN:
            {
                return new Bullet(
                    scn.resourcesManager()->getModel("resources/Bullet/bullet.obj"),
			        scn.resourcesManager()->getShader(PATH_VERTEX, PATH_FRAGMENT),
			        {Vec3::zero, Vec3::zero, {0.1f, 0.1f, 0.1f}},
                    owner, damage);
            }
            case BulletType::SMG:
            {
                return new Bullet(
                    scn.resourcesManager()->getModel("resources/Bullet/bullet.obj"),
			        scn.resourcesManager()->getShader(PATH_VERTEX, PATH_FRAGMENT),
			        {Vec3::zero, Vec3::zero, {0.1f, 0.1f, 0.1f}},
                    owner, damage);
            }
            case BulletType::EXPLOSIVE:
            {
                return new Bullet(
                    scn.resourcesManager()->getModel("resources/Sphere/sphere.obj"),
			        scn.resourcesManager()->getShader(PATH_VERTEX, PATH_FRAGMENT),
			        {Vec3::zero, Vec3::zero, {0.1f, 0.1f, 0.1f}},
                    owner, damage);
            }
            default: return nullptr;
        }
    }
} // Game
