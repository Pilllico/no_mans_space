cmake_minimum_required(VERSION 3.5)

project(ecs LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

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

qt5_add_resources(SHADERS shaders.qrc)

add_executable(ecs
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
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
    geometryengine.h
    geometryengine.cpp
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
    rendersystem.cpp
    rendersystem.h
    ${SHADERS}
)

target_link_libraries(ecs Qt${QT_VERSION_MAJOR}::Widgets BulletDynamics BulletCollision LinearMath)
