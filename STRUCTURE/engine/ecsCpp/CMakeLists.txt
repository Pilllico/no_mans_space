cmake_minimum_required(VERSION 3.5)

project(ecs LANGUAGES CXX)

find_package(OpenGL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory (external)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
)

INCLUDE_DIRECTORIES(bullet)

file(GLOB SOURCES_LINEAR "bullet/LinearMath/*.cpp")
file(GLOB HEADERS_LINEAR "bullet/LinearMath/*.h")
file(GLOB SOURCES_LINEAR2 "bullet/LinearMath/TaskScheduler/*.cpp")
file(GLOB HEADERS_LINEAR2 "bullet/LinearMath/TaskScheduler/*.h")
add_library(LinearMath ${SOURCES_LINEAR} ${HEADERS_LINEAR} ${SOURCES_LINEAR2} ${HEADERS_LINEAR2})

file(GLOB SOURCES_COLLISION_BROADPHASE "bullet/BulletCollision/BroadphaseCollision/*.cpp")
file(GLOB HEADERS_COLLISION_BROADPHASE "bullet/BulletCollision/BroadphaseCollision/*.h")
file(GLOB SOURCES_COLLISION_DISPATCH "bullet/BulletCollision/CollisionDispatch/*.cpp")
file(GLOB HEADERS_COLLISION_DISPATCH "bullet/BulletCollision/CollisionDispatch/*.h")
file(GLOB SOURCES_COLLISION_SHAPES "bullet/BulletCollision/CollisionShapes/*.cpp")
file(GLOB HEADERS_COLLISION_SHAPES "bullet/BulletCollision/CollisionShapes/*.h")
file(GLOB SOURCES_COLLISION_GIMPACT "bullet/BulletCollision/Gimpact/*.cpp")
file(GLOB HEADERS_COLLISION_GIMPACT "bullet/BulletCollision/Gimpact/*.h")
file(GLOB SOURCES_COLLISION_NARROW "bullet/BulletCollision/NarrowPhaseCollision/*.cpp")
file(GLOB HEADERS_COLLISION_NARROW "bullet/BulletCollision/NarrowPhaseCollision/*.h")

add_library(BulletCollision
    "bullet/btBulletCollisionCommon.h"
    ${SOURCES_COLLISION_BROADPHASE} ${HEADERS_COLLISION_BROADPHASE}
    ${SOURCES_COLLISION_DISPATCH} ${HEADERS_COLLISION_DISPATCH}
    ${SOURCES_COLLISION_SHAPES} ${HEADERS_COLLISION_SHAPES}
    ${SOURCES_COLLISION_GIMPACT} ${HEADERS_COLLISION_GIMPACT}
    ${SOURCES_COLLISION_NARROW} ${HEADERS_COLLISION_NARROW}
    )
target_link_libraries(BulletCollision LinearMath)

file(GLOB SOURCES_DYNAMICS_CHARACTER "bullet/BulletDynamics/Character/*.cpp")
file(GLOB HEADERS_DYNAMICS_CHARACTER "bullet/BulletDynamics/Character/*.h")
file(GLOB SOURCES_DYNAMICS_SOLVER "bullet/BulletDynamics/ConstraintSolver/*.cpp")
file(GLOB HEADERS_DYNAMICS_SOLVER "bullet/BulletDynamics/ConstraintSolver/*.h")
file(GLOB SOURCES_DYNAMICS_DYNAMICS "bullet/BulletDynamics/Dynamics/*.cpp")
file(GLOB HEADERS_DYNAMICS_DYNAMICS "bullet/BulletDynamics/Dynamics/*.h")
file(GLOB SOURCES_DYNAMICS_VEHICLE "bullet/BulletDynamics/Vehicle/*.cpp")
file(GLOB HEADERS_DYNAMICS_VEHICLE "bullet/BulletDynamics/Vehicle/*.h")

add_library(BulletDynamics
    "bullet/btBulletDynamicsCommon.h"
    "bullet/btBulletCollisionCommon.h"
    ${SOURCES_DYNAMICS_CHARACTER} ${HEADERS_DYNAMICS_CHARACTER}
    ${SOURCES_DYNAMICS_SOLVER} ${HEADERS_DYNAMICS_SOLVER}
    ${SOURCES_DYNAMICS_DYNAMICS} ${HEADERS_DYNAMICS_DYNAMICS}
    ${SOURCES_DYNAMICS_VEHICLE} ${HEADERS_DYNAMICS_VEHICLE})

target_link_libraries(BulletDynamics BulletCollision LinearMath)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(ecs
    main.cpp
    signatures.cpp
    entity.cpp
    entity.h
    system.cpp
    system.h
    component.h
    component.cpp
    entitymanager.cpp
    entitymanager.h
    transform.cpp
    transform.h
    componentmanager.cpp
    componentmanager.h
    transformmanager.cpp
    transformmanager.h
    displaysystem.h
    displaysystem.cpp
    physicssystem.h
    physicssystem.cpp
    physics.cpp
    physics.h
    physicsmanager.h
    physicsmanager.cpp
    motionstate.h
    motionstate.cpp
    render.h
    render.cpp
    rendermanager.cpp   
    rendermanager.h
    rendersystem.cpp
    rendersystem.h

	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp
	common/tangentspace.hpp
	common/tangentspace.cpp
)

target_link_libraries(ecs BulletDynamics BulletCollision LinearMath ${ALL_LIBS})
