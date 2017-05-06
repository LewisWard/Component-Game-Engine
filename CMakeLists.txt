cmake_minimum_required (VERSION 3.4.3)
PROJECT(GameEngine)

# if Visual Studio
if(MSVC)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()


# add paths for include files
include_directories("${PROJECT_SOURCE_DIR}/Game/include" "${PROJECT_SOURCE_DIR}/GameEngine/include" "${PROJECT_SOURCE_DIR}/GameEngineCore/include" "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3" "${PROJECT_SOURCE_DIR}/GameEngineCore/include/freeglut/include")

# set source files
file(GLOB_RECURSE BULLET3_COLLISION 
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Collision/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Collision/*.h")
file(GLOB_RECURSE BULLET3_COMMON
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Common/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Common/*.h")
file(GLOB_RECURSE BULLET3_DYNAMICS
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Dynamics/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Dynamics/*.h")
file(GLOB_RECURSE BULLET3_GEOMETRY
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Geometry/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Geometry/*.h")
file(GLOB_RECURSE BULLET3_SERIALIZE
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Serialize/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/Bullet3Serialize/*.h")
file(GLOB_RECURSE BULLET_COLLISION
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletCollision/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletCollision/*.h")
file(GLOB_RECURSE BULLET_DYNAMICS
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletDynamics/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletDynamics/*.h")
file(GLOB_RECURSE BULLET_INVERSEDYNAMICS
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletInverseDynamics/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletInverseDynamics/*.h")
file(GLOB_RECURSE BULLET_SOFTBODY
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletSoftBody/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/BulletSoftBody/*.h")
file(GLOB_RECURSE BULLET_CLEW
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/clew/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/clew/*.h")
file(GLOB_RECURSE BULLET_MATH
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/LinearMath/*.cpp"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/LinearMath/*.h")
file(GLOB BULLET3 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/bullet3/*.h")
file(GLOB FREEGLUT ${PROJECT_SOURCE_DIR}/GameEngineCore/include/freeglut/src/*.c)
file(GLOB SOIL_FILES
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/soil/*.c"
 "${PROJECT_SOURCE_DIR}/GameEngineCore/include/soil/*.h")

# copy asset directory to build directory
file(COPY EngineAssets DESTINATION ${CMAKE_BINARY_DIR})

add_library(GameEngineCore STATIC ${PROJECT_SOURCE_DIR}/GameEngineCore/src/Window.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/src/ObjObject.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/src/ObjParser.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/src/Texture.cpp
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/src/Timer.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/src/VertexBuffer.cpp
			     
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/include/AABB.h
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/include/glew.h
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/include/glFunctions.h
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/include/OBB.h
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/include/ObjObject.h
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/include/ObjParser.h
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/include/Texture.h
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/include/Timer.h
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/include/VertexBuffer.h
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/include/wglew.h
			     ${PROJECT_SOURCE_DIR}/GameEngineCore/include/Window.h
			     ${BULLET3_COLLISION}
			     ${BULLET3_COMMON}
			     ${BULLET3_DYNAMICS}
			     ${BULLET3_GEOMETRY}
			     ${BULLET3_SERIALIZE}
			     ${BULLET_COLLISION}
			     ${BULLET_DYNAMICS}
			     ${BULLET_INVERSEDYNAMICS}
			     ${BULLET_SOFTBODY}
			     ${BULLET_CLEW}
			     ${BULLET_MATH}
			     ${BULLET3}
			     ${FREEGLUT}
			     ${SOIL_FILES})
# set folders in IDE
source_group("Bullet" FILES ${BULLET_COLLISION} ${BULLET3_COMMON} ${BULLET3_DYNAMICS} ${BULLET3_GEOMETRY} ${BULLET3_SERIALIZE} ${BULLET_COLLISION} ${BULLET_DYNAMICS} ${BULLET_INVERSEDYNAMICS} ${BULLET_SOFTBODY} ${BULLET_CLEW} ${BULLET_MATH} ${BULLET3})
source_group("FreeGlut" FILES ${FREEGLUT})
source_group("Soil" FILES ${SOIL_FILES})

add_library(GameEngine STATIC ${PROJECT_SOURCE_DIR}/GameEngine/src/BoxCollider.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Camera.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/CollisionShape.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Components.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Configurations.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/DebugBTDraw.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/GameObject.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/InputManager.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Light.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Log.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/MeshRenderer.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Program.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/RigidBody.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Shaders.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/SphereCollider.cpp
			     ${PROJECT_SOURCE_DIR}/GameEngine/src/Transform.cpp
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/src/AABB.cpp
                             ${PROJECT_SOURCE_DIR}/GameEngineCore/src/glew.c
			     
                             ${PROJECT_SOURCE_DIR}/GameEngine/include/BoxCollider.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Camera.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/CollisionShape.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Components.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Configurations.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/DebugBTDraw.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/GameObject.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/InputManager.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Light.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Log.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/MeshRenderer.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Program.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/RigidBody.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Shaders.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/SphereCollider.h
			     ${PROJECT_SOURCE_DIR}/GameEngine/include/Transform.h)
target_link_libraries(GameEngine GameEngineCore)

# add the executable
add_executable(Game ${PROJECT_SOURCE_DIR}/Game/src/Main.cpp
                             ${PROJECT_SOURCE_DIR}/Game/src/Application.cpp
			    
                             ${PROJECT_SOURCE_DIR}/Game/include/Application.h
                             ${PROJECT_SOURCE_DIR}/Game/include/Defines.h)
target_link_libraries(Game GameEngine)