project("exmaple")

set(PLUGIN_SOURCES
"${CMAKE_CURRENT_LIST_DIR}/example.cpp"
"${SRC}/Platform/SDL2/RenderWindow.cpp"
"${SRC}/Platform/SDL2/entity.cpp"
)
set(PLUGIN_INCLUDE_DIRS
"${CMAKE_CURRENT_LIST_DIR}"
"${SRC}/ShakTris/Plugins/PluginManager.hpp"
"${SRC}/Platform/SDL2/headers/Game.hpp"
"${SRC}/Platform/SDL2/headers/entity.hpp"
"${SRC}/Platform/SDL2/headers/RenderWindow.hpp"
"${SRC}/ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"
"${SRC}/Platform/SDL2/headers/Game.hpp"
"${SRC}/Platform/SDL2/headers/RenderWindow.hpp"
"${SRC}/Platform/SDL2/headers/entity.hpp"
"${SRC}/Platform/SDL2/Keyboard/Keyboard.hpp"
"${SRC}/Platform/SDL2/Menus/Menus.hpp"
"${SRC}/Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
"${SRC}/Platform/SDL2/Menus/MainMenu/Play/Play.hpp"
"${SRC}/Platform/SDL2/Menus/MainMenu/Settings/Settings.hpp"
"${SRC}/Platform/SDL2/gameManager/gameManager.hpp"
)

set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(PLUGIN_NAME=${plugin})

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".tetris")

 
include("${SRC}/Platform/Util/AddBinary.cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2-image REQUIRED)
add_library(${plugin} SHARED
        ${PLUGIN_SOURCES}
)

target_include_directories(${plugin} PUBLIC ${PLUGIN_INCLUDE_DIRS} 
	${SDL2_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
	${SRC}
	${SDL2_INCLUDE_DIRS}
	${PLATFORM_HEADERS}
	)
target_link_libraries(${plugin} SDL2::SDL2 SDL2::SDL2_image Registry)
#target_link_libraries(${plugin} Registry)
set_target_properties( 
		${plugin}
    PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb"
)