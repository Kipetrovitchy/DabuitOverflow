#include "Johan.h"

namespace UI
{
    #pragma region Constructors / Destructors
    Johan::Johan() noexcept :
        _flo { nullptr },
        _sam { nullptr },
        _paul { nullptr },
        _etienne { nullptr },
        _insaneProducerGroup { nullptr },
        _ty { nullptr },
        _rotation { 0.f },
        _enabled { false }
    {}
    #pragma endregion

    #pragma region Methods
    Johan& Johan::init(ResourcesManager* mgr, Canvas* mainMenu) noexcept
    {
        _flo = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
                        mgr->getShader("./resources/Shaders/text.vsh", 
                                       "./resources/Shaders/text.fsh"));
        _flo->text() = L"Florian";
        _flo->transform().setAnchoredPosition({-20, 80, 0.f});
        _flo->setWidth(300).setHeight(100);
        _flo->setActive(false);

        _sam = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
                        mgr->getShader("./resources/Shaders/text.vsh", 
                                       "./resources/Shaders/text.fsh"));
        _sam->text() = L"Samuel";
        _sam->transform().setAnchoredPosition({300, -100, 0.f});
        _sam->setWidth(300).setHeight(100);
        _sam->setActive(false);

        _paul = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
                        mgr->getShader("./resources/Shaders/text.vsh", 
                                       "./resources/Shaders/text.fsh"));
        _paul->text() = L"Paul";
        _paul->transform().setAnchoredPosition({200, 110, 0.f});
        _paul->setWidth(300).setHeight(100);
        _paul->setActive(false);

        _etienne = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
                        mgr->getShader("./resources/Shaders/text.vsh", 
                                       "./resources/Shaders/text.fsh"));
        _etienne->text() = L"Etienne";
        _etienne->transform().setAnchoredPosition({-75, -100, 0.f});
        _etienne->setWidth(300).setHeight(100);
        _etienne->setActive(false);

        _insaneProducerGroup = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
                        mgr->getShader("./resources/Shaders/text.vsh", 
                                       "./resources/Shaders/text.fsh"));
        _insaneProducerGroup->text() = L"Produced by Dabuito";
        _insaneProducerGroup->textAnchor() = EAnchor::BOTRIGHT;
        _insaneProducerGroup->transform().setAnchor(EAnchor::BOTRIGHT);
        _insaneProducerGroup->transform().setAnchoredPosition({-260, 60, 0.f});
        _insaneProducerGroup->setWidth(500).setHeight(100);
        _insaneProducerGroup->setActive(false);

        _ty = new Text(mgr->getFont(  "./resources/ProductSans-Medium.ttf"), 
                        mgr->getShader("./resources/Shaders/text.vsh", 
                                       "./resources/Shaders/text.fsh"));
        _ty->text() = L"Thanks To";
        _ty->transform().setAnchoredPosition({100.f, 0.f, 0.f});
        _ty->textScale() = 0.25f;
        _ty->setWidth(300).setHeight(100);
        _ty->setActive(false);

        mainMenu->addChild(_flo);
        mainMenu->addChild(_sam);
        mainMenu->addChild(_paul);
        mainMenu->addChild(_etienne);
        mainMenu->addChild(_insaneProducerGroup);
        mainMenu->addChild(_ty);

        return *this;
    }

    Johan& Johan::update(float deltatime) noexcept
    {
        _rotation += deltatime;

        _flo->transform().setRotation({0.3f * _rotation, 0.9f * _rotation, 0.61f * _rotation});
        _sam->transform().setRotation({0.4f * _rotation, 0.1f * _rotation, 0.5f * _rotation});
        _paul->transform().setRotation({0.3f * _rotation, 0.9f * _rotation, 0.31f * _rotation});
        _etienne->transform().setRotation({0.9f * _rotation, 0.3f * _rotation, 0.15f * _rotation});
        _ty->transform().setRotation({0.0f, 0.0f, _rotation});
        return *this;
    }

    Johan& Johan::setActive() noexcept
    {
        if (!_enabled)
        {
            _flo->setActive(true);
            _sam->setActive(true);
            _paul->setActive(true);
            _etienne->setActive(true);
            _insaneProducerGroup->setActive(true);
            _ty->setActive(true);
        }

        return *this;
    }
    #pragma endregion
} // namespace UI
