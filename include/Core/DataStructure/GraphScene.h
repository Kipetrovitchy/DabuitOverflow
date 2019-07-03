#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <vector>
#include <SDL2/SDL.h>

#include "LibMaths.h"
#include "Scene.h"
#include "InputMgr.h"

namespace Core::DataStructure
{
    #pragma region Typedefs
    typedef unsigned int        uint;
    typedef Resources::Scene        Scene;
    typedef Core::Maths::Mat        Mat;
    typedef Core::Maths::Vec3       Vec3;
    typedef Game::Inputs::InputMgr  InputMgr;
    #pragma endregion

    class GraphScene
    {
    private:
        #pragma region Attributes
        std::vector<Scene*> _scenes;
        uint                _actualScene;
        #pragma endregion

    public:
        #pragma region Constructors
        GraphScene();
        GraphScene(const GraphScene& g);
        ~GraphScene();
        #pragma endregion

        #pragma region Operators
        GraphScene& operator=(const GraphScene& g);
        #pragma endregion

        #pragma region Functions
        void update      (float deltaTime) noexcept;
        void physicUpdate(float deltaTime) noexcept;
        void draw(Mat& viewProj, const Vec3& camPos) noexcept;

        uint addScene() noexcept;
        uint addScene(Scene* scene) noexcept;
        void changeScene(uint scene) noexcept;
        void empty() noexcept;
        #pragma endregion

        #pragma region Accessors
        Scene*  currentScene()   noexcept;
        #pragma endregion
    };
} /* Core::DataStructure */

#endif//__GRAPH_H__
