#include "Bullet.h"

namespace Game
{
    #pragma region Constructors
        Bullet::Bullet() : GameObject(),
            _owner  {nullptr},
            _damage {0.f}
        {
            addRigidBody(true, 1.0f);
            addCollider(Physics::Collisions::EColliderType::SPHERE, true);
        }
        Bullet::Bullet(Model* m, Shader* s, const Transform& tr, Entity* owner,
                       float damage) :
            GameObject("bullet", m, s, tr),
            _owner  {owner},
            _damage {damage}
        {
            addRigidBody(true, 1.0f);
            addCollider(Physics::Collisions::EColliderType::SPHERE, true);
        }
        Bullet::Bullet(const Bullet& copy) : GameObject(copy),
            _owner  {copy._owner},
            _damage {copy._damage}
        {}
    #pragma endregion

    #pragma region Operators
        Bullet&     Bullet::operator=(const Bullet& copy)
        {
            GameObject::operator=(copy);
            _owner      = copy._owner;

            return *this;
        }
    #pragma endregion

    #pragma region Functions
        GameObject& Bullet::update(Scene& scene, float deltaTime) noexcept
        {
            (void) scene;
            (void) deltaTime;
            return *this;
        }

        GameObject& Bullet::onTrigger(Scene& scene, Collider* collider,
                                      SegmentHit* hit) noexcept
        {
            if (collider->gameObject()->struckByBullet(scene, hit->intersection, 
                                                       _damage))
                scene.remove(this);

            return *this;
        }

        GameObject& Bullet::save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept 
        {
            (void)folderPath;
            (void)fs;
            (void)resourcesManager;
            return *this;
        }

    #pragma endregion
} // namespace Game