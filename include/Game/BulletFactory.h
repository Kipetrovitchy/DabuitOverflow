#ifndef __BULLET_FACTORY_H__
#define __BULLET_FACTORY_H__

#include "Bullet.h"

#define PATH_VERTEX "resources/Shaders/model3D.vs"
#define PATH_FRAGMENT "resources/Shaders/model3D.fs"

enum class BulletType
{
    NONE = 0,

    SMG,
    RIFLE,
    PISTOL,
    ASSAULT,
    SHOTGUN,
    EXPLOSIVE,
    
    COUNT
};

namespace Resources
{
    class Scene;
}

namespace Game
{
    typedef Resources::Scene    Scene;
    
    Bullet* createBullet(Scene& scn, const BulletType& type, Entity* owner,
                         float damage) noexcept;
}

#endif//__BULLET_TYPE_H__