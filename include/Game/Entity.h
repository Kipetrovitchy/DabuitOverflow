#ifndef __Entity_H__
#define __Entity_H__

#include "LibMaths.h"
#include "GameObject.h"
#include "Model.h"
#include "Shader.h"
#include "Transform.h"
#include "Scene.h"
#include "ResourcesManager.h"

#define ENTITY_MAXLIFE 100.0f

namespace Game
{
    #pragma region Typedefs
    typedef LowRenderer::GameObject     GameObject;
    typedef Resources::Model            Model;
    typedef Resources::Shader           Shader;
    typedef Physics::Transform          Transform;
    typedef Resources::Scene            Scene;
    typedef Resources::ResourcesManager ResourcesManager;
    typedef Core::Maths::Vec3           Vec3;
    #pragma endregion

    class Entity : public GameObject
    {
        protected:
            #pragma region Attributes
            bool  _isDead;
            float _life;
            float _maxLife;
            #pragma endregion
    
        public:
            #pragma region Constructors
            Entity();
            Entity(const Entity& e);
            Entity(const std::string& name, Model* m, Shader* s, const Transform& tr);
            Entity(const std::string& name, Model* m, Shader* s, const Transform& tr, 
                float maxLife);
            Entity(const std::string& name, Model* m, Shader* s, const Transform& tr, 
                float maxLife, float currentLife);
            virtual ~Entity() = default;
            #pragma endregion

            #pragma region Accessors
            inline float    life() const noexcept {return _life;};
            inline float&   life() noexcept {return _life;};
            inline float    maxLife() const noexcept {return _maxLife;};
            inline float&   maxLife() noexcept {return _maxLife;};
            #pragma endregion
    
            #pragma region Operators
            Entity& operator=(const Entity& e);
            #pragma endregion
    
            #pragma region Functions
            inline bool isDead() noexcept { return _life <= 0; };
            virtual Entity& takeDamage(float f) noexcept;
            virtual Entity& regainHealth(float f) noexcept;
            virtual Vec3 getHeadPosition() noexcept;

            bool struckByBullet(Scene& scene,
                                const Core::Maths::Vec3& collPoint, 
                                float damage) noexcept override;
            GameObject& save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept override;
            #pragma endregion
    };

} // namespace Game

#endif //__Entity_H__