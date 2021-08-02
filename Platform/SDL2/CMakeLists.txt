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
	"${SRC}/Platform/SDL2/headers/RenderWindow.hpp"
	"${SRC}/Platform/SDL2/headers/entity.hpp"
	"${SRC}/Platform/SDL2/Keyboard/Keyboard.hpp"
	"${SRC}/Platform/SDL2/Menus/Menus.hpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/MainMenu.hpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/Play/Play.cpp"
	"${SRC}/Platform/SDL2/Menus/MainMenu/Settings/Settings.hpp"
	"${SRC}/Platform/SDL2/gameManager/gameManager.hpp"
	)

set(ICON_DIR "${CMAKE_SOURCE_DIR}/Asset/Icon")

include("${SRC}/Platform/SDL2/ExecutableTypeSimple.cmake")