find_package(SDL2 REQUIRED)
find_package(SDL2-image REQUIRED)


project("exmaple")

set(PLUGIN_SOURCES
"${CMAKE_CURRENT_LIST_DIR}/example.cpp"
)
set(PLUGIN_INCLUDE_DIRS
"${CMAKE_CURRENT_LIST_DIR}"
)

set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(PLUGIN_NAME=${plugin})

set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".tetris")
 
include("${SRC}/Platform/Util/AddBinary.cmake")
AddBinary(
	${plugin}
	PLUGIN
	SOURCES      ${PLUGIN_SOURCES}
	INCLUDE_DIRS ${PLUGIN_INCLUDE_DIRS}
	LIBRARIES
		SDL2::SDL2main
		PlatformSDL2
		Registry
)