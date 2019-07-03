#include "GameObject.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "LibMaths.h"
#include "Log.h"
#include "Assert.h"
#include "Vertex.h"
#include "Material.h"
#include "Segment.h"
#include "Scene.h"
#include "Impact.h"

namespace LowRenderer
{
	#pragma region typedefs
    typedef Resources::Material Material;
    typedef Core::Maths::Vec3   Vec3;
    typedef Resources::Vertex   Vertex;
    typedef Game::Impact        Impact;
	#pragma endregion

	#pragma region Constructors
    GameObject::GameObject():
        _active    { true },
        _model     { nullptr },
        _shader    { nullptr },
        _collider  { nullptr },
        _rigidBody { nullptr }
    {}

    GameObject::GameObject (Model* m,
                            Shader* s,
                            const Transform& tr):
        _active    { true },
        _transform { tr },
        _model     { m },
        _shader    { s },
        _collider  { nullptr },
        _rigidBody { nullptr }
    {}

    GameObject::GameObject (Model* m,
                            Shader* s):
        _active    { true },
        _model     {m},
        _shader    {s},
        _collider  { nullptr },
        _rigidBody { nullptr }
    {}

    GameObject::GameObject (const std::string& name,
                            Model* m,
                            Shader* s):
        _name      { name },
        _active    { true },
        _model     {m},
        _shader    {s},
        _collider  { nullptr },
        _rigidBody { nullptr }
    {}

    GameObject::GameObject (const std::string& name,
                            Model* m,
                            Shader* s,
                            const Transform& tr):
        _name      { name },
        _active    { true },
        _transform { tr },
        _model     { m },
        _shader    { s },
        _collider  { nullptr },
        _rigidBody { nullptr }
    {}

    GameObject::GameObject(const GameObject& gO):
        _name      { gO._name },
        _active    { gO._active },
        _transform { gO._transform },
        _model     { gO._model },
        _shader    { gO._shader },
        _collider  { nullptr },
        _rigidBody { nullptr }
    {
        if (gO._collider)
        {
            _collider = gO._collider->copy();
            _transform.setCollider(_collider);
        }
        if (gO._rigidBody)
            _rigidBody = new RigidBody(gO._rigidBody);

        // Copy each pointer of scene
        std::vector<GameObject*>::const_iterator it = gO._children.begin();
        for (; it != gO._children.end(); ++it)
        {
            // If the scene exists
            if (*it)
                // Push back a copy of the pointer of the scene
                _children.push_back(new GameObject(**it));
        }
    }

    GameObject::~GameObject()
    {
        if (_collider)
            delete _collider;

        if (_rigidBody)
            delete _rigidBody;

        removeChildren();
    }
	#pragma endregion

    #pragma region Operators
    GameObject& GameObject::operator=(const GameObject& gO) noexcept
    {
        _name      = gO._name;
        _active    = gO._active;
        _transform = gO._transform;
        _model     = gO._model;
        _shader    = gO._shader;
        _collider  = nullptr;
        _rigidBody = nullptr;

        if (gO._collider)
        {
            _collider = gO._collider->copy();
            _transform.setCollider(_collider);
        }
        if (gO._rigidBody)
            _rigidBody = new RigidBody(gO._rigidBody);

        // Copy each pointer of scene
        std::vector<GameObject*>::const_iterator it = gO._children.begin();
        for (; it != gO._children.end(); ++it)
        {
            // If the scene exists
            if (*it)
                // Push back a copy of the pointer of the scene
                _children.push_back(new GameObject(**it));
        }

        return *this;
    }
    #pragma endregion

	#pragma region Functions
    #pragma region GameObject
    GameObject& GameObject::update(Scene& scene, float deltaTime) noexcept
    {
        (void) scene;
        (void) deltaTime;
        
        return *this;
    }

    GameObject& GameObject::physicUpdate(Scene& scene, float deltaTime) noexcept
    {
        if (!_active || !_rigidBody)
            return *this;
            
        _rigidBody->physicUpdate(scene, _transform, _collider, deltaTime);
        
        return *this;
    }

    GameObject& GameObject::render(const Mat& viewMat, const Vec3& viewPos,
                    const std::vector<Light*>& lights, Mat transformParent)
        noexcept
    {
        if (!_active)
            return *this;
            
        // Update the matrix
        transformParent = transformParent * _transform.transform();

        // Render the current game object
        if (_shader &&  _model)
        {
            _shader->use();

            // Give the matrix to the shader
            _shader->setMatrix4("transform.viewMat", viewMat.elements);
            _shader->setMatrix4("transform.model", transformParent.elements);
            // Create the inverse matrix for the normals
            Mat invModM4 { transformParent.inverse().transpose() };
            float elements[9] { 
                invModM4.elements[0], invModM4.elements[1], invModM4.elements[2],
                invModM4.elements[4], invModM4.elements[5], invModM4.elements[6],
                invModM4.elements[8], invModM4.elements[9], invModM4.elements[10] };
            _shader->setMatrix3("transform.inverseModel", elements);
            _shader->setVec3   ("viewPos", viewPos);

            setLights(lights);

            _model->bindVAO();
            drawMaterials();
            _model->unbindVAO();

            _shader->unuse();
        }
        
        renderChildren(viewMat, viewPos, lights, transformParent);

        return *this;
    }

    void GameObject::setLights(const std::vector<Light*>& lights)
    {
        // Set the number of lights given
        _shader->setUint("nLights", lights.size());

        // Current index of the light
        int i = 0;
        // Go through all the lights
        for (auto it = lights.begin(); it != lights.end(); ++it)
        {
            // Set the value of the ith light to the shader
            (*it)->setValuesToShader(*_shader, i++);
        }
    }

    void GameObject::drawMaterials()
    {
        std::vector<Material>& materials = _model->materials();
        std::vector<std::pair<uint, uint>> indices = _model->indicesMaterial();

        for (auto it = indices.begin(); it != indices.end(); ++it)
        {
            uint materialIndex = it->second;
            if (materials.size() > materialIndex)
            {
                // Get the current material
                Material& mat = materials[materialIndex];
                mat.setValuesToShader(*_shader);

                // Get the number of indices to draw
                uint index = it->first;
                auto itNext = std::next(it, 1);
                uint nDraw = (itNext != indices.end()) // If next material
                    ? itNext->first - index   // Get indices to the next material
                    : _model->nIndices() - index; // Get indices to the end

                // Draw all the elements
                glDrawElements(GL_TRIANGLES, nDraw, GL_UNSIGNED_INT, (GLvoid*)(index * sizeof(GLfloat)));
                mat.unbind();
            }
        }
    }

    void GameObject::renderChildren(const Mat& viewMat, const Vec3& viewPos,
                                    const std::vector<Light*>& lights,
                                    Mat transformParent) noexcept
    {
        // Go throught all the children
        for (auto it = _children.begin(); it != _children.end(); ++it)
        {
            // Render the child if it exists
            if (*it)
                (*it)->render(viewMat, viewPos, lights, transformParent);
        }
    }

    GameObject* GameObject::addChild(GameObject* gO) noexcept
    {
        // Push it to the list of children
        _children.push_back(gO);

        return gO;
    }

    GameObject& GameObject::removeChild(GameObject* gO) noexcept
    {
        if (!gO)
            return *this;

        std::vector<GameObject*>::iterator itChildren = _children.begin();
        while (itChildren != _children.end())
        {
            if (*itChildren == gO)
            {
                (*itChildren)->removeChildren();
                delete *itChildren;
                _children.erase(itChildren);

                break;
            }
            ++itChildren;
        }

        return *this;
    }

    GameObject& GameObject::removeChildren() noexcept
    {
        // Remove each children's scene
        std::vector<GameObject*>::iterator itChildren = _children.begin();
        while (itChildren != _children.end())
        {
            if (*itChildren)
                delete *itChildren;

            itChildren = _children.erase(itChildren);
        }

        return *this;
    }

    bool GameObject::isActive() noexcept
    {
        return _active;
    }

    bool GameObject::hasCollider() noexcept
    {
        return _collider != nullptr;
    }

    bool GameObject::checkCollision(const Collider* collider, 
                                    const Vec3& speed, 
                                    float deltaTime, 
                                    SegmentHit*& hit) noexcept
    {
        if (!_active || !_collider || !collider || _collider == collider)
            return false;

        return collider->collide(*_collider, speed, deltaTime, hit);
    }

    bool GameObject::collideWithSegment(const Segment& s, SegmentHit*& hit) const noexcept
    {
        if (_active && _collider)
            return _collider->collideWithSegment(s, hit);
        return false;
    }

    GameObject& GameObject::onCollision(Scene& scene, Collider* collider, SegmentHit* hit) noexcept
    {
        (void) scene;
        (void) collider;
        (void) hit;

        return *this;
    }

    GameObject& GameObject::onTrigger(Scene& scene, Collider* collider, SegmentHit* hit) noexcept
    {
        (void) scene;
        (void) collider;
        (void) hit;

        return *this;
    }

    GameObject& GameObject::addRigidBody(bool useGravity, float mass,
                                         float friction) noexcept
    {
        _rigidBody = new RigidBody(useGravity, mass, friction);

        return *this;
    }

    GameObject& GameObject::addCollider(const EColliderType& type,
                                        bool isTrigger) noexcept
    {
        if (_collider)
        {
            delete _collider;
            _collider = nullptr;
        }
        
        _collider = Physics::Collisions::createColliderOfType(type, this, isTrigger);
        _transform.setCollider(_collider);
        _transform.updateMatrix();

        return *this;
    }

    bool GameObject::struckByBullet(Scene& scene, const Vec3& collPoint, 
                                    float damage) noexcept
    {
        (void) damage;

        scene.addChild(new Impact("ball impact",
			Model::createCube(scene.resourcesManager(), "resources/Bullet/impact.png"),
			scene.resourcesManager()->getShader (PATH_VERTEX, PATH_FRAGMENT),
			{collPoint, Vec3::zero, {0.05f, 0.05f, 0.05f}}
		), 2);

        return true;
    }

    bool GameObject::pickUpItem(ItemType type, uint numberOfItem) noexcept
    {
        (void) type;
        (void) numberOfItem;

        return false;
    }
    
    GameObject& GameObject::save(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept
    {
        saveGameObject(fs, resourcesManager);

        fs << "," << 0 << "," << 0 << "," << 0 << ","  << 0 << "," << 0 <<"\n";

        saveChildren(fs, resourcesManager, folderPath);

        return *this;
    }

    GameObject& GameObject::saveGameObject(std::ofstream& fs, ResourcesManager& resourcesManager) noexcept
    {
        //Crop the game object model name if it was created from a texxture
        std::string model = resourcesManager.findModelPathByValue(_model);
        if (model != "")
        {
            std::string textured = "Textured_";
            size_t texturedPos = model.find(textured);
            if (texturedPos != std::string::npos)
            {
                model = model.substr(texturedPos + textured.size());
            }
        }

        //Set the collider type and its trigger status in case the game object doesn't have a collider
        std::string colliderType = "";
        int colliderIsTrigger = 0;
        if (_collider)
        {
            colliderType = _collider->type();
            colliderIsTrigger = _collider->isTrigger();
        }

        //std::cout << "name : " << _name << std::endl;

        fs << _name << "," << model << 
        "," << _transform.position().x << "," << _transform.position().y << "," << _transform.position().z <<
        "," << _transform.rotation().x << "," << _transform.rotation().y << "," << _transform.rotation().z <<
        "," << _transform.scale().x << "," << _transform.scale().y << "," << _transform.scale().z <<
        "," << colliderType << "," << colliderIsTrigger;

        return *this;
    }

    GameObject& GameObject::saveChildren(std::ofstream& fs, ResourcesManager& resourcesManager, std::string folderPath) noexcept
    {
        std::vector<GameObject*>::iterator itChildren = _children.begin();
        for (;  itChildren != _children.end(); itChildren++)
        {
            if (*itChildren)
                (*itChildren)->save(fs,resourcesManager, folderPath);
        }

        return *this;
    }
    #pragma endregion

    #pragma region Transform
    void GameObject::translate(const Vec3& translation) noexcept
    {
        _transform.translate(translation);
    }

    void GameObject::rotate(const Vec3& rotation) noexcept
    {
        _transform.rotate(rotation);
    }

    void GameObject::grow(const Vec3& growth) noexcept
    {
        _transform.grow(growth);
    }

    void GameObject::setPosition(const Vec3& position) noexcept
    {
        _transform.setPosition(position);
    }

    void GameObject::setRotation(const Vec3& rotation) noexcept
    {
        _transform.setRotation(rotation);
    }

    void GameObject::setScale(const Vec3& scale) noexcept
    {
        _transform.setScale(scale);
    }

    void GameObject::updatePosition(const Vec3& pos) noexcept
    {
        _transform.updatePosition(pos);
    }

    void GameObject::updateRotation(const Vec3& rot) noexcept
    {
        _transform.updateRotation(rot);
    }

    void GameObject::updateScale(const Vec3& scale) noexcept
    {
        _transform.updateScale(scale);
    }

    void GameObject::updateMatrix() noexcept
    {
        _transform.updateMatrix();
    }
    #pragma endregion
	#pragma endregion
} /* LowRenderer */

// Bonne réflexions :)
