
set(PLATFORM_SOURCES
	${GAME_SOURCES}
	"${SRC}/Platform/SDL2/Game.cpp"
	"${SRC}/Platform/SDL2/RenderWindow.cpp"
	"${SRC}/Platform/SDL2/entity.cpp"
	"${SRC}/Platform/SDL2/Keyboard/Keyboard.cpp"
	"${SRC}/Platform/SDL2/Menus/Menus.cpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/MainMenu.cpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/Play/Play.cpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/Settings/Settings.cpp"
	"${SRC}/Platform/SDL2/gameManager/gameManager.cpp"
)
option(USE_ORIGINAL_MENU "Use original game's menu (\"Test Mode\")" OFF)
	list(APPEND PLATFORM_SOURCES "${SRC}/Platform/SDL2/Game.cpp")

set(PLATFORM_HEADERS 
	"${SRC}/Platform/SDL2/headers/Game.hpp"
	"${SRC}/Platform/SDL2/headers/RenderWindow.hpp"
	"${SRC}/Platform/SDL2/headers/entity.hpp"
	"${SRC}/Platform/SDL2/Keyboard/Keyboard.hpp"
	"${SRC}/Platform/SDL2/Menus/Menus.hpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/Play/Play.cpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/Settings/Settings.hpp"
	"${SRC}/Platform/SDL2/gameManager/gameManager.hpp"

	)

set(REGISTRY_HEADERS 
	"${SRC}/ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"
	"${SRC}/ShakTris/Plugins/PluginManager.hpp"
	)


set(REGISTRY_SOURCES 
	"${SRC}/ShakTris/Plugins/PluginHeaders/PluginRegistry.cpp"
	"${SRC}/ShakTris/Plugins/PluginManager.cpp"
	)


set(ICON_DIR "${CMAKE_SOURCE_DIR}/Asset/Icon")

include("${SRC}/Platform/SDL2/ExecutableTypeSimple.cmake")

#AddBinary(
#	Registry
#	RUNTIME
#	SOURCES ${REGISTRY_SOURCES}
#	INCLUDE_DIRS ${REGISTRY_HEADERS}
#	LIBRARIES
#		libshaktris
#		${PLATFORM_LIBRARIES}
#)

add_library(Registry SHARED STATIC ${REGISTRY_SOURCES})
target_include_directories(Registry PUBLIC include ${REGISTRY_HEADERS})
target_link_libraries(Registry PRIVATE SDL2::SDL2 SDL2::SDL2_image)
set_target_properties( 
		Registry
    PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb"
)

