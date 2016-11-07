// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 09/10/2016
#pragma once
#include "Configurations.h"
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

			bool readConfigFile()
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

					for (size_t i = 0; i < lines.size(); ++i)
					{
						// process the read data
						std::string inputName, keyA, keyB;

						size_t position = lines[i].find("=");
						size_t multiKey = lines[i].find(":");
						if (multiKey == std::string::npos)
						{
							inputName = lines[i].substr(0, position);
							keyA = lines[i].substr(position + 1, 2);
						}
						else
						{
							inputName = lines[i].substr(0, position);
							keyA = lines[i].substr(position + 1, 1);
							keyB = lines[i].substr(multiKey + 1, 2); ///< need to allow for double digit numbers like 32 (Space Bar)
						}

						m_srdKeys[i].inputName = inputName;

						if(keyA.size() == 1)
							m_srdKeys[i].keyBinding = (short)keyA[0];
						else
							m_srdKeys[i].keyBinding = (short)atoi(keyA.c_str());

						// got a multi key
						if(!keyB.empty())
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

			void makeMultiKey(Key& k, short higher, short lower);

			void useMultiKey(Key key, short& higher, short& lower);

			void makeSingleKey(Key& k, short value);

			Key m_srdKeys[11];
			std::vector<Key> m_keysDown;
			std::vector<Key> m_keysHeld;
		};
	};
};
