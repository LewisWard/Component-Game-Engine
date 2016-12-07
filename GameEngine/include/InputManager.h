// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#pragma once
#include "Configurations.h"
#include "ObjObject.h"
#include "Window.h"
#define MULTIKEYMASK 0xFF ///< mask to pack/extract multi-kes
#define BSPACE 8 ///< backspace key
#define ENTER 13 ///< enter key
#define ESC 27   ///< escape key
#define SPACE 32 ///< space key

namespace GE
{
	namespace Input
	{
		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Mouse buttons and events 
		//----------------------------------------------------------------------------------------------------------------------
		enum mouseKeys
		{
			kLeftButton, kMiddleButton, kRightButton,
			kButtonDown, kButtonUp,
			kNoButton
		};

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Mouse position
		//----------------------------------------------------------------------------------------------------------------------
		struct Mouse
		{
			int x;
			int y;
		};

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Keyboard key
		//----------------------------------------------------------------------------------------------------------------------
		struct Key
		{
			std::string inputName; ///< action name, to match name stated in controls.ini
			int value = 0;				 ///< key value, if not press will be zero
			short keyBinding;			 ///< key ASCII value that maps to keyboard
			bool multiKey = false; ///< is this key a multi-key
		};

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Handles input
		//----------------------------------------------------------------------------------------------------------------------
		class InputManager
		{
		public:
			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Constructor
			//----------------------------------------------------------------------------------------------------------------------
			InputManager();

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Destructor
			//----------------------------------------------------------------------------------------------------------------------
			~InputManager();

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Update, gets latest events from mouse and keyboard (key down/up etc.)
			//----------------------------------------------------------------------------------------------------------------------
			void update();

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Get a key that has been pressed
			/// prama	std::string input name
			/// \return short 1 if key is being pressed
			//----------------------------------------------------------------------------------------------------------------------
			short getKeyDown(std::string inputName);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Get a key that is being held down
			/// prama	std::string input name
			/// \return short 1 if key is being pressed
			//----------------------------------------------------------------------------------------------------------------------
			short getKeyHeld(std::string inputName);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Get a mouse button that is being pressed down
			/// prama	GE::Input::mouseKeys button
			/// \return bool is that button being pressed down
			//----------------------------------------------------------------------------------------------------------------------
			bool getMouseDown(mouseKeys button);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Get a mouse button that is being held down
			/// prama	GE::Input::mouseKeys button
			/// \return bool is that button being pressed down
			//----------------------------------------------------------------------------------------------------------------------
			bool getMouseHeld(mouseKeys button);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Get the mouse position
			/// \return GE::Input::Mouse
			//----------------------------------------------------------------------------------------------------------------------
			inline Mouse getMousePosition() { return m_mouse; }

		private:

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Reads the controls.ini file
			/// \return bool if it was successful, if not will map default keys to input names
			//----------------------------------------------------------------------------------------------------------------------
			bool readConfigFile();

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Turns a key into a multi-key
			/// prama GE::Input::Key key
			/// prama short the ASCII value to store in higher 8 bits
			/// prama short the ASCII value to store in lower 8 bits
			//----------------------------------------------------------------------------------------------------------------------
			void makeMultiKey(Key& k, short higher, short lower);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Cannot directly use a multi-key, this will return the ASCII values in the higher and lower shorts
			/// prama GE::Input::Key key
			/// prama short the ASCII value to store in higher 8 bits
			/// prama short the ASCII value to store in lower 8 bits
			//----------------------------------------------------------------------------------------------------------------------
			void useMultiKey(Key key, short& higher, short& lower);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Turns a multi-key back into a single key
			/// prama GE::Input::Key key
			/// prama short the ASCII value
			//----------------------------------------------------------------------------------------------------------------------
			void makeSingleKey(Key& k, short value);

			std::vector<Key> m_srdKeys; ///< standard keys
			std::vector<Key> m_keysDown; ///< pressed down keys
			std::vector<Key> m_keysHeld; ///< held down keys
			int m_mouseKeys[3]; ///< mouse buttons
			int m_mouseKeysDown[3]; ///< mouse buttons pressed down
			int m_mouseKeysHeld[3];///< mouse buttons held down
			Mouse m_mouse; ///< mouse position
		};

		//----------------------------------------------------------------------------------------------------------------------
		/// \brief Fires a ray into the world from the screen, Converts a mouse position from device coords to world space
		//----------------------------------------------------------------------------------------------------------------------
		class MouseConverter
		{
		public:
			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Constructor
			/// prama glm::mat4 projection matrix
			/// prama glm::mat4 view matrix
			/// prama glm::vec2 screen size
			//----------------------------------------------------------------------------------------------------------------------
			MouseConverter(glm::mat4 projection, glm::mat4 view, glm::vec2 screen);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief Destructor
			//----------------------------------------------------------------------------------------------------------------------
			~MouseConverter();

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief updates the ray
			/// prama GE::Input::Mouse mouse
			//----------------------------------------------------------------------------------------------------------------------
			void update(GE::Input::Mouse mouse);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief get the ray
			/// prama glm::vec3 ray
			//----------------------------------------------------------------------------------------------------------------------
			inline glm::vec3 getRay() { return m_currentRay; }

		private:

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief computes the ray from screen to world space
			/// prama float mouseX
			/// prama float mouseY
			/// \return glm::vec3 ray
			//----------------------------------------------------------------------------------------------------------------------
			glm::vec3 calculateMouseRay(float mouseX, float mouseY);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief convert the ray from eye space to world space
			/// prama glm::vec4 ray in eye space
			/// \return glm::vec3 ray
			//----------------------------------------------------------------------------------------------------------------------
			glm::vec3 toWorldCoords(glm::vec4 eyeCoords);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief convert the ray from clip space to view space
			/// prama glm::vec4 ray in clip space
			/// \return glm::vec3 ray
			//----------------------------------------------------------------------------------------------------------------------
			glm::vec4 toEyeCoords(glm::vec4 clipCoords);

			//----------------------------------------------------------------------------------------------------------------------
			/// \brief convert the ray from device coords to clip space
			/// prama  float mouseX
			/// prama  float mouseY
			/// \return glm::vec3 ray
			//----------------------------------------------------------------------------------------------------------------------
			glm::vec2 getNormalDeviceCoords(float mouseX, float mouseY);

			glm::vec2 m_screenSize;
			glm::vec3 m_currentRay;
			glm::mat4 m_projectionMatrix;
			glm::mat4 m_viewMatrix;
		};
	};
};
