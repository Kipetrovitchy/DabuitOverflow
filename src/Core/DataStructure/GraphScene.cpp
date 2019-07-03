#include "GraphScene.h"

namespace Core::DataStructure
{
    #pragma region Constructors
    GraphScene::GraphScene():
        _actualScene { 0 }
    {
        _scenes.push_back(new Scene());
    }

    GraphScene::GraphScene(const GraphScene& g):
        _actualScene { g._actualScene }
    {
        std::vector<Scene*>::const_iterator it = g._scenes.begin();
        // Copy the scenes
        for (; it != g._scenes.end(); ++it)
            if (*it)
                _scenes.push_back(new Scene(**it));
    }

    GraphScene::~GraphScene()
    {
        empty();
    }
    #pragma endregion

    #pragma region Operators
    GraphScene& GraphScene::operator=(const GraphScene& g)
    {
        // Empty the list of scenes
        empty();

        // Copy the values
        _actualScene = g._actualScene;

        // Copy all the scenes
        std::vector<Scene*>::const_iterator itScene = g._scenes.begin();
        for (; itScene != g._scenes.end(); ++itScene)
            if (*itScene)
                _scenes.push_back(new Scene(**itScene));

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    void GraphScene::update(float deltaTime) noexcept
    {
        Scene* curr = currentScene();

        if (curr)
            curr->update(deltaTime);
    }

    void GraphScene::physicUpdate(float deltaTime) noexcept
    {
        Scene* curr = currentScene();

        if (curr)
            curr->physicUpdate(deltaTime);
    }

    void GraphScene::draw(Mat& viewProj, const Vec3& camPos) noexcept
    {
        Scene* scene = currentScene();

        // Draw the scene give the projection and the camera first
        if (scene)
            scene->render(viewProj, camPos);
    }

    uint GraphScene::addScene() noexcept
    {
        // Add the scene
        _scenes.push_back(new Scene());

        // Return the indices of the created scene
        return _scenes.size() - 1;
    }

     uint GraphScene::addScene(Scene* scene) noexcept
    {
        // Add the scene
        _scenes.push_back(scene);

        // Return the indices of the created scene
        return _scenes.size() - 1;
    }

    void GraphScene::changeScene(uint scene) noexcept
    {
        // Only change the scene if it exists
        if (scene < _scenes.size())
            _actualScene = scene;
    }

    void GraphScene::empty() noexcept
    {
        // Remove each children's scene
        std::vector<Scene*>::iterator it = _scenes.begin();
        while (it != _scenes.end())
        {
            if (*it)
                delete *it;

            it = _scenes.erase(it);
        }
    }
    #pragma endregion

    #pragma region Attributes
    Scene*  GraphScene::currentScene() noexcept
    {
        if (_actualScene < _scenes.size())
            return _scenes[_actualScene];

        return nullptr;
    }
    #pragma endregion
} /* Core::DataStructure */
