// Author  : Lewis Ward (i7212443)
// Program : Game Engine
// Date    : 26/10/2016
#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "Texture.h"

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
int int int	int					- GameObject[0] textureID, ModelID, vertexShaderID, fragmentShaderID (ID based on order in this file)
bool bool								- GameObject[0] if true use a collider, if true use Sphere Collider - default Box Collider
...
... GameObject[n]				- List all GameObject 
*/

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Stores the data of a GE::GameObject from a game.ini file
//----------------------------------------------------------------------------------------------------------------------
struct gameObjectData
{
	glm::vec3 position;
	float scale;
	int fragmentShaderID;
	int vertexShaderID;
	int textureID;
	int modelID;
	bool hasCollider;
	bool sphereCollider;
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Stores the data for game.ini files
//----------------------------------------------------------------------------------------------------------------------
struct gameINI
{
	std::vector<gameObjectData> gameObjects;
	std::vector<std::string> texturePaths;
	std::vector<std::string> shaderPaths;
	std::vector<std::string> modelPaths;
	std::string windowTitle;
	int gameObjectCount;
	int textureCount;
	int shaderCount;
	int modelCount;
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Loads and stores a configuration file
//----------------------------------------------------------------------------------------------------------------------
class Configurations
{
public:
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Constructor
	//----------------------------------------------------------------------------------------------------------------------
	Configurations();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~Configurations();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief  Loads and stores a configuration file (follows game.ini layout)
	/// prama		Filename
	/// \return bool true if successful
	//----------------------------------------------------------------------------------------------------------------------
	bool readINIFile(const char* file);

	gameINI data; ///< the read data
};