// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016

#include "Configurations.h"

Configurations::Configurations()
{

}

Configurations::~Configurations()
{

}

bool Configurations::readINIFile(const char* file)
{
	std::ifstream ifs(file);

	// if the file opened read in the data
	if (ifs.is_open())
	{
		char* buffer = new char[128];

		ifs.getline(buffer, 128, '\n');
		data.windowTitle = buffer;

		ifs.getline(buffer, 128, '\n');
		data.textureCount = std::atoi(buffer);

		ifs.getline(buffer, 128, '\n');
		data.modelCount = std::atoi(buffer);

		ifs.getline(buffer, 128, '\n');
		data.shaderCount = std::atoi(buffer);

		// ADD: GameObject count

		for (size_t i = 0; i < data.textureCount; i++)
		{
			ifs.getline(buffer, 128, '\n');
			data.texturePaths.push_back(buffer);
		}

		for (size_t i = 0; i < data.modelCount; i++)
		{
			ifs.getline(buffer, 128, '\n');
			data.modelPaths.push_back(buffer);
		}

		for (size_t i = 0; i < data.shaderCount; i++)
		{
			ifs.getline(buffer, 128, '\n');
			data.shaderPaths.push_back(buffer);
		}

		/*
		// TODO: Loop over GameObject Count

		// ADD: GameObject[i] positionX, positionY, positionZ, scale

		// ADD: GameObject[i] textureID, ModelID, TextureID

		// ADD: GameObject[i] if true use a collider, if true use Sphere Collider

		*/

		delete[] buffer;
	}
	else
	{
		std::cout << "Failed to read " << file << " .ini file\n";
		return 1;
	}

	ifs.close();

	return 0;
}
