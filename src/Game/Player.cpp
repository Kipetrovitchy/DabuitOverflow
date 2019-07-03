#include "Player.h"

#include "LibMaths.h"
#include "Camera3D.h"
#include "SphereCollider.h"
#include "SegmentHit.h"
#include "DecisionPlayerGrounded.h"
#include "Transition.h"
#include "StatePlayerFlying.h"
#include "StatePlayerGrounded.h"

#include "Medikit.h"

namespace Game
{
    typedef Physics::Collisions::SphereCollider SphereCollider;
    typedef Physics::Collisions::Segment        Segment;
    typedef Physics::Collisions::SegmentHit     SegmentHit;
    typedef Core::Maths::Sphere                 Sphere;
    typedef Items::Medikit                      Medikit;

    #pragma region Constructors
    Player::Player() :
        Entity(),
        IController(),
        _hasToJump      { false },
        _hasToShoot     { false },
        _hasToReload    { false },
        _hasToHeal      { false },
        _hasToAim       { false },
        _isGrounded     { false },
        _camera         { nullptr },
        _gunAnchorObject{ nullptr },
        _acceleration   { PLAYER_BASE_ACCELERATION },
        _deceleration   { PLAYER_BASE_DECELERATION },
        _maxSpeed       { PLAYER_BASE_MAXSPEED },
        _jumpStrenght   { PLAYER_BASE_JUMPSTRENGHT },
        _direction      { Vec3::zero },
        _zoom           { 1.0f }
    {
        addRigidBody();
        addCollider(Physics::Collisions::EColliderType::SPHERE);
        createStateMachine();
    } 

    Player::Player(const std::string& name, Model* m, Shader* s, const Transform& tr,
            Camera3D* camera, float maxLife, float maxSpeed) :
        Entity(name, m, s, tr, maxLife),
        IController(),
        _hasToJump      { false },
        _hasToShoot     { false },
        _hasToReload    { false },
        _hasToHeal      { false },
        _hasToAim       { false },
        _isGrounded     { false },
        _camera         { camera },
        _gunAnchorObject{ nullptr },
        _acceleration   { PLAYER_BASE_ACCELERATION },
        _deceleration   { PLAYER_BASE_DECELERATION },
        _maxSpeed       { maxSpeed },
        _jumpStrenght   { PLAYER_BASE_JUMPSTRENGHT },
        _direction      { Vec3::zero },
        _zoom           { 1.0f }
    {
        addRigidBody(true, 3.0f);
        addCollider(Physics::Collisions::EColliderType::SPHERE);
        createStateMachine();
    }

    Player::Player(const Player& p) :
        Entity(p),
        _hasToJump      { p._hasToJump },
        _hasToShoot     { p._hasToShoot },
        _hasToReload    { p._hasToReload },
        _hasToHeal      { p._hasToHeal },
        _hasToAim       { p._hasToAim },
        _isGrounded     { p._isGrounded },
        _camera         { p._camera },
        _gunAnchorObject{ p._gunAnchorObject },
        _acceleration   { p._acceleration },
        _deceleration   { p._deceleration },
        _maxSpeed       { p._maxSpeed },
        _jumpStrenght   { p._jumpStrenght },
        _direction      { p._direction },
        _zoom           { p._zoom },
        _stateMachine   { p._stateMachine },
        _inventory      { p._inventory }
    {}
    #pragma endregion

    #pragma region Operators
    Player&     Player::operator=(const Player& p)
    {
        Entity::operator=(p);
        _hasToJump      = p._hasToJump;
        _hasToShoot     = p._hasToShoot;
        _hasToReload    = p._hasToReload;
        _hasToHeal      = p._hasToHeal;
        _hasToAim       = p._hasToAim;
        _isGrounded     = p._isGrounded;
        _isDead         = p._isDead;
        _camera         = p._camera;
        _acceleration   = p._acceleration;
        _deceleration   = p._deceleration;
        _maxSpeed       = p._maxSpeed;
        _jumpStrenght   = p._jumpStrenght;
        _direction      = p._direction;
        _zoom           = p._zoom;
        _stateMachine   = p._stateMachine;
        _inventory      = p._inventory;

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    Vec3 Player::getForward() noexcept
    {
        if (!_camera)
            return Vec3::forward;

        Vec3 forward { _camera->front() };
        forward.y = 0;
        
        return forward.unit();
    }
    Vec3 Player::getRight() noexcept
    {
        return getForward().cross(Vec3::up);
    }

    
    Player& Player::moveForward() noexcept
    {
        if (_direction.z == 0)
            _direction.z = 1;
        else
            _direction.z = 0;

        return *this;
    }
    Player& Player::moveBackward() noexcept
    {
        if (_direction.z == 0)
            _direction.z = -1;
        else
            _direction.z = 0;

        return *this;
    }
    Player& Player::moveRight() noexcept
    {
        if (_direction.x == 0)
            _direction.x = 1;
        else
            _direction.x = 0;

        return *this;
    }
    Player& Player::moveLeft() noexcept
    {
        if (_direction.x == 0)
            _direction.x = -1;
        else
            _direction.x = 0;

        return *this;
    }


    Player& Player::jump() noexcept
    {
        _hasToJump = true;
        
        return *this;
    }
    Player& Player::shoot() noexcept
    {
        _hasToShoot = true;
        
        return *this;
    }
    Player& Player::reload() noexcept
    {
        _hasToReload = true;

        return *this;
    }
    Player& Player::changeWeapon(int dir) noexcept
    {
        Weapon* current = dynamic_cast<Weapon*>(_inventory.mainItem());
        _inventory.switchMain(dir);
        Weapon* newMain = dynamic_cast<Weapon*>(_inventory.mainItem());
        if (newMain)
        {
            current->setActive(false);
            newMain->setActive(true);
            _updateWeapon(newMain);
            _updateAmmo(newMain->actualClip(),
                        _inventory.nbOfItem(newMain->bulletType()));
        }
        
        return *this;
    }
    Player& Player::heal() noexcept
    {
        _hasToHeal = true;
        
        return *this;
    }
    Player& Player::aim() noexcept
    {
        _hasToAim = true;

        return *this;
    }


    GameObject& Player::update(Scene& scene, float deltaTime) noexcept
    {
        if (!_active)
            return *this;
        
        _stateMachine.update(scene, deltaTime);
        _inventory.update(scene, deltaTime);
        
        _hasToJump   = false;
        _hasToShoot  = false;
        _hasToReload = false;
        _hasToHeal   = false;
        _hasToAim    = false;

        return *this;
    }

    Player& Player::move(float deltaTime) noexcept
    { 
        Vec3 velocity = _rigidBody->velocity();

        _direction.unit();
        Vec3 forward { getForward() };
        //Adapt vDirector to the cam orientation
        Vec3    impulseDir = (forward * _direction.z + 
                             (getRight()   * _direction.x));

        //Accelerate or decelerate if keys are pressed or not
        Vec3    impulse = ((impulseDir * _maxSpeed) - velocity) * (_acceleration * deltaTime);
        impulse.y = 0;
        _rigidBody->addForce(impulse);

        // Rotate the player on the y axis and its gun on the z axis to make it look up and down
        _transform.setRotation({0.0f, -_camera->theta(), 0.0f});
        if (_gunAnchorObject)
            _gunAnchorObject->transform().updateRotation({0.0f, 0.0f, _camera->phi()});

        _direction.x = _direction.z = 0;

        return *this;
    }


    Player& Player::tryJump() noexcept
    {
        if (_isGrounded && _hasToJump)
        {
            _rigidBody->addForce(Vec3::up * _jumpStrenght);
            _hasToJump = false;
        }
        return *this;
    }
    Player& Player::tryShoot(Scene& scene) noexcept
    {
        if (_hasToShoot)
        {
            Weapon* gun = dynamic_cast<Weapon*>(_inventory.mainItem());
            if (gun)
            {
                if (_camera)
                    gun->shoot(scene, _camera->front());
                else
                    gun->shoot(scene, Vec3::forward);
                _updateAmmo(gun->actualClip(),
                            _inventory.nbOfItem(gun->bulletType()));
            }

            _hasToShoot = false;
        }
        return *this;
    }
    Player& Player::tryReload() noexcept
    {
        if (_hasToReload)
        {
            Weapon* gun = dynamic_cast<Weapon*>(_inventory.mainItem());
            
            if (gun)
                gun->startReload();
        }
        
        return *this;
    }
    Player& Player::tryHeal() noexcept
    {
        if (_hasToHeal)
        {
            Medikit* med = dynamic_cast<Medikit*>(_inventory.getItem(ItemType::MEDIKIT));
            if (med)
            {
                med->use(this);
                _inventory.removeItem(med->type());
                updateHpHUD();
                _updateMedkit(false);
            }
        }
        
        return *this;
    }
    Player& Player::tryAim(float deltaTime) noexcept
    {
        if (_hasToAim)
        {
            if (_zoom < ZOOM_MAX)
            {
                _zoom += deltaTime * 20;
                if (_zoom > ZOOM_MAX)
                    _zoom = ZOOM_MAX;
                _camera->updateFov(FOV / _zoom);
            }
        }
        else
        {
            if (_zoom > ZOOM_MIN)
            {
                _zoom -= deltaTime * 20;
                if (_zoom < ZOOM_MIN)
                    _zoom = ZOOM_MIN;
                _camera->updateFov(FOV / _zoom);
            }
        }

        return *this;
    }


    Player& Player::updateIsGroundedValue(Scene& scene) noexcept
    {
        _isGrounded = _rigidBody->isGrounded(scene, _transform, _collider);

        return *this;
    }

    Player& Player::createStateMachine() noexcept
    {
        using namespace StateMachines; 

        DecisionPlayerGrounded* dpg = new DecisionPlayerGrounded(this, false);
        DecisionPlayerGrounded* notDpg = new DecisionPlayerGrounded(this, true);

        StatePlayerFlying* flying = new StatePlayerFlying(this);
        StatePlayerGrounded* grounded = new StatePlayerGrounded(this);

        Transition* groundedToFlying = new Transition(flying);
        Transition* flyingToGrounded = new Transition(grounded);

        groundedToFlying->addDecision(notDpg);
        flyingToGrounded->addDecision(dpg);

        flying->addTransition(flyingToGrounded);
        grounded->addTransition(groundedToFlying);
 
        _stateMachine.changeState(grounded); 

        _stateMachine.addReferences(6, groundedToFlying, flyingToGrounded, flying, grounded, dpg, notDpg);  

        return *this;
    }

    Player& Player::loadGunModel() noexcept
    {
        _gunAnchorObject = new GameObject("Gun Anchor",
			nullptr, nullptr,
			{{0.12f, 0.4f, 0.1f}, Vec3::zero, Vec3::one}
		);
		addChild(_gunAnchorObject);

        return *this;
    }
    

    Player& Player::updateHpHUD() noexcept
    {
        _updateHP(_life, _maxLife);

        return *this;
    }
    Player& Player::updateWeaponHUD() noexcept
    {
        if (dynamic_cast<Weapon*>(_inventory.mainItem()))
            _updateWeapon((Weapon*)_inventory.mainItem());

        return *this;
    }
    Player& Player::updateAmmoHUD() noexcept
    {
        if (dynamic_cast<Weapon*>(_inventory.mainItem()))
        {
            Weapon* actual { (Weapon*)_inventory.mainItem() };
            _updateAmmo(actual->actualClip(),
                    _inventory.nbOfItem(actual->bulletType()));
        }

        return *this;
    }

    Player& Player::updateMedkitHUD() noexcept
    {
        Item* medkit { _inventory.getItem(ItemType::MEDIKIT)};

        if (medkit)
            _updateMedkit(true);
        else
            _updateMedkit(false);

        return *this;
    }

    Entity& Player::takeDamage(float f) noexcept
    {
        Entity::takeDamage(f);
        _updateHP(_life, _maxLife);

        return *this;
    }

    bool Player::pickUpItem(ItemType type, uint numberOfItem) noexcept
    {
        if (type == ItemType::MEDIKIT)
            _updateMedkit(true);
        
        _inventory.addItem(type, numberOfItem);
        if (dynamic_cast<Weapon*>(_inventory.mainItem()))
        {
            Weapon* actual { (Weapon*)_inventory.mainItem() };
            _updateAmmo(actual->actualClip(),
                        _inventory.nbOfItem(actual->bulletType()));
        }

        return true;
    }
    
    Player& Player::setUpdateHP(std::function<void(int, int)> func) noexcept
    {
        _updateHP = func;
        _updateHP(_life, _maxLife);

        return *this;
    }
    Player& Player::setUpdateWeapon(std::function<void(Weapon*)> func) noexcept
    {
        _updateWeapon = func;
        if ((Weapon*)_inventory.mainItem())
            _updateWeapon((Weapon*)_inventory.mainItem());

        return *this;
    }
    Player& Player::setUpdateAmmo(std::function<void(int, int)> func) noexcept
    {
        _updateAmmo = func;
        if ((Weapon*)_inventory.mainItem())
        {
            Weapon* actual { (Weapon*)_inventory.mainItem() };
            _updateAmmo(actual->actualClip(),
                    _inventory.nbOfItem(actual->bulletType()));
        }

        return *this;
    }

    Player& Player::setUpdateMedkit(std::function<void(bool)> func) noexcept
    {
        _updateMedkit = func;

        return *this;
    }

    bool Player::struckByBullet(Scene& scene,
                                const Core::Maths::Vec3& collPoint, 
                                float damage) noexcept
    {
        (void) scene;   
        (void) collPoint;   
        (void) damage;   

        return false;
    }

    GameObject& Player::save(std::ofstream& fs, ResourcesManager& resourceManager, std::string folderPath) noexcept
    {
        GameObject::saveGameObject(fs, resourceManager);

        fs << "," << 2 << "," << _maxLife << "," << _life << "," << 0 << "," << 0 << "\n";

        std::ofstream inventoryfs;
        std::string fileName = folderPath + "inventory.csv";
        inventoryfs.open (fileName, std::ofstream::trunc);
        inventoryfs << "ItemType,Nb,IsMainItem\n";

        _inventory.save(inventoryfs);

        inventoryfs.close();

        return *this;
    }
    #pragma endregion
} // namespace Game
