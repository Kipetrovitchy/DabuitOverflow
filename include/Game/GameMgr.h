#ifndef __SIMULATION_H__
#define __SIMULATION_H__

typedef unsigned int uint;

#include <string>
#include <GL/glew.h>
#include "GameObject.h"
#include "LibMaths.h"
#include "InputMgr.h"
#include "ResourcesManager.h"
#include "Scene.h"
#include "Camera3D.h"
#include "CameraUI.h"
#include "Camera.h"
#include "GraphScene.h"
#include "GraphCanvas.h"
#include "Light.h"
#include "Player.h"
#include "Text.h"
#include "Image.h"
#include "Button.h"
#include "InputModule.h"
#include "HUDManager.h"
#include "LevelManager.h"
#include "PickableItem.h"

#ifdef _WIN32
	#define PATH_VERTEX ".\\resources\\Shaders\\model3D.vs"
	#define PATH_FRAGMENT ".\\resources\\Shaders\\model3D.fs"
#elif defined(__linux__)
	#define PATH_VERTEX "./resources/Shaders/model3D.vs"
	#define PATH_FRAGMENT "./resources/Shaders/model3D.fs"
#endif

#define BASE_TIME_SCALE 	1.0f
#define PHYSIC_COOLDOWN_MAX 0.02f

namespace Game
{
	#pragma region enum
	enum class EGameState : unsigned int
	{
		NONE = 0,
		MENUS,
		INGAME
	};
	#pragma endregion
	#pragma region typedefs
	typedef Core::Maths::Vec3 					Vec3;
	typedef Resources::ResourcesManager			ResourcesManager;
	typedef Resources::Scene 					Scene;
	typedef Core::DataStructure::GraphScene		GraphScene;
	typedef Core::DataStructure::GraphCanvas	GraphCanvas;
	typedef LowRenderer::GameObject 			GameObject;
	typedef LowRenderer::Light 					Light;
	typedef LowRenderer::Camera3D				Camera3D;
	typedef LowRenderer::CameraUI				CameraUI;
	typedef Game::Player 						Player;
	typedef Inputs::InputModule					InputModule;
	typedef Game::Items::PickableItem			PickableItem;
	#pragma endregion

	class Window;
	class GameMgr
	{
	private:
		#pragma region Attributes
		EGameState			_gameState;
		Window*		 		_window;
		InputMgr*			_inputs;

		ResourcesManager* 	_manager;
		GraphScene*  		_graphScene;
		GraphCanvas*  		_graphCanvas;
		Camera3D*           _camera;
		CameraUI*           _cameraUI;
		Player*				_player;
		HUDManager*			_hudMgr;
		LevelManager*		_levelMgr;

		bool _needQuit;
		bool _cancelBounce;

		float _timeScale;
		float _physicCooldown;
		static constexpr float s_physicCooldownMax { PHYSIC_COOLDOWN_MAX };
		#pragma endregion

		#pragma region TESTS

		float dirW { 1.f };
		float minW { 0.f };
		float maxW { M_PI };
		float actualW { 1.f };

		float lasthp { 100.f};
		bool  f1Bounce { false };
		bool updatecam { false };
		#pragma endregion

	public:
		#pragma region Constructors
		GameMgr();
		~GameMgr();
		#pragma endregion

		#pragma region Accessors
			inline GraphScene*  graphScene() const {return _graphScene;};
			inline GraphScene*& graphScene() {return _graphScene;};
			inline Player*  player() const {return _player;};
			inline Player*& player() {return _player;};
		#pragma endregion

		#pragma region Function
		void	setRenderWindow(Window* window);
		void	setTimeScale(float scale);

		bool	init(uint width, uint height);
		void	update(double frameTime);
		void	updateMenus(double frameTime);
		void	updateInGame(double frameTime);
		void	resize(uint width, uint height);

		bool	initScene();
		void	initCrates(GameObject* parent);
		void	initLights();
		void	initSkybox();
		void	quit();

		void	goToIngame();
		void 	loadGame();
		void 	newGame();
		void	goToMainMenu();
		void	goToEscMenu();
		void	goToOptionsMenu();
		void	goToLastMenu();
		#pragma endregion

		inline bool needQuit() const { return _needQuit; }
		inline Window* window() const { return _window; }
	};
}


#endif
