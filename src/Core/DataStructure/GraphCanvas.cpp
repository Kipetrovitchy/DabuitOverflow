#include "GraphCanvas.h"

namespace Core::DataStructure
{
    #pragma region Constructors / Destructors
    GraphCanvas::GraphCanvas() :
        _actualCanvas { 0 }
    {}
    GraphCanvas::GraphCanvas(const GraphCanvas& g) :
        _actualCanvas { g._actualCanvas}
    {
        for (auto it = g._canvas.begin(); it != g._canvas.end(); ++it)
            if (*it)
                _canvas.push_back(new Canvas(**it));
    }
    GraphCanvas::~GraphCanvas()
    {
        empty();
    }
    #pragma endregion

    #pragma region Operators
    GraphCanvas& GraphCanvas::operator=(const GraphCanvas& g)
    {
        _actualCanvas = g._actualCanvas;
        for (auto it = g._canvas.begin(); it != g._canvas.end(); ++it)
            if (*it)
                _canvas.push_back(new Canvas(**it));

        return *this;
    }
    #pragma endregion

    #pragma region Functions
    void GraphCanvas::update(const InputModule& module) noexcept
    {
        Canvas* current = { currentCanvas() };

        current->update(module);
    }

    void GraphCanvas::render(const Mat& viewProj, Vec3 camPos) noexcept
    {
        Canvas* current = { currentCanvas() };

        current->render(viewProj, camPos);
    }

    Canvas* GraphCanvas::addCanvas() noexcept
    {
        Canvas* newCanvas { new Canvas() };
        // Add the scene
        _canvas.push_back(newCanvas);

        // Return the indices of the created scene
        return newCanvas;
    }

    void GraphCanvas::changeCanvas(uint canvas) noexcept
    {
        // Only change the scene if it exists
        if (canvas < _canvas.size())
            _actualCanvas = canvas;
    }

    void GraphCanvas::empty() noexcept
    {
        for (auto it = _canvas.begin(); it != _canvas.end(); ++it)
            if (*it)
                delete *it;
    }

    void GraphCanvas::resizeCanvas() noexcept
    {
        for (auto it = _canvas.begin(); it != _canvas.end(); ++it)
            (*it)->updateChildrenTransform();
    }
    #pragma endregion

    #pragma region Accessors
    Canvas*  GraphCanvas::currentCanvas() noexcept
    {
        return _canvas[_actualCanvas];
    }
    #pragma endregion
} // namespace Core::Datastructure
