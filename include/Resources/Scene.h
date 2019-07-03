#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
#include <vector>
#include <queue>
#include <fstream>

#include "InputMgr.h"
#include "LibMaths.h"
#include "GameObject.h"
#include "Light.h"
#include "ResourcesManager.h"

namespace Resources
{
    typedef Game::Inputs::InputMgr          InputMgr;
    typedef LowRenderer::GameObject         GameObject;
    typedef LowRenderer::Light              Light;
    typedef Core::Maths::Mat                Mat;
    typedef Resources::ResourcesManager     ResourcesManager;

    typedef std::pair<GameObject*, float>   ObjectLife;

    bool lifeTimeComparer(const ObjectLife& o1, const ObjectLife& o2);

    class Scene
    {
    private:
        #pragma region Attributes
        std::list <GameObject*>                    _objects;
        std::vector<GameObject*>                   _objectsToAdd;
        std::vector<std::pair<GameObject*, float>> _objectsToRemove;

        std::vector<Light*>         _lights;
        ResourcesManager*           _resourcesManager;
        #pragma endregion

        #pragma region Functions
        Scene& insertInOrderToRemove(GameObject* gO, float lifeTime) noexcept;
        Scene& updateObjectsToAdd() noexcept;
        Scene& updateObjectsToRemove(float deltaTime) noexcept;
        #pragma endregion

    public:
        #pragma region Constructors
        Scene() = default;
        Scene(const Scene& s);
        ~Scene();
        #pragma endregion

        #pragma region Operator
        Scene& operator=(const Scene& s);
        #pragma endregion

        #pragma region Fonctions
        GameObject*  addChild(GameObject* gO) noexcept;
        GameObject*  addChild(GameObject* gO, float lifeTime) noexcept;
        Scene&       remove(GameObject* gO) noexcept;
        Scene&       remove(GameObject* gO, float lifeTime) noexcept;
        Light*       addLight(Light* light) noexcept;

        Scene&  update          (float deltaTime) noexcept;
        Scene&  physicUpdate    (float deltaTime) noexcept;
        Scene&	render          (const Mat& viewProj, const Vec3& viewPos) noexcept;
                                 
        Scene& emptyLists() noexcept;
        Scene& save(std::ofstream& fs, std::string folderPath) noexcept;
        #pragma endregion

        #pragma region Accessors
        inline std::list<GameObject*>&      objects() { return _objects; };
        inline std::vector<GameObject*>&    objectsToAdd() { return _objectsToAdd; };
        inline std::vector<std::pair<GameObject*, float>>& objectsToRemove() { return _objectsToRemove; };
        inline std::vector<Light*>&         lights()   { return _lights; };

        inline ResourcesManager*&   resourcesManager() {return _resourcesManager; }
        #pragma endregion
    };
} /* Resources */

#endif//__SCENE_H__
