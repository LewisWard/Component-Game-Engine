// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#pragma once
#include "Configurations.h"
#include "ObjObject.h"
#include "Window.h"
#define MULTIKEYMASK 0xFF
#define BSPACE 8
#define ENTER 13
#define ESC 27
#define SPACE 32

namespace GE
{
	namespace Input
	{
		enum mouseKeys
		{
			kLeftButton, kMiddleButton, kRightButton,
			kButtonDown, kButtonUp,
			kNoButton
		};

		struct Mouse
		{
			int x;
			int y;
		};

		struct Key
		{
			std::string inputName;
			int value = 0;
			short keyBinding;
			bool multiKey = false;
		};

		class InputManager
		{
		public:
			InputManager();

			~InputManager();

			void update();

			short getKeyDown(std::string inputName);

			short getKeyHeld(std::string inputName);

			bool getMouseDown(mouseKeys button);

			bool getMouseHeld(mouseKeys button);

			inline Mouse getMousePosition() { return m_mouse; }

		private:

			bool readConfigFile();

			void makeMultiKey(Key& k, short higher, short lower);

			void useMultiKey(Key key, short& higher, short& lower);

			void makeSingleKey(Key& k, short value);

			std::vector<Key> m_srdKeys;
			std::vector<Key> m_keysDown;
			std::vector<Key> m_keysHeld;
			int m_mouseKeys[3];
			int m_mouseKeysDown[3];
			int m_mouseKeysHeld[3];
			Mouse m_mouse;
		};

		class MouseConverter
		{
		public:

			MouseConverter(glm::mat4 projection, glm::mat4 view, glm::vec2 screen);

			~MouseConverter();

			void update(GE::Input::Mouse mouse);

			inline glm::vec3 getRay() { return m_currentRay; }

		private:

			glm::vec3 calculateMouseRay(float mouseX, float mouseY);

			glm::vec3 toWorldCoords(glm::vec4 eyeCoords);

			glm::vec4 toEyeCoords(glm::vec4 clipCoords);

			glm::vec2 getNormalDeviceCoords(float mouseX, float mouseY);

			glm::vec2 m_screenSize;
			glm::vec3 m_currentRay;
			glm::mat4 m_projectionMatrix;
			glm::mat4 m_viewMatrix;
		};
	};
};
