cmake_minimum_required(VERSION 3.3)
project(hero)
find_package(OpenGL)
find_package(GLEW)
find_package(SDL2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Game.cpp Game.h Error.h Timer.cpp Timer.h Sprite.cpp Sprite.h GLSLProgram.cpp GLSLProgram.h Error.cpp Vertex.h)
add_executable(hero ${SOURCE_FILES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OPENGL_LIBRARY} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} )
#include_directories(${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})

