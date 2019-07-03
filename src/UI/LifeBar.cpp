#include "LifeBar.h"

namespace UI
{
    #pragma region Constructors / Destructors
    LifeBar::LifeBar() noexcept :
        _fg { nullptr },
        _bg { nullptr }
    {}

    LifeBar::LifeBar(const LifeBar& lifebar) noexcept :
        _fg { lifebar._fg },
        _bg { lifebar._bg }
    {}

    LifeBar::LifeBar(ResourcesManager* mgr, Canvas* hud) noexcept :
        _fg { nullptr },
        _bg { nullptr}
    {
        init(mgr, hud);
    }
    #pragma endregion

    #pragma region Operators
    LifeBar& LifeBar::operator=(const LifeBar& lifebar) noexcept
    {
        _fg = lifebar._fg;
        _bg = lifebar._bg;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    LifeBar& LifeBar::init(ResourcesManager* mgr, Canvas* hud)
    {
        _bg = new Image(mgr->getTexture("./resources/Life Bar/bg.png"),
                        mgr->getShader( "./resources/Shaders/image.vs",
                                        "./resources/Shaders/image.fs"));
        _bg->setHeight(50).setWidth(300);
        _bg->transform().setAnchor(EAnchor::TOPLEFT);
        _bg->transform().setAnchoredPosition({160, -35, -1.f});

        _fg = new Image(mgr->getTexture("./resources/bg.png"),
                        mgr->getShader( "./resources/Shaders/image.vs",
                                        "./resources/Shaders/image.fs"));
        _fg->setHeight(50).setWidth(300);
        _fg->transform().setAnchor(EAnchor::TOPLEFT);
        _fg->transform().setAnchoredPosition({160, -35, 0.f});
        _fg->color() = Vec4 {  0.31372549019,  0.62745098039,   0.15686274509, 1};
        // _fg->color() = Vec4 {  0.33725490196,  0.65882352941,  0.33725490196, 1};

        hud->addChild(_fg);
        hud->addChild(_bg);

        return *this;
    }

    LifeBar& LifeBar::updateHP(int actual, int max)
    {
        float newWidth { 300 * (actual / (float)max) };

        _fg->setWidth(newWidth);
        _fg->transform().setAnchoredPosition({newWidth / 2.f + 10, -35.f, 0.f});

        return *this;
    }
    #pragma endregion
} // namespace UI
