// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#pragma once
#include "Window.h"
#include <vector>
#define MULTIKEYMASK 0xFF
#define BSPACE 8
#define ENTER 13
#define ESC 27
#define SPACE 32

namespace GE
{
	namespace Input
	{
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

			bool getKeyDown(std::string inputName);

			bool getKeyHeld(std::string inputName);

		private:

			void makeMultiKey(Key& k, short higher, short lower);

			void useMultiKey(Key key, short& higher, short& lower);

			void makeSingleKey(Key& k, short value);

			Key m_srdKeys[11];
			std::vector<Key> m_keysDown;
			std::vector<Key> m_keysHeld;
		};
	};
};
