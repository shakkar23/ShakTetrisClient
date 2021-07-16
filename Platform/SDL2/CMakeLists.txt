set(PLATFORM_SOURCES
	${GAME_SOURCES}
	"${SRC}/Platform/SDL2/Game.cpp"
	"${SRC}/Platform/SDL2/RenderWindow.cpp"
	"${SRC}/Platform/SDL2/entity.cpp"
)
option(USE_ORIGINAL_MENU "Use original game's menu (\"Test Mode\")" OFF)
	list(APPEND PLATFORM_SOURCES "${SRC}/Platform/SDL2/Game.cpp")

set(PLATFORM_HEADERS 
	"${SRC}/Platform/SDL2/headers/RenderWindow.hpp"
	"${SRC}/Platform/SDL2/headers/entity.hpp"
	)

set(ICON_DIR "${CMAKE_SOURCE_DIR}/Asset/Icon")

include("${SRC}/Platform/SDL2/ExecutableTypeSimple.cmake")