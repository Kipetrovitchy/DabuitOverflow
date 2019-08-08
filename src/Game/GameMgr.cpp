#include <GL/glew.h>
#include <iostream>
#include "GameMgr.h"
#include "Window.h"
#include "Log.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "3DCollisions.h"
#include "SegmentHit.h"
#include "BoxCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Canvas.h"
#include "Camera.h"
#include <cmath>
#include "SaveManager.h"
#include "Skybox.h"

namespace Game
{
	typedef LowRenderer::DirectionalLight 	DirectionalLight;
	typedef LowRenderer::PointLight 		PointLight;
	typedef LowRenderer::SpotLight  		SpotLight;
	typedef LowRenderer::Camera 			Camera;

	GameMgr::GameMgr():
		_gameState		{ EGameState::NONE },
		_window 		{ nullptr },
		_manager		{ nullptr },
		_graphScene		{ nullptr },
		_camera			{ nullptr },
		_cameraUI		{ nullptr },
		_player			{ nullptr },
		_hudMgr			{ nullptr },
		_levelMgr		{ nullptr },
		_needQuit		{ false },
		_cancelBounce	{ false },
		_timeScale		{ BASE_TIME_SCALE },
		_physicCooldown { s_physicCooldownMax }
	{}

	GameMgr::~GameMgr()
	{
		delete _inputs;
		delete _manager;
		delete _graphScene;
		delete _graphCanvas;
		delete _camera;
		delete _cameraUI;
		delete _hudMgr;
		delete _levelMgr;
	}

	void GameMgr::setRenderWindow(Window* window)
	{
		_window = window;
	}

	void GameMgr::setTimeScale(float scale)
	{
		if (scale > 1.0f || scale < 0.0f)
			return;

		_timeScale = scale;
	}

	bool GameMgr::init(uint width, uint height)
	{
		Resources::Canvas::windowTransform()->setWidth(width);
		Resources::Canvas::windowTransform()->setHeight(height);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_LESS, 1);
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		try
		{
			_inputs			= new InputMgr();
			_manager		= new ResourcesManager();
			_graphScene   	= new GraphScene();
			_graphCanvas	= new GraphCanvas();
			_camera			= new Camera3D(width, height);
			_cameraUI		= new CameraUI(width, height, {0, 0, 100}, {0, 0, -1}, Vec3::down);
		}
		catch(std::string s)
		{
			return false;
		}
		initScene();
		_hudMgr = new HUDManager();
		_levelMgr = new LevelManager(_player, &_hudMgr->gameOverMsgs());
		_hudMgr->init(this, _manager, *_graphCanvas, *_player, *_levelMgr);
		_camera->target() = &_player->transform();
		_inputs->init(*_player);

		goToMainMenu();

		return true;
	}

	bool GameMgr::initScene()
	{
		_graphScene->addScene();
		_graphScene->addScene();
		_graphScene->changeScene(1);

		_graphScene->currentScene()->resourcesManager() = _manager;

		_player = new Game::Player(
			"Player",
			nullptr,
			_manager->getShader (PATH_VERTEX, PATH_FRAGMENT),
			// {{36,5,30}, {0.f, 0.f, 0.0f}, Vec3::one},
			{{1.5f, 2.0f, 1.5f}, {0.f, 0.f, 0.0f}, Vec3::one},
			_camera, 100.0f, 4.0f);
		_player->loadGunModel();
		_graphScene->currentScene()->addChild(_player);
		_player->inventory().init(_player, _manager);

		// PickableItem* pI = new PickableItem("ammo",
		// 	_manager->getModel  ("resources/Crate/crate.obj"),
		// 	_manager->getShader (PATH_VERTEX, PATH_FRAGMENT),
		// 	{{-4.0f, 1.5f, 4.0f}, Vec3::zero, {1.0f, 1.0f, 1.0f}},
		// 	ItemType::RIFLE_AMMO, 10);
		// _graphScene->currentScene()->addChild(pI);

		PickableItem* pI2 = new PickableItem("health",
			_manager->getModel  (".\\resources\\Crate\\crate.obj"),
			_manager->getShader (PATH_VERTEX, PATH_FRAGMENT),
			{{4.0f, 1.0f, 1.5f}, Vec3::zero, {0.5f, 0.5f, 0.5f}},
			ItemType::MEDIKIT, 1);
		_graphScene->currentScene()->addChild(pI2);

		initLights();

		return true;
	}

	void GameMgr::initCrates(GameObject* parent)
	{
		(void) parent;
	}

	void GameMgr::initLights()
	{
		DirectionalLight* dl = new DirectionalLight(
			{-0.6f, -1.0f, -0.2f}, {0.45f}, 0.8f);

		_graphScene->currentScene()->addLight(dl);
		_graphScene->currentScene()->addLight(new PointLight({3.0f,  2.0f,  7.0f}, {0.7f, 0.6f, 0.3f}, 0.0f));
		_graphScene->currentScene()->addLight(new PointLight({14.0f, 2.0f, 13.0f}, {0.7f, 0.6f, 0.3f}, 0.0f));
		_graphScene->currentScene()->addLight(new SpotLight ({25.0f, 5.0f, 9.0f}, {0.5f, 0.35f, 0.15f}, 0.0f, {1.0f, 0.09f, 0.032f}, {-0.3f, -1.0f, -0.3f}));
		_graphScene->currentScene()->addLight(new SpotLight ({25.0f, 5.0f, 17.0f}, {0.5f, 0.35f, 0.15f}, 0.0f, {1.0f, 0.09f, 0.032f}, {-0.3f, -1.0f, 0.3f}));
		_graphScene->currentScene()->addLight(new PointLight({28.0f, 2.0f, 13.0f}, {0.7f, 0.6f, 0.3f}, 0.0f, {1.0f, 0.22f, 0.20f}));
		_graphScene->currentScene()->addLight(new PointLight({37.0f, 3.0f, 13.0f}, {0.7f, 0.6f, 0.3f}, 0.0f));
		_graphScene->currentScene()->addLight(new PointLight({37.0f, 3.0f, 20.0f}, {0.7f, 0.6f, 0.3f}, 0.0f));
		_graphScene->currentScene()->addLight(new PointLight({37.0f, 5.0f, 29.0f}, {0.7f, 0.6f, 0.3f}, 0.0f, {1.0f, 0.045f, 0.0075f}));
		_graphScene->currentScene()->addLight(new PointLight({37.0f, 6.0f, 45.0f}, {0.7f, 0.6f, 0.3f}, 0.0f));
		_graphScene->currentScene()->addLight(new PointLight({25.0f, 6.0f, 45.0f}, {0.7f, 0.6f, 0.3f}, 0.0f));
		_graphScene->currentScene()->addLight(new SpotLight ({16.0f, 9.0f, 38.0f}, {0.5f, 0.35f, 0.15f}, 0.0f, {1.0f, 0.09f, 0.032f}, {0.3f, -1.0f, 0.3f}));
		_graphScene->currentScene()->addLight(new SpotLight ({16.0f, 9.0f, 52.0f}, {0.5f, 0.35f, 0.15f}, 0.0f, {1.0f, 0.09f, 0.032f}, {0.3f, -1.0f, -0.3f}));
	}

	void GameMgr::initSkybox()
	{
		Skybox* skybox = new Skybox( "Skybox",
			_manager->getModel  ("resources/Skybox/skybox.obj"),
			_manager->getShader (PATH_VERTEX, "resources/Shaders/model3Dnolight.fs"),
			{{0.0f, 30.f, 0.0f}, {0.f, 0.f, 0.0f}, {500, 500, 500}});
		_graphScene->currentScene()->addChild(skybox);
	}

	void GameMgr::quit()
	{
		_needQuit = true;
	}

	void GameMgr::goToIngame()
	{
		_inputs->enablePlayerCommands();
		_window->showCursor(false);
		_graphScene->changeScene(1);
		_graphCanvas->changeCanvas(1);
		_gameState = EGameState::INGAME;
		_hudMgr->updateMenuState(EMenuState::NONE);
		_window->showCursor(false);
	}

	void GameMgr::newGame()
	{
		_inputs->enablePlayerCommands();
		_graphScene->changeScene(1);
		_graphCanvas->changeCanvas(1);
		_gameState = EGameState::INGAME;
		Resources::SaveManager::load("resources/Save/Init/", _graphScene->currentScene(),
									 _player, _levelMgr);
		initSkybox();
		_window->showCursor(false);
	}

	void GameMgr::loadGame()
	{
		_inputs->enablePlayerCommands();
		_graphScene->changeScene(1);
		_graphCanvas->changeCanvas(1);
		_gameState = EGameState::INGAME;
		Resources::SaveManager::load("resources/Save/Save1/", _graphScene->currentScene(),
									 _player, _levelMgr);
		initSkybox();
		_window->showCursor(false);
	}

	void GameMgr::goToMainMenu()
	{
		_inputs->disablePlayerCommands();
		_window->showCursor(true);
		_graphScene->changeScene(0);
		_graphCanvas->changeCanvas(0);
		_gameState = EGameState::MENUS;
		_hudMgr->updateMenuState(EMenuState::MAIN);
		_hudMgr->loadGameButton()->disableUpdate(!Resources::SaveManager::saveExists("resources/Save/Save1/"));
		_window->showCursor(true);

	}

	void GameMgr::goToEscMenu()
	{
		_inputs->disablePlayerCommands();
		_window->showCursor(true);
		_graphCanvas->changeCanvas(2);
		_gameState = EGameState::MENUS;
		_hudMgr->updateMenuState(EMenuState::ESCAPE);
		_window->showCursor(true);
	}

	void GameMgr::goToOptionsMenu()
	{
		_graphCanvas->changeCanvas(3);
		_hudMgr->updateMenuState(EMenuState::OPTIONS);
	}

	void GameMgr::goToLastMenu()
	{
		switch (_hudMgr->menuState())
		{
		case EMenuState::ESCAPE:
			goToIngame(); break;
		
		case EMenuState::OPTIONS:
			if (_hudMgr->lastMenuState() == EMenuState::MAIN)
				goToMainMenu();
			else if (_hudMgr->lastMenuState() == EMenuState::ESCAPE)
				goToEscMenu();
			break;
		
		case EMenuState::KEYBINDS:
			break;

		case EMenuState::INVENTORY:
			break;

		default:
			break;
		}
	}

	void GameMgr::update(double frameTime)
	{
		_inputs->processEvents(_window);

		if (_gameState == EGameState::MENUS)
			updateMenus(frameTime);
		else if (_gameState == EGameState::INGAME)
			updateInGame(frameTime);
	}

	void GameMgr::updateMenus(double frameTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_graphCanvas->update(_inputs->module());
		
		_hudMgr->update(frameTime);

		glDepthRangef(0.02f, 1.0f);
		_graphScene->draw(_camera->getViewProj(), _camera->position());

		glDepthRangef(0.f, 0.01f);
		_graphCanvas->render(_cameraUI->getViewProj(), _cameraUI->position());

		if (_inputs->module().cancel() && !_cancelBounce)
		{
			goToLastMenu();
			_cancelBounce = true;
		}

		if (!_inputs->module().cancel() && _cancelBounce)
			_cancelBounce = false;
	}

	void GameMgr::updateInGame(double frameTime)
	{
		//std::cout << "game update" << std::endl;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_graphScene->update(frameTime);
		_graphCanvas->update(_inputs->module());
		
		_hudMgr->update(frameTime);
		// Update the fixed physic update
		_physicCooldown -= frameTime;
		if (_physicCooldown < s_physicCooldownMax)
		{
			// Give the time that has passed (multiplied by the time scale)
			_graphScene->physicUpdate((s_physicCooldownMax - _physicCooldown) *_timeScale);
			_physicCooldown = s_physicCooldownMax;
		}


		float x, y;
    	_window->getMousePos(x, y);

		//Update the level manager to determine the end of the game
		_levelMgr->update(*_graphScene->currentScene());
		
		if ((_levelMgr->showWin() || _levelMgr->showLoose()))
		{
			_inputs->disableAllCommands();
			_timeScale = 0.0001;
			if (_levelMgr->showMessage(frameTime))
			{
				goToMainMenu();
				_inputs->enableAllCommands();
				_timeScale = 1;
			}
		}
		else
			_camera->update(x, y, _window->getWindow());

		glDepthRangef(0.02f, 1.0f);
		_graphScene->draw(_camera->getViewProj(), _camera->position());

		glDepthRangef(0.f, 0.01f);
		_graphCanvas->render(_cameraUI->getViewProj(), _cameraUI->position());

		if (_inputs->module().cancel() && !_cancelBounce)
		{
			goToEscMenu();
			_cancelBounce = true;
		}

		if (!_inputs->module().cancel() && _cancelBounce)
			_cancelBounce = false;

	}

	void GameMgr::resize(uint width, uint height)
	{
		glViewport(0, 0, width, height);
		_inputs->resize(width, height);

		_camera->updateSize(width, height);
		_cameraUI->updateSize(width, height);

		Resources::Canvas::windowTransform()->setWidth(width);
		Resources::Canvas::windowTransform()->setHeight(height);
		_graphCanvas->resizeCanvas();
	}
}
