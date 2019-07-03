#include "Weapon.h"
#include "Inventory.h"
#include "Player.h"

namespace Game::Items
{
    #pragma region Constructors
        Weapon::Weapon() : Item(),
            _inventory      {nullptr},
            _model          {nullptr},
            _canShoot       {false},
            _shootCd        {0.f},
            _reloadCd       {0.f},
            _bulletType     {ItemType::NONE},
            _actualClip     {1},
            _clipSize       {1},
            _rate           {1},
            _range          {1},
            _reload         {0},
            _damage         {0}
        {}

        Weapon::Weapon(Inventory* inventory, const ItemType& type,
                       const string& name, float weight, const ItemType& bType,
                       uint clipS, float rate, float range, float reload,
                       float damage, Texture* texture, GameObject* model) : 
            Item(type, name, 1, 0, weight, texture),
            _inventory      {inventory},
            _model          {model},
            _canShoot       {false},
            _shootCd        {0.f},
            _reloadCd       {0.f},
            _bulletType     {bType},
            _actualClip     {0},
            _clipSize       {clipS},
            _rate           {rate},
            _range          {range},
            _reload         {reload},
            _damage         {damage}
        {
            _inventory->owner()->gunAnchorObject()->addChild(_model);
            _model->active() = false;
        }
        Weapon::Weapon(const Weapon& copy) : Item(copy),
            _inventory      {copy._inventory},
            _model          {copy._model},
            _canShoot       {false},
            _shootCd        {0.f},
            _reloadCd       {copy._reloadCd},
            _bulletType     {copy._bulletType},
            _actualClip     {copy._actualClip},
            _clipSize       {copy._clipSize},
            _rate           {copy._rate},
            _range          {copy._range},
            _reload         {copy._reload},
            _damage         {copy._damage}
        {}
        Weapon::~Weapon()
        {
            _inventory->owner()->gunAnchorObject()->removeChild(_model);
        }
    #pragma endregion

    #pragma region Operators
        Weapon& Weapon::operator=(const Weapon& copy)
        {
            Item::operator=(copy);
            _inventory  = copy._inventory;
            _canShoot   = copy._canShoot;
            _shootCd    = copy._shootCd;
            _reloadCd   = copy._reloadCd;
            _name       = copy._name;
            _stackMax   = copy._stackMax;
            _weight     = copy._weight;
            _bulletType = copy._bulletType;
            _actualClip = copy._actualClip;
            _clipSize   = copy._clipSize;
            _rate       = copy._rate;
            _range      = copy._range;
            _reload     = copy._reload;
            _damage     = copy._damage;

            return *this;
        }
    #pragma endregion

    #pragma region Functions
        Item& Weapon::update(Scene& scene, float deltaTime) noexcept
        {
            (void) scene;
            updateCanShootValue(deltaTime);

            if (_actualClip == 0 && _reloadCd <= 0.0f)
                startReload();

            return *this;
        }

        Weapon& Weapon::updateCanShootValue(float deltaTime) noexcept
        {
            if (_model->isActive())
            {
                if (_shootCd > 0.0f)
                {
                    _shootCd -= deltaTime;
                    if (_shootCd <= 0)
                        _model->updateRotation({0.0f});
                    else
                        _model->updateRotation({0.0f, 0.0f, (float)((M_PI / 2) * (_shootCd))});
                }
                
                if (_reloadCd > 0.0f)
                {
                    _reloadCd -= deltaTime;
                    float angle = (2 * M_PI) * (_reloadCd / _reload);
                    if (_reloadCd <= 0.0f)
                    {
                        reloadClip();
                        _model->updateRotation({0.0f});
                    }
                    else
                        _model->updateRotation({0.0f, 0.0f, angle});
                }
            }
            else
            {
                if (_shootCd > 0.0f)
                    _shootCd = _rate / 60.f;
                if (_reloadCd > 0.0f)
                    _reloadCd = _reload;
            }

            if ((_inventory->nbOfItem(_bulletType) != 0 || _actualClip != 0) &&
                (_shootCd <= 0.f && _reloadCd <= 0.f))
                _canShoot = true;
            else
                _canShoot = false;

            return *this;
        }

        Weapon& Weapon::shoot(Scene& scene, const Vec3& front) noexcept
        {
            if (_canShoot)
            {
                if (_actualClip-- > 0)
                {
                    _canShoot = false;
                    _shootCd = 60.f / _rate;
                    
                    Bullet* b = createBullet(scene, BulletType::RIFLE,
                                             (Entity*)_inventory->owner(), _damage);
                    b->transform().updatePosition(b->owner()->getHeadPosition());

                    scene.addChild(b, 2);

                    b->rigidBody()->addForce(front * 100);
                    _firedBullets.push_back(b);

                    _inventory->removeItem(_bulletType);
                }
            }

            return *this;
        }

        Weapon& Weapon::startReload() noexcept
        {
            if (_reloadCd <= 0.0f)
            {
                Item* ammoType {_inventory->getItem(_bulletType)};
                if (ammoType && (_actualClip < _clipSize)
                            && (ammoType->currStack() - _actualClip != 0))
                {    
                    _reloadCd = _reload;
                }
            }

            return *this;
        }

        Weapon& Weapon::reloadClip() noexcept
        {
            Item* ammoType {_inventory->getItem(_bulletType)};
            if (ammoType && (_actualClip < _clipSize)
                         && (ammoType->currStack() - _actualClip != 0))
            {    
                uint ammo = ammoType->currStack() - _actualClip;
                uint addMax = _clipSize - _actualClip;

                _actualClip += ((ammo) <= addMax ? ammo : addMax);
                _inventory->owner()->updateAmmoHUD();
            }

            return *this;
        }

        Weapon& Weapon::setActive(bool flag) noexcept
        {
            if (_model)
                _model->active() = flag;
            
            return *this;
        }

    #pragma endregion
}