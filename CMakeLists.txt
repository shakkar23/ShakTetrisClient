cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE on)


project("ShakTetrisClient" VERSION 0.7.9)

if(NOT PLATFORM_NAME)
	set(PLATFORM_NAME "SDL2")
endif()

if(NOT EXECUTABLE_TYPE)
	set(EXECUTABLE_TYPE Simple)
endif()

set(SRC "${CMAKE_SOURCE_DIR}")

set(GAME_SOURCES
	"${SRC}/ShakTetrisClient.cpp"
	"${SRC}/ShakTris/Input/Input.cpp"
)
set(GAME_HEADERS
	"${SRC}/ShakTris//Input/Input.hpp"

)

add_subdirectory("${SRC}/Platform/${PLATFORM_NAME}")