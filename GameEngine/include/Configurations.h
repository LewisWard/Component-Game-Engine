// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include <vector>
#include <fstream>
#include <iostream>

/*
---------------------------------------------------------------------
                      game.ini structure
---------------------------------------------------------------------
string									- Window title
int											- Texture count
int											- Model (.obj) count
int											- Shader count
int											- GameObject count
string									- texture file from EngineAssets directory (i.e. textures/grid.png)
string									- model file from EngineAssets directory (i.e. models/sphere.obj)
string									- shader file from EngineAssets directory (i.e. shaders/shader.vrt)
float float float float - GameObject[0] positionX, positionY, positionZ, scale
int int int							- GameObject[0] textureID, ModelID, TextureID (ID based on order in this file)
bool bool								- GameObject[0] if true use a collider, if true use Sphere Collider - default Box Collider
...
... GameObject[n]				- List all GameObject positions
*/

struct gameINI
{
	std::vector<std::string> texturePaths;
	std::vector<std::string> shaderPaths;
	std::vector<std::string> modelPaths;
	std::string windowTitle;
	int textureCount;
	int shaderCount;
	int modelCount;
};

class Configurations
{
public:
	Configurations();

	~Configurations();

	bool readINIFile(const char* file);

	gameINI data;
};