#ifndef __GRAPHCANVAS_H__
#define __GRAPHCANVAS_H__

#include "Canvas.h"
#include "InputModule.h"
#include "LibMaths.h"

namespace Core::DataStructure
{
    #pragma region Typedefs
    typedef Resources::Canvas           Canvas;
    typedef Game::Inputs::InputModule   InputModule;
    typedef Core::Maths::Mat            Mat;
    typedef Core::Maths::Vec3           Vec3;
    #pragma endregion

    class GraphCanvas
    {
    private:
        #pragma region Attributes
        std::vector<Canvas*>    _canvas;
        uint                    _actualCanvas;
        #pragma endregion

    public:
        #pragma region Constructors
        GraphCanvas();
        GraphCanvas(const GraphCanvas& g);
        ~GraphCanvas();
        #pragma endregion

        #pragma region Operators
        GraphCanvas& operator=(const GraphCanvas& g);
        #pragma endregion

        #pragma region Functions
        void update      (const InputModule& module)        noexcept;
        void render      (const Mat& viewProj, Vec3 camPos) noexcept;

        Canvas* addCanvas() noexcept;
        void changeCanvas(uint canvas) noexcept;
        void empty() noexcept;
        void resizeCanvas() noexcept;
        #pragma endregion

        #pragma region Accessors
        Canvas*  currentCanvas()   noexcept;
        #pragma endregion
    };
} // namespace Core::Datastructure

#endif // __GRAPHCANVAS_H__