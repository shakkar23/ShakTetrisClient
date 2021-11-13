project("exmaple")




set(PLUGIN_SOURCES
"${CMAKE_CURRENT_LIST_DIR}/example.cpp"
"${SRC}/Platform/SDL2/entity.cpp"
)
set(PLUGIN_INCLUDE_DIRS
"${CMAKE_CURRENT_LIST_DIR}"
"${SRC}/Platform/SDL2/headers/Game.hpp"
"${SRC}/Platform/SDL2/headers/entity.hpp"
"${SRC}/Platform/SDL2/headers/RenderWindow.hpp"
"${SRC}/ShakTris/Plugins/PluginHeaders/PluginRegistry.hpp"
"${SRC}/Platform/SDL2/RenderWindow.cpp"
"${SRC}/Platform/SDL2/entity.cpp"
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

target_include_directories(${plugin} PRIVATE ${PLUGIN_INCLUDE_DIRS} 
	${SDL2_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
	${SRC}
	${SDL2_INCLUDE_DIRS}
	${PLATFORM_HEADERS}
	)
target_link_libraries(${plugin} PUBLIC SDL2::SDL2 SDL2::SDL2_image)
target_link_libraries(${plugin} PRIVATE Registry)
set_target_properties( 
		${plugin}
    PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb"
)