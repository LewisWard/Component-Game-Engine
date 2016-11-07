// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#include "InputManager.h"

namespace GE
{
	namespace Input
	{
		InputManager::InputManager()
		{
			m_srdKeys[0].inputName = "movementVert";
			m_srdKeys[0].keyBinding = (int)'w';
			m_srdKeys[1].inputName = "movementHoriz";
			m_srdKeys[1].keyBinding = (int)'a';
			m_srdKeys[2].inputName = "mouseX";
			m_srdKeys[2].keyBinding = 0;
			m_srdKeys[3].inputName = "mouseY";
			m_srdKeys[3].keyBinding = 0;
			m_srdKeys[4].inputName = "fire1";
			m_srdKeys[4].keyBinding = 0;
			m_srdKeys[5].inputName = "fire2";
			m_srdKeys[5].keyBinding = 0;
			m_srdKeys[6].inputName = "fire3";
			m_srdKeys[6].keyBinding = 0;
			m_srdKeys[7].inputName = "jump";
			m_srdKeys[7].keyBinding = SPACE;
			m_srdKeys[8].inputName = "action";
			m_srdKeys[8].keyBinding = (int)'e';
			m_srdKeys[9].inputName = "enter";
			m_srdKeys[9].keyBinding = ENTER;
			m_srdKeys[10].inputName = "quit";
			m_srdKeys[10].keyBinding = ESC;

			makeMultiKey(m_srdKeys[0], (short)'w', (short)'s');
			//makeMultiKey(m_srdKeys[1], (short)'a', (short)'d');
		}

		InputManager::~InputManager()
		{
		}

		void InputManager::makeMultiKey(Key& k, short higher, short lower)
		{
			k.keyBinding = lower & MULTIKEYMASK;
			k.keyBinding += higher << 8;
			k.multiKey = true;
		}

		void InputManager::useMultiKey(Key key, short& higher, short& lower)
		{
			higher = (key.keyBinding >> 8);
			lower = (key.keyBinding & MULTIKEYMASK);
		}

		void InputManager::makeSingleKey(Key& k, short value)
		{
			k.keyBinding = value;
			k.multiKey = false;
		}

		void InputManager::update()
		{
			// get size of the array
			int keys = sizeof(m_srdKeys) / sizeof(m_srdKeys[0]);


			// cycle over them
			for (int i = 0; i < keys; i++)
			{
				// IF SINGLE STANDARD KEY PRESSED
				if (isKeyPressed(m_srdKeys[i].keyBinding))
				{
					// if it is empty we don't need to cycle over the vector
					if (m_srdKeys[i].value == 0)
					{
						m_srdKeys[i].value = 1;
						m_keysDown.push_back(m_srdKeys[i]);
					}
					else
					{
						// make sure we don't have it more then once
						if (!getKeyHeld(m_srdKeys[i].inputName))
						{
							// already pressed down to now is held down
							m_keysHeld.push_back(m_srdKeys[i]);
						}
					}
				}
				// HANDLE MULTIKEYS
				else if (m_srdKeys[i].multiKey) 
				{
					short higherKey, lowerKey;
					useMultiKey(m_srdKeys[i], higherKey, lowerKey);

					if (isKeyPressed(higherKey) || isKeyPressed(lowerKey))
					{
						// if it is empty we don't need to cycle over the vector
						if (m_srdKeys[i].value == 0)
						{
							m_srdKeys[i].value = 1;
							m_keysDown.push_back(m_srdKeys[i]);
						}
						else
						{
							// make sure we don't have it more then once
							if (!getKeyHeld(m_srdKeys[i].inputName))
							{
								// already pressed down to now is held down
								m_keysHeld.push_back(m_srdKeys[i]);
							}
						}
					}
					else
					{
						// match the key that has been released to the correct vector index, then erase it
						for (size_t ii = 0; ii < m_keysDown.size(); ++ii)
						{
							if (m_srdKeys[i].inputName == m_keysDown[ii].inputName)
							{
								m_srdKeys[i].value = 0;
								m_keysDown.erase(m_keysDown.begin() + ii);
								ii--;
							}
						}

						for (size_t ii = 0; ii < m_keysHeld.size(); ++ii)
						{
							if (m_srdKeys[i].inputName == m_keysHeld[ii].inputName)
							{
								m_srdKeys[i].value = 0;
								m_keysHeld.erase(m_keysHeld.begin() + ii);
								ii--;
							}
						}
					}
				}
				// DELETE SINGLE KEYS NOT PRESSED
				else
				{
					// match the key that has been released to the correct vector index, then erase it
					for (size_t ii = 0; ii < m_keysDown.size(); ++ii)
					{
						if (m_srdKeys[i].inputName == m_keysDown[ii].inputName)
						{
							m_srdKeys[i].value = 0;
							m_keysDown.erase(m_keysDown.begin() + ii);
							ii--;
						}
					}

					for (size_t ii = 0; ii < m_keysHeld.size(); ++ii)
					{
						if (m_srdKeys[i].inputName == m_keysHeld[ii].inputName)
						{
							m_srdKeys[i].value = 0;
							m_keysHeld.erase(m_keysHeld.begin() + ii);
							ii--;
						}
					}
				}
			}
		}

		bool InputManager::getKeyDown(std::string inputName)
		{
			for (size_t i = 0; i < m_keysDown.size(); ++i)
			{
				if (m_keysDown[i].inputName == inputName)
				{
					return true;
				}
			}

			return false;
		}

		bool InputManager::getKeyHeld(std::string inputName)
		{
			for (size_t i = 0; i < m_keysHeld.size(); ++i)
			{
				if (m_keysHeld[i].inputName == inputName)
				{
					return true;
				}
			}

			return false;
		}

	};
};
