#include "GameOverMsgs.h"

namespace UI
{
    #pragma region Constructors / Desctructors
    GameOverMsgs::GameOverMsgs() noexcept :
        _winMsg { nullptr },
        _looseMsg { nullptr },
        _baseCdShown { 1.f },
        _cd { 1.f }
    {}
    GameOverMsgs::GameOverMsgs(ResourcesManager* mgr, Canvas* hud, float cd) noexcept
    {
        init(mgr, hud, cd);
    }
    GameOverMsgs::GameOverMsgs(const GameOverMsgs& copy)  noexcept :
        _winMsg { copy._winMsg },
        _looseMsg { copy._looseMsg },
        _baseCdShown { copy._baseCdShown },
        _cd { copy._cd }
    {}
    #pragma endregion

    #pragma region Operators
    GameOverMsgs& GameOverMsgs::operator=(const GameOverMsgs& copy) noexcept
    {
        _winMsg = copy._winMsg;
        _looseMsg = copy._looseMsg;
        _baseCdShown = copy._baseCdShown;
        _cd = copy._cd;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    GameOverMsgs& GameOverMsgs::init(ResourcesManager* mgr, Canvas* hud, float cd)
    {
        _baseCdShown = cd;
        _cd = cd;
        _winMsg = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
						   mgr->getShader("./resources/Shaders/text.vsh", 
                                          "./resources/Shaders/text.fsh"));
        _winMsg->transform().setAnchoredPosition({0.f, 0.f, 0.f});
        _winMsg->text() = L"YOU WIN !";
        _winMsg->textAnchor() = EAnchor::MIDCENTER;
        _winMsg->textScale() = 0.5f;
        _winMsg->update();
        _winMsg->setActive(false);

        _looseMsg = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
						   mgr->getShader("./resources/Shaders/text.vsh", 
                                          "./resources/Shaders/text.fsh"));
        _looseMsg->transform().setAnchoredPosition({0.f, 0.f, 0.f});
        _looseMsg->text() = L"YOU LOOSE !";
        _looseMsg->textAnchor() = EAnchor::MIDCENTER;
        _looseMsg->textScale() = 0.5f;
        _looseMsg->update();
        _looseMsg->color() = Vec4 {1.f, 0.f, 0.f, 1.f};
        _looseMsg->setActive(false);

        _bg = new Image(mgr->getTexture("./resources/bg.png"),
                        mgr->getShader( "./resources/Shaders/image.vs",
                                        "./resources/Shaders/image.fs"));
        _bg->setWidth(Canvas::windowTransform().width());
        _bg->setHeight(Canvas::windowTransform().height());
        _bg->color() = Vec4 { 0.f, 0.f, 0.f, 0.f};
        _bg->transform().setAnchoredPosition({0.f, 0.f, -0.1f});

        hud->addChild(_looseMsg);
        hud->addChild(_winMsg);
        hud->addChild(_bg);
        return *this;
    }

    GameOverMsgs& GameOverMsgs::showWin() noexcept
    {
        _winMsg->setActive(true);
        _bg->setWidth(Canvas::windowTransform().width());
        _bg->setHeight(Canvas::windowTransform().height());

        return *this;
    }
    GameOverMsgs& GameOverMsgs::showLoose() noexcept
    {
        _looseMsg->setActive(true);
        _bg->setWidth(Canvas::windowTransform().width());
        _bg->setHeight(Canvas::windowTransform().height());

        return *this;
    }


    bool GameOverMsgs::updateWin(float deltatime) noexcept
    {
        _cd -= deltatime;

        float ratio { (_baseCdShown - _cd) / _baseCdShown };

        _winMsg->setWidth(Canvas::windowTransform().width() * ratio);
        _winMsg->setHeight(Canvas::windowTransform().height() * ratio);

        _bg->color() = Vec4 { 0.f, 0.f, 0.f, ratio };
        if (_cd <= 0)
        {
            _bg->color() = Vec4 { 0.f, 0.f, 0.f, 0.f };
            _winMsg->setActive(false);
            _cd = _baseCdShown;
            return true;
        }

        return false;
    }

    bool GameOverMsgs::updateLoose(float deltatime) noexcept
    {
        _cd -= deltatime;

        float ratio { (_baseCdShown - _cd) / _baseCdShown };

        _looseMsg->setWidth(Canvas::windowTransform().width() * ratio);
        _looseMsg->setHeight(Canvas::windowTransform().height() * ratio);

        _bg->color() = Vec4 { 0.f, 0.f, 0.f, ratio };

        if (_cd <= 0)
        {
            _bg->color() = Vec4 { 0.f, 0.f, 0.f, 0.f };
            _looseMsg->setActive(false);
            _cd = _baseCdShown;
            return true;
        }

        return false;
    }
    #pragma endregion
} // namespace UI
