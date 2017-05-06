/*
Copyright (c) 2016-2017 Lewis Ward: http://www.lewis-ward.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the author be held liable for any damages arising from the use of this software.
Anyone can compile the software for personal use, no permission is granted for anyone to use the software for any other use including commercial applications,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.
2. This notice may not be removed or altered from any source distribution.
*/
#include "Application.h"

std::shared_ptr<Application> g_app;

//----------------------------------------------------------------------------------------------------------------------
/// \brief  initialisation of everything
//----------------------------------------------------------------------------------------------------------------------
void init()
{
	g_app = std::make_shared<Application>();
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief  update
//----------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_app->update(dt);
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief  3D draw
//----------------------------------------------------------------------------------------------------------------------
void draw3D()
{
	g_app->draw();
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief  called after the window is closed, use to delete/free memory
//----------------------------------------------------------------------------------------------------------------------
void cleanup()
{
	std::cout << "\ncleaning up\n";
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief  main function, do not add anything to this function.
//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	return run(argc, argv);
}
