#ifndef __PICKABLE_ITEM_H__
#define __PICKABLE_ITEM_H__

#include <string>

#include "GameObject.h"
#include "Scene.h"
#include "ResourcesManager.h"

#define PI_MAX_VERTICAL_DISTANCE 0.1f
#define PI_VERTICAL_SPEED 0.1f
#define PI_ROTATION_SPEED 0.5f

namespace Game::Items
{
    #pragma region Typedefs
        typedef std::string                         string;
        typedef LowRenderer::GameObject             GameObject;
        typedef Resources::Model                    Model;
        typedef Resources::Shader                   Shader;
        typedef Physics::Transform                  Transform;
        typedef Physics::Collider                   Collider;
        typedef Resources::Scene                    Scene;
        typedef Physics::Collisions::SegmentHit     SegmentHit;
        typedef Resources::ResourcesManager ResourcesManager;
    #pragma endregion

    class PickableItem : public GameObject
    {
        protected:
            #pragma region Attributes
                ItemType        _itemType;
                float           _currVerticalDistance;
                float           _currentRotation;
                int             _verticalDir;
                uint            _number;
            #pragma endregion

        public:
            #pragma region Constructors
                PickableItem();
                PickableItem(const std::string& name, Model* m, Shader* s,
                             const Transform& tr, ItemType type, uint nb);
                PickableItem(const PickableItem& m);
                ~PickableItem() = default;
            #pragma endregion

            #pragma region Accessors
                inline ItemType     itemType() const { return _itemType; }
                inline ItemType&    itemType()       { return _itemType; }
                inline uint         number()   const { return _number; }
                inline uint&        number()         { return _number; }
            #pragma endregion

            #pragma region Operators
                PickableItem&   operator=(const PickableItem& type);
            #pragma endregion

            #pragma region Functions
                GameObject& update(Scene& scene, float deltaTime) noexcept override;
                GameObject& onTrigger(Scene& scene, Collider* collider,       
                                          SegmentHit* hit) noexcept override;
                GameObject& save(std::ofstream& fs, ResourcesManager& resourcesManager, 
                    std::string folderPath) noexcept override;
            #pragma endregion
    };
} // namespace Game::Items

#endif //__PICKABLE_ITEM_H__