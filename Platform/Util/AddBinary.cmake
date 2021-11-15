# The Absolute Reference:
# 
# Copyright (c) 2021 Brandon McGriff
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 
# SDL 2.0:
# 
# Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>
#   
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
# 
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#   
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required. 
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
# 
# PhysicsFS:
# 
#    Copyright (c) 2001-2020 Ryan C. Gordon and others.
# 
#    This software is provided 'as-is', without any express or implied warranty.
#    In no event will the authors be held liable for any damages arising from
#    the use of this software.
# 
#    Permission is granted to anyone to use this software for any purpose,
#    including commercial applications, and to alter it and redistribute it
#    freely, subject to the following restrictions:
# 
#    1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software in a
#    product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 
#    2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 
#    3. This notice may not be removed or altered from any source distribution.
# 
#        Ryan C. Gordon <icculus@icculus.org>
# 
# Sources/Platform/Util/ini.h
# Sources/Platform/Util/ini.c:
# 
# /**
#  * Copyright (c) 2016 rxi
#  *
#  * Permission is hereby granted, free of charge, to any person obtaining a copy
#  * of this software and associated documentation files (the "Software"), to deal
#  * in the Software without restriction, including without limitation the rights
#  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  * copies of the Software, and to permit persons to whom the Software is
#  * furnished to do so, subject to the following conditions:
#  *
#  * The above copyright notice and this permission notice shall be included in
#  * all copies or substantial portions of the Software.
#  *
#  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  * SOFTWARE.
#  */
# 
# Sources/Platform/Util/GL3/khrplatform.h
# Sources/Platform/Util/GLES2/khrplatform.h:
# 
# /*
# ** Copyright (c) 2008-2018 The Khronos Group Inc.
# **
# ** Permission is hereby granted, free of charge, to any person obtaining a
# ** copy of this software and/or associated documentation files (the
# ** "Materials"), to deal in the Materials without restriction, including
# ** without limitation the rights to use, copy, modify, merge, publish,
# ** distribute, sublicense, and/or sell copies of the Materials, and to
# ** permit persons to whom the Materials are furnished to do so, subject to
# ** the following conditions:
# **
# ** The above copyright notice and this permission notice shall be included
# ** in all copies or substantial portions of the Materials.
# **
# ** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# ** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# ** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# ** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# ** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# ** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# ** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
# */
# 
# Sources/Platform/Util/linmath.h:
# 
#             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
#                     Version 2, December 2004 
# 
#  Copyright (C) 2013 Wolfgang 'datenwolf' Draxinger <code@datenwolf.net>
# 
#  Everyone is permitted to copy and distribute verbatim or modified 
#  copies of this license document, and changing it is allowed as long 
#  as the name is changed. 
# 
#             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
#    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
# 
#   0. You just DO WHAT THE FUCK YOU WANT TO.
# 
# 






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
	if((NOT ${TYPE} STREQUAL LIBRARY) AND (NOT ${TYPE} STREQUAL EXECUTABLE) AND (NOT ${TYPE} STREQUAL RUNTIME) AND (NOT ${TYPE} STREQUAL PLUGIN) AND (NOT ${TYPE} STREQUAL MODULE) AND (NOT ${TYPE} STREQUAL BRUH))
		message(FATAL_ERROR "Invalid type; must be LIBRARY or EXECUTABLE or RUNTIME or PLUGIN")
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
		add_library(${NAME} STATIC ${SOURCES})
	elseif(${TYPE} STREQUAL EXECUTABLE)
		add_executable(${NAME} ${SOURCES})
	elseif(${TYPE} STREQUAL RUNTIME)
		add_library(${NAME} SHARED ${SOURCES}) # yeah this is kinda windows specific :/ other systems use other things
	elseif(${TYPE} STREQUAL PLUGIN)
		add_library(${NAME} SHARED ${SOURCES}) # yeah this is kinda windows specific :/ other systems use other things
	elseif(${TYPE} STREQUAL BRUH)
		add_library(${NAME} SHARED ${SOURCES}) # yeah this is kinda windows specific :/ other systems use other things
	endif()
	target_include_directories(${NAME} PUBLIC ${INCLUDE_DIRS})
	target_link_libraries(${NAME} ${LIBRARIES})
endfunction()