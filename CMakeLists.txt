cmake_minimum_required(VERSION 3.10)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project("ShakTetrisClient" VERSION 0.7.9)

if(NOT PLATFORM_NAME)
	set(PLATFORM_NAME "SDL2")
endif()

if(NOT EXECUTABLE_TYPE)
	set(EXECUTABLE_TYPE Simple)
endif()

set(SRC "${CMAKE_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 20)

set(PLUGINS_INSTALL_LOCATION "plugins")
set(PLUGINS
	example
)

set(GAME_SOURCES
	"${SRC}/ShakTetrisClient.cpp"

	"${SRC}/ShakTris/Input/Input.cpp"
	"${SRC}/ShakTris/Plugins/PluginHeaders/Tetris.cpp"
)

set(GAME_HEADERS
	"${SRC}/ShakTris/Input/Input.hpp"
	"${SRC}/ShakTris/Plugins/PluginHeaders/Tetris.hpp"
)

add_subdirectory("${SRC}/Platform/${PLATFORM_NAME}")
 set(CMAKE_INSTALL_BINDIR ".")
include("${SRC}/ShakTris/Plugins/ExternalPlugins/plugin-helper.cmake")
