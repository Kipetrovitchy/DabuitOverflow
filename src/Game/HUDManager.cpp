#include "HUDManager.h"
#include "Text.h"
#include "Image.h"
#include "Canvas.h"
#include "GameMgr.h"
#include "Window.h"
#include "SaveManager.h"
#include "Vec4.h"

#pragma region Typedefs
typedef Core::Maths::Vec4 Vec4;
typedef Resources::Canvas Canvas;
#pragma endregion

namespace Game
{
    #pragma region Constructors / Destructors
    HUDManager::HUDManager() noexcept :
        _weapon { nullptr },
        _ammoInClip { nullptr },
        _ammoTotal { nullptr },
		_menuState { EMenuState::NONE },
		_lastMenuState { EMenuState::NONE }
    {}

    HUDManager::HUDManager(const HUDManager& hud) noexcept :
        _weapon { hud._weapon },
        _ammoInClip { hud._ammoInClip },
        _ammoTotal { hud._ammoTotal },
        _lifeBar { hud._lifeBar },
		_gameOverMsgs { hud._gameOverMsgs },
		_menuState { hud._menuState },
		_lastMenuState { hud._lastMenuState }
    {}
    #pragma endregion

    #pragma region Operators
    HUDManager& HUDManager::operator=(const HUDManager& hud) noexcept
    {
        _weapon = hud._weapon;
        _lifeBar = hud._lifeBar;
        _ammoInClip = hud._ammoInClip;
        _ammoTotal = hud._ammoTotal;

        return *this;
    }
    #pragma endregion

    #pragma region Methods
    HUDManager& HUDManager::init(GameMgr* game, ResourcesManager* mgr,
                                 GraphCanvas& graph, Player& player, LevelManager& lm) noexcept
    {
		//Create the interfaces for each case
        createMainMenu(game, mgr, graph);
        createHUD(game, mgr, graph);
		createEscMenu(game, mgr, graph);
		createOptionsMenu(game, mgr, graph);
    
		//Set the events for the player
        player.setUpdateHP([this](int a, int m) { updateHP(a, m);});
		player.setUpdateWeapon([this](Weapon* w) { updateWeapon(w);});
		player.setUpdateAmmo([this](int a, int m) { updateAmmo(a, m);});
		player.setUpdateMedkit([this](bool s) { updateMedkit(s);});
		lm.setUpdateEnemiesLeft([this](int left) { updateEnemiesLeft(left); });
        return *this;
    }

	HUDManager& HUDManager::updateMenuState(EMenuState state) noexcept
	{
		_lastMenuState = _menuState;
		_menuState = state;

		return *this;
	}
	
	HUDManager& HUDManager::update(float deltatime) noexcept
	{
		if (_gameOverMsgs.isWin())
			_johan.setActive();
		
		if (_menuState == EMenuState::MAIN)
			_johan.update(deltatime);

		return *this;
	}
    #pragma endregion

    #pragma region Private Functions
    void HUDManager::createMainMenu(GameMgr* game, ResourcesManager* mgr,
                                    GraphCanvas& graph)
    {
        Canvas* mainMenu { graph.addCanvas() };

		//Game title text
		UI::Text* title = new UI::Text(mgr->getFont(TEXT_FONT), 
									   mgr->getShader(TEXT_VERTEX, 
														   TEXT_FRAGMENT));
		title->transform().setAnchor(UI::EAnchor::TOPCENTER);
		title->transform().setAnchoredPosition({0, -70, 0});
		title->setWidth(400).setHeight(100);
		title->textAnchor() = UI::EAnchor::TOPCENTER;
		title->text() = L"Kill the Red Balls";
		title->textScale() = 0.3f;
		title->update();

		UI::Button* newGame = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		newGame->transform().setAnchor(UI::EAnchor::MIDLEFT);
		newGame->transform().setAnchoredPosition({200, 100, 0});
		newGame->setWidth(200).setHeight(75);
		newGame->text()->text() = L"New Game";
		newGame->text()->textScale() = 0.25f;
		newGame->text()->update();
		newGame->addListener([g = game]() { g->newGame(); });
		newGame->addListener([this]() { updateMenuState(EMenuState::NONE); });

		_loadGame = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		_loadGame->transform().setAnchor(UI::EAnchor::MIDLEFT);
		_loadGame->transform().setAnchoredPosition({200, 0, 0});
		_loadGame->setWidth(200).setHeight(75);
		_loadGame->text()->text() = L"Load Game";
		_loadGame->text()->textScale() = 0.25f;
		_loadGame->text()->update();
		_loadGame->addListener([g = game]() 
		{ 
			g->loadGame();
		});
		_loadGame->targetsColor().push_back(_loadGame->text());

		UI::Button* options = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		options->transform().setAnchor(UI::EAnchor::MIDLEFT);
		options->transform().setAnchoredPosition({200, -100, 0});
		options->setWidth(200).setHeight(75);
		options->text()->text() = L"Options";
		options->text()->textScale() = 0.25f;
		options->text()->update();
		options->addListener([g = game]() { g->goToOptionsMenu(); });

		UI::Button* quit = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		quit->transform().setAnchor(UI::EAnchor::MIDLEFT);
		quit->transform().setAnchoredPosition({200, -200, 0});
		quit->setWidth(200).setHeight(75);
		quit->text()->text() = L"Quit Game";
		quit->text()->textScale() = 0.25f;
		quit->text()->update();
		quit->addListener([g = game]() { g->quit(); });

		mainMenu->addChild(title);
		mainMenu->addChild(newGame);
		mainMenu->addChild(_loadGame);
		mainMenu->addChild(options);
		mainMenu->addChild(quit);

		_johan.init(mgr, mainMenu);
    }

	void HUDManager::createEscMenu(GameMgr* game, ResourcesManager* mgr,
								   GraphCanvas& graph)
	{

		Canvas* escMenu { graph.addCanvas() };

		UI::Image* bg = new UI::Image(mgr->getTexture(BG_IMG),
									 mgr->getShader(  IMG_VERTEX,
												      IMG_FRAGMENT));
		bg->color() = Vec4 { 0.f, 0.f, 0.f, 0.7f };
		bg->setWidth(3000).setHeight(3000);
		bg->transform().setAnchoredPosition({0, 0, -5.f});

		UI::Text* title = new UI::Text(mgr->getFont(TEXT_FONT), 
									   mgr->getShader(TEXT_VERTEX, 
														   TEXT_FRAGMENT));
		title->transform().setAnchor(UI::EAnchor::TOPCENTER);
		title->transform().setAnchoredPosition({0, -70, 0});
		title->setWidth(400).setHeight(100);
		title->textAnchor() = UI::EAnchor::TOPCENTER;
		title->text() = L"Pause Menu";
		title->textScale() = 0.3f;
		title->update();

		UI::Button* resume = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		resume->transform().setAnchor(UI::EAnchor::MIDCENTER);
		resume->transform().setAnchoredPosition({0, 100, 0});
		resume->setWidth(200).setHeight(75);
		resume->text()->text() = L"Resume";
		resume->text()->textScale() = 0.25f;
		resume->text()->update();
		resume->addListener([g = game]() { g->goToIngame(); });

		UI::Button* save = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		save->transform().setAnchor(UI::EAnchor::MIDCENTER);
		save->transform().setAnchoredPosition({0, 0, 0});
		save->setWidth(200).setHeight(75);
		save->text()->text() = L"Save";
		save->text()->textScale() = 0.25f;
		save->text()->update();
		save->addListener([g = game]() 
		{ 
			Resources::SaveManager::save(
				"resources/Save/Save1/", 
				g->graphScene()->currentScene());
		});

		UI::Button* options = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		options->transform().setAnchor(UI::EAnchor::MIDCENTER);
		options->transform().setAnchoredPosition({0, -100, 0});
		options->setWidth(200).setHeight(75);
		options->text()->text() = L"Options";
		options->text()->textScale() = 0.25f;
		options->text()->update();
		options->addListener([g = game]() { g->goToOptionsMenu(); });

		UI::Button* quit = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   mgr->getFont(  TEXT_FONT),
										   mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		quit->transform().setAnchor(UI::EAnchor::MIDCENTER);
		quit->transform().setAnchoredPosition({0, -200, 0});
		quit->setWidth(200).setHeight(75);
		quit->text()->text() = L"Main Menu";
		quit->text()->textScale() = 0.25f;
		quit->text()->update();
		quit->addListener([&g = *game]() { g.goToMainMenu(); });

		escMenu->addChild(title);
		escMenu->addChild(resume);
		escMenu->addChild(save);
		escMenu->addChild(options);
		escMenu->addChild(quit);
		escMenu->addChild(bg);
	}

	void HUDManager::createOptionsMenu(GameMgr* game, ResourcesManager* mgr,
        				               GraphCanvas& graph)
	{
		Canvas* options { graph.addCanvas() };

		UI::Image* bg = new UI::Image(mgr->getTexture(BG_IMG),
									 mgr->getShader(  IMG_VERTEX,
												      IMG_FRAGMENT));
		bg->color() = Vec4 { 0.f, 0.f, 0.f, 0.7f };
		bg->setWidth(3000).setHeight(3000);
		bg->transform().setAnchoredPosition({0, 0, -5.f});

		UI::Text* title = new UI::Text(mgr->getFont(TEXT_FONT), 
									   mgr->getShader(TEXT_VERTEX, 
														   TEXT_FRAGMENT));
		title->transform().setAnchor(UI::EAnchor::TOPCENTER);
		title->transform().setAnchoredPosition({0, -70, 0});
		title->setWidth(400).setHeight(100);
		title->textAnchor() = UI::EAnchor::TOPCENTER;
		title->text() = L"Options";
		title->textScale() = 0.3f;
		title->update();

		UI::Button* res1280x720 = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   		 mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   		 mgr->getFont(  TEXT_FONT),
										   		 mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		res1280x720->transform().setAnchor(UI::EAnchor::MIDLEFT);
		res1280x720->transform().setAnchoredPosition({100, 70, 0});
		res1280x720->setWidth(150);
		res1280x720->text()->text() = L"1280x720";
		res1280x720->text()->update();
		res1280x720->addListener([w = game->window()](){w->reshape(1280, 720);});
		res1280x720->targetsColor().push_back(res1280x720->text());

		UI::Button* res1024x600 = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   		 mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   		 mgr->getFont(  TEXT_FONT),
										   		 mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		res1024x600->transform().setAnchor(UI::EAnchor::MIDLEFT);
		res1024x600->transform().setAnchoredPosition({100, 20, 0});
		res1024x600->setWidth(150);
		res1024x600->text()->text() = L"1024x600";
		res1024x600->text()->update();
		res1024x600->addListener([w = game->window()](){w->reshape(1024, 600);});
		res1024x600->targetsColor().push_back(res1024x600->text());

		UI::Button* fullscreen = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   		 mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   		 mgr->getFont(  TEXT_FONT),
										   		 mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		fullscreen->transform().setAnchor(UI::EAnchor::MIDLEFT);
		fullscreen->transform().setAnchoredPosition({100, 125, 0});
		fullscreen->setWidth(150);
		fullscreen->text()->text() = L"Fullscreen";
		fullscreen->text()->update();
		fullscreen->addListener([w = game->window(), res1 = res1024x600, res2 = res1280x720]()
								{
									w->setFullscreen(true);
									res1->disableUpdate(true);
									res2->disableUpdate(true);
								});

		UI::Button* windowed = new UI::Button(mgr->getTexture(BUTTON_IMG),
										   		 mgr->getShader(IMG_VERTEX,
										   					   IMG_FRAGMENT),
										   		 mgr->getFont(  TEXT_FONT),
										   		 mgr->getShader(TEXT_VERTEX,
										                       TEXT_FRAGMENT));
		windowed->transform().setAnchor(UI::EAnchor::MIDLEFT);
		windowed->transform().setAnchoredPosition({270, 125, 0});
		windowed->setWidth(150);
		windowed->text()->text() = L"Windowed";
		windowed->text()->update();
		windowed->addListener([w = game->window(), res1 = res1024x600, res2 = res1280x720]()
								{
									w->setFullscreen(false);
									res1->disableUpdate(false);
									res2->disableUpdate(false);
								});

		UI::Button* back = new UI::Button(mgr->getTexture(BUTTON_IMG),
										  mgr->getShader(IMG_VERTEX,
										   				 IMG_FRAGMENT),
										  mgr->getFont(  TEXT_FONT),
										  mgr->getShader(TEXT_VERTEX,
										                 TEXT_FRAGMENT));
		back->transform().setAnchor(UI::EAnchor::BOTCENTER);
		back->transform().setAnchoredPosition({0, 70, 0});
		back->setWidth(200).setHeight(75);
		back->text()->text() = L"Back";
		back->text()->update();
		back->addListener([g = game](){g->goToLastMenu();});

		options->addChild(title);
		options->addChild(res1280x720);
		options->addChild(res1024x600);
		options->addChild(windowed);
		options->addChild(fullscreen);
		options->addChild(back);
		options->addChild(bg);

	}
    void HUDManager::createHUD(GameMgr* game, ResourcesManager* mgr,
                    GraphCanvas& graph)
    {
        (void)game;
        Canvas* HUD { graph.addCanvas() };
		_weapon = new UI::Image(mgr->getTexture(OUTLINE_IMG),
								mgr->getShader(IMG_VERTEX,
													IMG_FRAGMENT));
		_weapon->setWidth(200);
		_weapon->setHeight(200);
		_weapon->transform().setAnchoredPosition(Vec3{ -110.f, 110.f, 0});
		_weapon->transform().setAnchor(UI::EAnchor::BOTRIGHT);
		_weapon->color() = Vec4 { 1, 1, 1, 0.5};

		_lifeBar.init(mgr, HUD);

		_ammoInClip = new UI::Text(mgr->getFont(TEXT_FONT), 
							    mgr->getShader(TEXT_VERTEX, 
											   TEXT_FRAGMENT));
		_ammoInClip->transform().setAnchor(UI::EAnchor::BOTRIGHT);
		_ammoInClip->transform().setAnchoredPosition({-120, 35, 1});
		_ammoInClip->textAnchor() = UI::EAnchor::BOTRIGHT;
		_ammoInClip->textScale() = 0.3f;
		_ammoInClip->text() = L"Ammo here";
		_ammoInClip->setWidth(100).setHeight(50);

		_ammoTotal = new UI::Text(mgr->getFont(TEXT_FONT), 
							    mgr->getShader(TEXT_VERTEX, 
											   TEXT_FRAGMENT));
		_ammoTotal->transform().setAnchor(UI::EAnchor::BOTRIGHT);
		_ammoTotal->transform().setAnchoredPosition({-60, 35, 1});
		_ammoTotal->textAnchor() = UI::EAnchor::BOTRIGHT;
		_ammoTotal->text() = L"Ammo here";
		_ammoTotal->setWidth(100).setHeight(50);
		

		_enemyLeft = new UI::Text(mgr->getFont(TEXT_FONT), 
							      mgr->getShader(TEXT_VERTEX, 
											     TEXT_FRAGMENT));
		_enemyLeft->transform().setAnchor(UI::EAnchor::TOPRIGHT);
		_enemyLeft->transform().setAnchoredPosition({-120, -45, 1});
		_enemyLeft->textAnchor() = UI::EAnchor::TOPRIGHT;
		_enemyLeft->text() = L"Enemies left :";
		_enemyLeft->setWidth(200).setHeight(50);

		UI::Image* cross = new Image(mgr->getTexture(CROSS_IMG),
									mgr->getShader(IMG_VERTEX,
													IMG_FRAGMENT));
		cross->setWidth(30).setHeight(30);

		_medkit = new Image(mgr->getTexture(MEDKIT_IMG),
								  mgr->getShader( IMG_VERTEX,
												  IMG_FRAGMENT));
		_medkit->setWidth(60).setHeight(60);
		_medkit->transform().setAnchor(UI::EAnchor::TOPLEFT);
		_medkit->transform().setAnchoredPosition({40, -110, 0.f});
		_medkit->setActive(false);
		HUD->addChild(_ammoInClip);
		HUD->addChild(_ammoTotal);
		HUD->addChild(_weapon);
		HUD->addChild(_enemyLeft);
		HUD->addChild(cross);
		HUD->addChild(_medkit);

		_gameOverMsgs.init(mgr, HUD, 2.f);
    }

    void HUDManager::updateHP(int actual, int max) noexcept
    {
        _lifeBar.updateHP(actual, max);
    }

	void HUDManager::updateWeapon(Weapon* mainWeapon) noexcept
	{
		_weapon->texture() = mainWeapon->texture();
	}

	void HUDManager::updateAmmo(int inClip, int inInventory) noexcept
	{
		_ammoInClip->text() = std::to_wstring(inClip);
		_ammoInClip->update();

		if (inClip <= 0)
			_ammoInClip->color() = Vec4 {1, 0, 0, 1};
		else
			_ammoInClip->color() = Vec4 {1, 1, 1, 1};

		_ammoTotal->text() = std::to_wstring(inInventory - inClip);
		_ammoTotal->update();

		if (inInventory - inClip <= 0)
			_ammoTotal->color() = Vec4 {1, 0, 0, 1};
		else
			_ammoTotal->color() = Vec4 {1, 1, 1, 1};
	}

	void HUDManager::updateMedkit(bool state) noexcept
	{
		if (state)
			_medkit->setActive(true);
		else
			_medkit->setActive(false);
	}
	
	void HUDManager::updateEnemiesLeft(int left) noexcept
	{
		if (left > 1)
			_enemyLeft->text() = L"Enemies left : " + std::to_wstring(left);
		else 
			_enemyLeft->text() = L"Enemy left : " + std::to_wstring(left); 

		_enemyLeft->update();
	}
    #pragma endregion
} // namespace Game
