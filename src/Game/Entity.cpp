#include "Entity.h"
#include "Impact.h"

namespace Game
{
    #pragma region Constructor
    Entity::Entity() : 
        GameObject(),
        _life { ENTITY_MAXLIFE },
        _maxLife { ENTITY_MAXLIFE }
    {}

    Entity::Entity(const Entity& e) : 
        GameObject(e),
        _life { e._life },
        _maxLife { e._maxLife }
    {}

    Entity::Entity(const std::string& name, Model* m, Shader* s, const Transform& tr) : 
        GameObject(name, m, s, tr),
        _life { ENTITY_MAXLIFE },
        _maxLife { ENTITY_MAXLIFE }
    {}

    Entity::Entity(const std::string& name, Model* m, Shader* s, const Transform& tr, 
        float maxLife) : 
        GameObject(name, m, s, tr),
        _life { maxLife }, 
        _maxLife { maxLife }
    {}

    Entity::Entity(const std::string& name, Model* m, Shader* s, const Transform& tr, 
        float maxLife, float currentLife) : 
        GameObject(name, m, s, tr),
        _life { currentLife }, 
        _maxLife { maxLife }
    {}
    #pragma region 

    #pragma region Operator
    Entity& Entity::operator=(const Entity& e)
    {
        GameObject::operator=(e);
        _life = e._life;
        _maxLife = e._maxLife;

        return *this;
    }
    #pragma endregion

    #pragma region Fonctions
    Entity& Entity::takeDamage(float f) noexcept
    {
        _life -= f;
        if (_life <= 0)
            _life = 0;


        return *this;
    }

    Entity& Entity::regainHealth(float f) noexcept
    {
        _life += f;
        if (_life > _maxLife)
            _life = _maxLife;

        return *this;
    }
    
    Vec3 Entity::getHeadPosition() noexcept
    {
        Vec3 head = _transform.position();
        head.y += _transform.scale().y / 2.0f;

        return head;
    }

    bool Entity::struckByBullet(Scene& scene,
                                const Core::Maths::Vec3& collPoint, 
                                float damage) noexcept
    {
        takeDamage(damage);
        if (_life == 0)
            scene.remove(this);

        Core::Maths::Mat worldToLoc = _transform.worldToLocal();

        addChild(new Impact("ball impact",
			Model::createCube(scene.resourcesManager(), "resources/Bullet/impact.png"),
			scene.resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
			{worldToLoc * collPoint, Vec3::zero, {0.05f, 0.05f, 0.05f}}));

        return true;
    }
    
    GameObject& Entity::save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept
    {
        GameObject::saveGameObject(fs, resourcesManager);
        fs << "," << 1 <<  "," << _maxLife << "," << _life << "," << 0 << "," << 0 << "\n";
        GameObject::saveChildren(fs, resourcesManager, folderPath);
        return *this;
    }

    #pragma endregion
} // namespace Game
