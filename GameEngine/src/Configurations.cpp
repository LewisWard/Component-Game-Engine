/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
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

		ifs.getline(buffer, 128, '\n');
		data.gameObjectCount = std::atoi(buffer);

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

		data.gameObjects.resize(data.gameObjectCount);

		for (size_t i = 0; i < data.gameObjectCount; i++)
		{
			glm::vec3 position;
			float scale;

			// get GameObject[i] positionX, positionY, positionZ, scale
			ifs.getline(buffer, 128, ' ');
			position.x = std::atof(buffer);

			ifs.getline(buffer, 128, ' ');
			position.y = std::atof(buffer);

			ifs.getline(buffer, 128, ' ');
			position.z = std::atof(buffer);

			ifs.getline(buffer, 128, '\n');
			scale = std::atof(buffer);

			data.gameObjects[i].position = position;
			data.gameObjects[i].scale = scale;

			// get GameObject[i] textureID, ModelID, TextureID
			ifs.getline(buffer, 128, ' ');
			data.gameObjects[i].textureID = std::atoi(buffer);

			ifs.getline(buffer, 128, ' ');
			data.gameObjects[i].modelID = std::atoi(buffer);

			ifs.getline(buffer, 128, ' ');
			data.gameObjects[i].vertexShaderID = std::atoi(buffer);

			ifs.getline(buffer, 128, '\n');
			data.gameObjects[i].fragmentShaderID = std::atoi(buffer);

			// get GameObject[i] if true use a collider, if true use Sphere Collider
			ifs.getline(buffer, 128, ' ');
			data.gameObjects[i].hasCollider = std::atoi(buffer);

			ifs.getline(buffer, 128, '\n');
			data.gameObjects[i].sphereCollider = std::atoi(buffer);
		}

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
