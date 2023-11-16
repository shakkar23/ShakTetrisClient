cmake_minimum_required(VERSION 3.16)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CC ${CMAKE_C_COMPILER})
set(CXX ${CMAKE_CXX_COMPILER})
project("ShakTetrisClient" VERSION "1.1.1")

if(NOT PLATFORM_NAME)
	set(PLATFORM_NAME "SDL2")
endif()

if(NOT EXECUTABLE_TYPE)
	set(EXECUTABLE_TYPE Simple)
endif()

set(SRC "${CMAKE_SOURCE_DIR}")

set(PLUGINS_INSTALL_LOCATION "plugins")

set(GAME_SOURCES
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

# Move the assets directory to the binary output directory
file(COPY "${CMAKE_SOURCE_DIR}/Asset" DESTINATION "${CMAKE_BINARY_DIR}/bin")