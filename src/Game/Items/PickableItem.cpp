#include "PickableItem.h"
#include "Item.h"

namespace Game::Items
{
    #pragma region Constructors
        PickableItem::PickableItem() :
            GameObject(),
            _itemType               {ItemType::NONE},
            _currVerticalDistance   {0.0f},
            _currentRotation        {0.0f},
            _verticalDir            {1},
            _number                 {0}
        {
            addCollider(Physics::Collisions::EColliderType::BOX, true);
        }

        PickableItem::PickableItem(const std::string& name, Model* m, Shader* s,
                                   const Transform& tr, ItemType type, uint nb) :
            GameObject(name, m, s, tr),
            _itemType               {type},
            _currVerticalDistance   {0.0f},
            _currentRotation        {0.0f},
            _verticalDir            {1},
            _number                 {nb}
        {
            addCollider(Physics::Collisions::EColliderType::BOX, true);
        }

        PickableItem::PickableItem(const PickableItem& pI) :
            GameObject(pI),
            _itemType               { pI._itemType },
            _currVerticalDistance   { pI._currVerticalDistance },
            _currentRotation        { pI._currentRotation },
            _verticalDir            { pI._verticalDir },
            _number                 { pI._number }
        {}
    #pragma endregion

    #pragma region Operators
        PickableItem&   PickableItem::operator=(const PickableItem& pI)
        {
            GameObject::operator=(pI);
            _itemType               = pI._itemType;
            _currVerticalDistance   = pI._currVerticalDistance;
            _currentRotation        = pI._currentRotation;
            _verticalDir            = pI._verticalDir;
            _number                 = pI._number;

            return *this;
        }
    #pragma endregion

    #pragma region Functions
        GameObject& PickableItem::update(Scene& scene, float deltaTime) noexcept
        {
            (void) scene;

            // Get the amount of the movement during the frame
            float frameMovement = deltaTime * _verticalDir * PI_VERTICAL_SPEED;
            _currVerticalDistance += frameMovement;

            // Set the direction to its opposite dir if it has reached its max distance
            if (std::fabs(_currVerticalDistance) > PI_MAX_VERTICAL_DISTANCE)
                _verticalDir *= -1;

            // Get the mod of the rotation
            _currentRotation = 
                std::fmod<float>(_currentRotation + deltaTime * PI_ROTATION_SPEED, M_PI * 2.0f);

            // Translate and update the object
            _transform.translate     ({0.0f, frameMovement, 0.0f});
            _transform.updateRotation({0.0f, _currentRotation, 0.0f});

            return *this;
        }

        GameObject& PickableItem::onTrigger(Scene& scene, Collider* collider,
                                                SegmentHit* hit) noexcept
        {
            (void) hit;

            if (collider->gameObject()->pickUpItem(_itemType, _number))
                scene.remove(this);

            return *this;
        }

        GameObject& PickableItem::save(std::ofstream& fs, 
            ResourcesManager& resourcesManager, std::string folderPath) noexcept 
        {
            GameObject::saveGameObject(fs, resourcesManager);
            fs << "," << 3 <<  "," << 0 << "," << 0 << "," << (uint)_itemType 
            << "," << _number << "\n";
            GameObject::saveChildren(fs, resourcesManager, folderPath);
            return *this;
        }
    #pragma endregion
} // namespace Game::Items
