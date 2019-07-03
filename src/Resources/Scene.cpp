#include "Scene.h"
#include <algorithm>
#include <limits>

namespace Resources
{
    #pragma region Constructors
    Scene::Scene(const Scene& s)
    {
        // Copy each pointer of scene
        std::list<GameObject*>::const_iterator it = s._objects.begin();
        for (; it != s._objects.end(); ++it)
        {
            // If the scene exists
            if (*it)
                // Push back a copy of the pointer of the scene
                _objects.push_back(new GameObject(**it));
        }

        std::vector<GameObject*>::const_iterator itAdd = s._objectsToAdd.begin();
        for (; itAdd != s._objectsToAdd.end(); ++itAdd)
        {
            // If the scene exists
            if (*itAdd)
                // Push back a copy of the pointer of the scene
                _objectsToAdd.push_back(new GameObject(**itAdd));
        }

        // Copy the lights
        std::vector<Light*>::const_iterator itLight = s._lights.begin();
        for (; itLight != s._lights.end(); ++itLight)
            if (*itLight)
                _lights.push_back((*itLight)->clone());
    }

    Scene::~Scene()
    {
        emptyLists();
    }
    #pragma endregion

    #pragma region Operator
    Scene& Scene::operator=(const Scene& s)
    {
        emptyLists();

        // Copy the children
        std::list<GameObject*>::const_iterator it = s._objects.begin();
        for (; it != s._objects.end(); ++it)
        {
            // If the scene exists
            if (*it)
                // Push back a copy of the pointer of the scene
                _objects.push_back(new GameObject(**it));
        }

        std::vector<GameObject*>::const_iterator itAdd = s._objectsToAdd.begin();
        for (; itAdd != s._objectsToAdd.end(); ++itAdd)
        {
            // If the scene exists
            if (*itAdd)
                // Push back a copy of the pointer of the scene
                _objectsToAdd.push_back(new GameObject(**itAdd));
        }

        // Copy the lights
        std::vector<Light*>::const_iterator itLight = s._lights.begin();
        for (; itLight != s._lights.end(); ++itLight)
            if (*itLight)
                _lights.push_back((*itLight)->clone());

        return *this;
    }
    #pragma endregion

    #pragma region Fonctions
    GameObject* Scene::addChild(GameObject* gO) noexcept
    {
        if (!gO)
            return nullptr;

        // Add it to the list of objects to be added
        _objectsToAdd.push_back(gO);

        return gO;
    }

    GameObject* Scene::addChild(GameObject* gO, float lifeTime) noexcept
    {
        if (!gO)
            return nullptr;

        // Add it to the list of objects to be added
        _objectsToAdd.push_back(gO);

        // Add the object to the objects to be removed
        insertInOrderToRemove(gO, lifeTime);

        return gO;
    }

    Scene& Scene::remove(GameObject* gO) noexcept
    {
        if (!gO)
            return *this;

        // Add the object to the objects to be removed
        insertInOrderToRemove(gO, 0.0f);

        return *this;
    }
    
    Scene& Scene::remove(GameObject* gO, float lifeTime) noexcept
    {
        if (!gO)
            return *this;

        // Add the object to the objects to be removed
        insertInOrderToRemove(gO, lifeTime);

        return *this;
    }

    bool compareLifeTime(const ObjectLife& o1, const float& lifeTime)
    {
        return o1.second > lifeTime;
    }

    Scene& Scene::insertInOrderToRemove(GameObject* gO, float lifeTime) noexcept
    {
        // Check if it is already inside the list
        auto itGameObjectAlreadyIn = std::find_if(
            _objectsToRemove.begin(), _objectsToRemove.end(),
            [&gO](const std::pair<GameObject*, float>& element){ return element.first == gO; } );

        // If the GameObject already needs to be destroyed
        if (itGameObjectAlreadyIn != _objectsToRemove.end())
        {
            // If the GameObject's lifetime contained in the list is higher than 
            // the one we are trying to add remove its iterator
            if (lifeTime < itGameObjectAlreadyIn->second)
                _objectsToRemove.erase(itGameObjectAlreadyIn);
            // Or do not change anything
            else
                return *this;
        }

        // Find the best place to insert the object (keep it ordered)
        auto it = std::lower_bound(
            _objectsToRemove.begin(), _objectsToRemove.end(),
            lifeTime, compareLifeTime);

        // Insert the gameObject and its life time
        _objectsToRemove.insert(it, std::pair<GameObject*, float>(gO, lifeTime));

        return *this;
    }

    Light* Scene::addLight(Light* light) noexcept
    {
        // Push it to the list of lights
        _lights.push_back(light);

        return light;
    }

    Scene& Scene::update(float deltaTime) noexcept
    {
        updateObjectsToAdd();
        
        for (auto it = _objects.begin(); it != _objects.end(); ++it)
        {
            if (*it)
                (*it)->update(*this, deltaTime);
        }

        updateObjectsToRemove(deltaTime);

        return *this;
    }

    Scene& Scene::updateObjectsToAdd() noexcept
    {
        auto it = _objectsToAdd.begin();
        while (it != _objectsToAdd.end())
        {
            // Add the current object to the list of objects
            _objects.push_back(*it);

            // Remove it from the list of objects to add
            it = _objectsToAdd.erase(it);
        }

        return *this;
    }

    Scene& Scene::updateObjectsToRemove(float deltaTime) noexcept
    {
        // Decrease all the lifeTimes of the Objects to be destroyed
        for (auto it = _objectsToRemove.begin(); it !=_objectsToRemove.end(); ++it)
            it->second -= deltaTime;

        // Get the reverse iterator to check the last object if it as to die
        auto it = _objectsToRemove.rbegin();
        while (it != _objectsToRemove.rend() && it->second <= std::numeric_limits<float>::epsilon())
        {
            // Remove the gameObject
            if (it->first)
            {
                _objects.remove(it->first);
                delete it->first;
            }
            
            // remove the Object from the list
            _objectsToRemove.pop_back();
            ++it;
        }

        return *this;
    }

    Scene& Scene::physicUpdate(float deltaTime) noexcept
    {
        for (auto it = _objects.begin(); it != _objects.end(); ++it)
        {
            if (*it)
                (*it)->physicUpdate(*this, deltaTime);
        }

        return *this;
    }
    
    Scene& Scene::render(const Mat& viewProj, const Vec3& viewPos) noexcept
    {
        // Create the new matrix
        for (auto it = _objects.begin(); it != _objects.end(); ++it)
        {
            // Draw the child if it exists
            if (*it)
                (*it)->render(viewProj, viewPos, _lights);
        }

        return *this;
    }

    Scene& Scene::emptyLists() noexcept
    {
        // Remove each children's scene
        std::list<GameObject*>::iterator itChildren = _objects.begin();
        while (itChildren != _objects.end())
        {
            if (*itChildren)
                delete *itChildren;

            itChildren = _objects.erase(itChildren);
        }

        // Remove each children's scene
        std::vector<GameObject*>::iterator itAdd = _objectsToAdd.begin();
        while (itAdd != _objectsToAdd.end())
        {
            if (*itAdd)
                delete *itAdd;

            itAdd = _objectsToAdd.erase(itAdd);
        }

        // As we are only stocking references there's no use to destroy the objects
        _objectsToRemove.clear();

        // Remove each children's scene
        std::vector<Light*>::iterator itLights = _lights.begin();
        while (itLights != _lights.end())
        {
            if (*itLights)
                delete *itLights;

            itLights = _lights.erase(itLights);
        }

        return *this;
    }

    Scene& Scene::save(std::ofstream& fs, std::string folderPath) noexcept
    {
        std::list<GameObject*>::iterator itChildren = _objects.begin();
        while (itChildren != _objects.end())
        {
            (*itChildren)->save(fs, *_resourcesManager, folderPath);
            itChildren++;
        }
        return *this;
    }
    #pragma endregion
} /* Resources */
