#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <GL/glew.h>
#include <string>

#include "InputMgr.h"
#include "LibMaths.h"

#include "Transform.h"
#include "Model.h"
#include "Shader.h"
#include "Collider.h"
#include "ColliderFactory.h"
#include "RigidBody.h"
#include "Light.h"
#include "ResourcesManager.h"

#include "SegmentHit.h"

#define PATH_VERTEX "resources/Shaders/model3D.vs"
#define PATH_FRAGMENT "resources/Shaders/model3D.fs"

namespace Resources
{
    class Scene;
}

namespace Game::Items
{
    enum class ItemType : uint;
} // namespace Game::Items


namespace LowRenderer
{
	#pragma region typedefs
    typedef Resources::Model                Model;
    typedef Resources::Shader               Shader;
    typedef Resources::Texture              Texture;
    typedef Physics::Transform              Transform;
    typedef Physics::Collider               Collider;
    typedef Physics::RigidBody              RigidBody;
    typedef Physics::Collisions::SegmentHit SegmentHit;
    typedef Core::Maths::Mat                Mat;
    typedef Core::Maths::Vec3               Vec3;
    typedef Core::Maths::Segment            Segment;
    typedef Game::Inputs::InputMgr          InputMgr;
    typedef Resources::Scene                Scene;
    typedef Resources::ResourcesManager     ResourcesManager;
    typedef Physics::Collisions::EColliderType  EColliderType;
    typedef Game::Items::ItemType               ItemType;
	#pragma endregion

    class GameObject
    {
    private:
        #pragma region Functions
        void    setLights(const std::vector<Light*>& lights);
        void    drawMaterials();
        void    renderChildren(const Mat& viewMat, const Vec3& viewPos,
                               const std::vector<Light*>& lights,
                               Mat transfromParent) noexcept;
        #pragma endregion
    
    protected:
        #pragma region Attributes
        std::string                 _name;
        bool                        _active;
        Transform                   _transform;
        Model*                      _model;
        Shader*                     _shader;
        Collider*                   _collider;
        RigidBody*                  _rigidBody;
        std::vector<GameObject*>    _children;
		#pragma endregion

    public:
		#pragma region Constructors
        GameObject();
        GameObject(Model* m, Shader* s);
        GameObject(Model* m, Shader* s, const Transform& tr);
        GameObject(const std::string& name, Model* m, Shader* s);
        GameObject(const std::string& name, Model* m, Shader* s, const Transform& tr);
        GameObject(const GameObject& m);
        virtual ~GameObject();
		#pragma endregion

        #pragma region Accessors
        inline std::string&              name()            { return _name; };
        inline std::string               name()      const { return _name; };
        inline bool&                     active()          { return _active; };
        inline bool                      active()    const { return _active; };
        inline Transform&                transform()       { return _transform; };
        inline Transform                 transform() const { return _transform; };
        inline Model*                    model()           { return _model; };
        inline Shader*                   shader()          { return _shader; };
        inline Collider*                 collider()        { return _collider; };
        inline RigidBody*                rigidBody()       { return _rigidBody; };
        inline std::vector<GameObject*>& children()        { return _children; };
		#pragma endregion

        #pragma region Operators
        GameObject& operator=(const GameObject& gO) noexcept;
        #pragma endregion

		#pragma region Functions
        // GameObject Functions
        #pragma region GameObject
        virtual GameObject& update(Scene& scene, float deltaTime) noexcept;
        GameObject& physicUpdate  (Scene& scene, float deltaTime) noexcept;
        GameObject& render        (const Mat& viewMat, const Vec3& viewPos,
                                   const std::vector<Light*>& lights,
                                   Mat transfromParent = Mat::identity(4)) noexcept;

        GameObject* addChild      (GameObject* gO)                      noexcept;
        GameObject& removeChild(GameObject* gO)                         noexcept;
        GameObject& removeChildren()                                    noexcept;

        bool isActive() noexcept;
        bool hasCollider() noexcept;
        bool checkCollision(const Collider* collider, 
                            const Vec3& speed, 
                            float deltaTime, 
                            SegmentHit*& hit) noexcept;
        bool collideWithSegment(const Segment& s, SegmentHit*& hit) const noexcept;

        virtual GameObject& onCollision(Scene& scene, Collider* collider, SegmentHit* hit) noexcept;
        virtual GameObject& onTrigger  (Scene& scene, Collider* collider, SegmentHit* hit) noexcept;

        GameObject& addRigidBody(bool useGravity = true, float mass = BASE_MASS, 
                                 float friction = BASE_FRICTION) noexcept;
        GameObject& addCollider(const EColliderType& type,
                                bool isTrigger = false) noexcept;

        virtual bool struckByBullet(Scene& scene, const Vec3& collPoint, 
                                    float damage) noexcept;
        virtual bool pickUpItem(ItemType type, uint numberOfItem) noexcept;
        virtual GameObject& save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept;
        
        GameObject& saveGameObject(std::ofstream& fs, ResourcesManager& resourcesManager) noexcept;
        GameObject& saveChildren(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept;
        #pragma endregion

        // Transform
        #pragma region Transform
        /* Translate the current position of the transform */
        void	translate      (const Vec3& translation)                noexcept;
        /* Rotate the current rotation of the transform */
        void	rotate         (const Vec3& rotation)                   noexcept;
        /* Grow the current scale of the transform */
        void	grow           (const Vec3& growth)                     noexcept;
        void	setPosition    (const Vec3& position)                   noexcept;
        void	setRotation    (const Vec3& rotation)                   noexcept;
        void	setScale       (const Vec3& scale)                      noexcept;
        /* Update the position and the transform matrix of the transform */
        void    updatePosition (const Vec3& pos)                        noexcept;
        /* Update the rotation and the transform matrix of the transform */
        void    updateRotation (const Vec3& rot)                        noexcept;
        /* Update the scale and the transform matrix of the transform */
        void    updateScale    (const Vec3& scale)                      noexcept;
        /* Update the transform of the transform */
        void    updateMatrix   ()                                       noexcept;
        #pragma endregion
		#pragma endregion
    };
} /* LowRenderer */
#endif//__GAMEOBJECT_H__
