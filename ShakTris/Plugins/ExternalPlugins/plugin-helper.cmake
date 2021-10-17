
foreach(plugin IN LISTS PLUGINS)
	add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/${plugin}")
set_target_properties( ${plugin}
    PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugins"
		PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/pdb"
)
endforeach()
