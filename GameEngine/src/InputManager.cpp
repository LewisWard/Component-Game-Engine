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
			m_mouseKeys[0] = mouseKeys::kLeftButton;
			m_mouseKeys[1] = mouseKeys::kMiddleButton;
			m_mouseKeys[2] = mouseKeys::kRightButton;

			// no button pressed
			for (int i = 0; i < 3; i++)
			{
				m_mouseKeysDown[i] = mouseKeys::kNoButton;
				m_mouseKeysHeld[i] = mouseKeys::kNoButton;
			}

			m_mouse.x = 0;
			m_mouse.y = 0;

			// edit vaules
			if (!readConfigFile())
			{
				m_srdKeys.resize(10);

				// standard keys always init
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
			}
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
			mousePosition(m_mouse.x, m_mouse.y);

			// cycle over the mouse buttons
			for (int i = 0; i < 3; i++)
			{
				// is mouse button pressed
				if (isMouseKeyPressed((short)m_mouseKeys[i]))
				{
					// if it's been pressed for the first time
					if (m_mouseKeysDown[i] == mouseKeys::kNoButton)
					{
						m_mouseKeysDown[i] = m_mouseKeys[i];
					}
					else
					{
						// otherwise it's been held down
						m_mouseKeysHeld[i] = m_mouseKeys[i];
					}
				}
				else
				{
					// not being pressed
					m_mouseKeysDown[i] = mouseKeys::kNoButton;
					m_mouseKeysHeld[i] = mouseKeys::kNoButton;
				}
			}

			// cycle over the keys
			for (int i = 0; i < m_srdKeys.size(); i++)
			{
				bool justSet = false;
				bool justMoved = false;
				// IF SINGLE STANDARD KEY PRESSED ADD TO PRESSED DOWN
				if (isKeyPressed(m_srdKeys[i].keyBinding))
				{
					// make sure it isn't add if it is already in the heldDown vector
					if (m_srdKeys[i].value == 0)
					{
						m_srdKeys[i].value = 1;
						m_keysDown.push_back(m_srdKeys[i]);
						justSet = true;
					}
				}


				// IF SINGLE STANDARD KEY PRESSED AND IS ALREADY PRESSED DOWN ADD TO HELD AND REMOVE TO DOWN
				if (m_keysDown.size() && !justSet)
				{
					// make sure the same key isn't added more then once
					bool heldAlready = false;
					for (int ii = 0; ii < m_keysHeld.size(); ii++)
					{
						if (m_keysHeld[ii].value == m_srdKeys[i].value)
							heldAlready = true;
					}

					// add it and remove from the keyDown
					if (false == heldAlready)
					{
						m_keysHeld.push_back(m_srdKeys[i]);
						justMoved = true;

						for (int h = 0; h < m_keysHeld.size(); h++)
							for (int d = 0; d < m_keysDown.size(); d++)
								if (m_keysHeld[h].keyBinding == m_keysDown[d].keyBinding)
								{
									m_keysDown.erase(m_keysDown.begin() + d);
								}
					}
				}

				// HANDLE MULTIKEYS
				if (m_srdKeys[i].multiKey) 
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
					if (!justSet)
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
					}

					if (!justMoved)
					{
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

		bool InputManager::getMouseDown(mouseKeys button)
		{
			for (size_t i = 0; i < 3; ++i)
			{
				if (m_mouseKeysDown[i] == button)
				{
					return true;
				}
			}

			return false;
		}

		bool InputManager::getMouseHeld(mouseKeys button)
		{
			for (size_t i = 0; i <3; ++i)
			{
				if (m_mouseKeysHeld[i] == button)
				{
					return true;
				}
			}

			return false;
		}

		bool InputManager::readConfigFile()
		{
			// open and read the file
			std::ifstream ifs(ENGINEASSETS"controls.ini");
			if (ifs.is_open())
			{
				std::vector<std::string> lines;
				char* buffer = new char[256];

				// read all of the lines
				while (!ifs.eof())
				{
					ifs.getline(buffer, 256, '\n');
					lines.push_back(buffer);
				}

				delete[] buffer;
				m_srdKeys.resize(lines.size());

				for (size_t i = 0; i < lines.size(); ++i)
				{
					// process the read data
					std::string inputName, keyA, keyB;

					size_t position = lines[i].find("=");
					size_t multiKey = lines[i].find(":");
					if (multiKey == std::string::npos)
					{
						inputName = lines[i].substr(0, position);
						keyA = lines[i].substr(position + 1, 3);
					}
					else
					{
						inputName = lines[i].substr(0, position);
						keyA = lines[i].substr(position + 1, 1);
						keyB = lines[i].substr(multiKey + 1, 3); ///< need to allow for double digit numbers like 32 (Space Bar)
					}

					m_srdKeys[i].inputName = inputName;

					if (keyA.size() == 1)
						m_srdKeys[i].keyBinding = (short)keyA[0];
					else
						m_srdKeys[i].keyBinding = (short)atoi(keyA.c_str());

					// got a multi key
					if (!keyB.empty())
						if (keyA.size() == 1)
							makeMultiKey(m_srdKeys[i], (short)keyA[0], (short)keyB[0]);
						else
							makeMultiKey(m_srdKeys[i], (short)atoi(keyA.c_str()), (short)atoi(keyB.c_str()));
				}
			}
			else
			{
				std::cout << "Failed to read " << ENGINEASSETS"controls" << " .ini file\n";
				return 0;
			}

			ifs.close();

			return 1;
		}

	};
};
