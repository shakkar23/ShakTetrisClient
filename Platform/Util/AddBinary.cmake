# AddBinary(
# 	${NAME}
# 	${TYPE}
# 	SOURCES ${SOURCE0} ${SOURCE1} ...
#	INCLUDE_DIRS ${DIR0} ${DIR1} ...
# 	LIBRARIES ${LIBRARY0} ${LIBRARY1} ...
# )
#
# TYPE can be either LIBRARY or EXECUTABLE.
#
# Simple example:
# AddBinary(
# 	program
#	EXECUTABLE
# 	SOURCES "Main.c"
# )
function(AddBinary NAME TYPE)
	if((NOT ${TYPE} STREQUAL LIBRARY) AND (NOT ${TYPE} STREQUAL EXECUTABLE))
		message(FATAL_ERROR "Invalid type; must be LIBRARY or EXECUTABLE")
	endif()

	set(LIST_NAMES SOURCES INCLUDE_DIRS LIBRARIES)
	set(ARGV_START 2)
	list(LENGTH ARGV ARGV_LAST)
	math(EXPR ARGV_LAST "${ARGV_LAST} - 1")
	if(${ARGV_LAST} GREATER_EQUAL ${ARGV_START})
		foreach(LIST_NAME IN LISTS LIST_NAMES)
			list(FIND ARGV ${LIST_NAME} NAME_INDEX)
			if(${NAME_INDEX} GREATER_EQUAL ${ARGV_START})
				math(EXPR ELEMENTS_START "${NAME_INDEX} + 1")
				if(${ELEMENTS_START} GREATER ${ARGV_LAST})
					continue()
				endif()
				set(OTHER_NAMES ${LIST_NAMES})
				list(FILTER OTHER_NAMES EXCLUDE REGEX ${LIST_NAME})
				foreach(ARGI RANGE ${ELEMENTS_START} ${ARGV_LAST})
					list(GET ARGV ${ARGI} ARG)
					list(FIND OTHER_NAMES ${ARG} OTHER_FOUND)
					if(${OTHER_FOUND} GREATER -1)
						break()
					else()
						list(APPEND ${LIST_NAME} ${ARG})
					endif()
				endforeach()
			else()
				continue()
			endif()
		endforeach()
	endif()
#	foreach(LIST_NAME IN LISTS LIST_NAMES)
#		set(LIST_NAME ${${LIST_NAME}} PARENT_SCOPE)
#	endforeach()

	list(LENGTH SOURCES SOURCES_LENGTH)
	if(${SOURCES_LENGTH} EQUAL 0)
		message(FATAL_ERROR "Sources list must have one or more files")
	endif()

	if(${TYPE} STREQUAL LIBRARY)
		add_library(${NAME} ${SOURCES})
	elseif(${TYPE} STREQUAL EXECUTABLE)
		add_executable(${NAME} ${SOURCES})
	endif()
	target_include_directories(${NAME} PUBLIC ${INCLUDE_DIRS})
	target_link_libraries(${NAME} PRIVATE ${LIBRARIES})
endfunction()