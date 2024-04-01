cmake_minimum_required(VERSION 3.0)
project(towerofthedead)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Target is Windows")
endif()
if(CMAKE_HOST_SYSTEM MATCHES "Linux")
	message(STATUS "Host is Linux")
endif()
set(SOURCES
	src/main.c
	src/dragoness/dragonessEssentialVars.c
	src/dragoness/dragonessShaderCode.c
	src/dragoness/dragonessTestModels.c
	src/dragoness/dragonessFunctions.c
	src/scripts/scriptAll.c
)
include_directories(src)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	if("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
		if(CMAKE_SIZEOF_VOID_P EQUAL 8)
			set(MINGW_W64 TRUE)
		endif()
	endif()
endif()
if(MINGW_W64)
	set(DLLPATH
		"vendor/windows/${DLLARCH}/lib"
	)
	set(CMAKE_EXE_LINKER_FLAGS
		"${CMAKE_EXE_LINKER_FLAGS} -L{DLLPATH}"
	)
	set(WINDRES
		"${MINGW_PREFIX}-windres"
	)
	find_program(WINDRES_PROGRAM "${MINGW_PREFIX}-windres")
	if(NOT WINDRES_PROGRAM)
		message(FATAL_ERROR
			"windres not found, necessary for compiling rc files"
		)
	endif()
	message(STATUS "Check for windres: ${WINDRES}")
	add_custom_command(
		OUTPUT totd-pubinfo.o
		COMMAND ${WINDRES} -o totd-pubinfo.o src/totd-pubinfo.rc
		DEPENDS src/totd-pubinfo.rc
		COMMENT "Compiling resource file"
	)
	list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/totd-pubinfo.o)
endif()
if(NOT MINGW_W64)
	find_library(M_LIBRARY m)
	if(NOT M_LIBRARY)
		message(FATAL_ERROR
			"libm not found"
		)
	endif()
	find_library(GLFW_LIBRARY glfw)
	if(NOT GLFW_LIBRARY)
		message(FATAL_ERROR
			"libglfw not found"
		)
	endif()
	find_library(GLEW_LIBRARY GLEW)
	if(NOT GLEW_LIBRARY)
		message(FATAL_ERROR
			"libglew not found"
		)
	endif()
	find_library(OPENGL_LIBRARY OpenGL)
	if(NOT OPENGL_LIBRARY)
		message(FATAL_ERROR
			"libOpenGL not found"
		)
	endif()
endif()
if(MINGW_W64)
	find_library(GLFW_LIBRARY NAMES glfw.dll HINTS ${DLLPATH})
	if(NOT GLFW_LIBRARY)
		message(FATAL_ERROR
			"libglfw not found"
		)
	endif()
	find_library(GLEW_LIBRARY NAMES GLEW.dll HINTS ${DLLPATH})
	if(NOT GLEW_LIBRARY)
		message(FATAL_ERROR
			"libglew not found"
		)
	endif()
	find_library(OPENGL_LIBRARY NAMES OpenGL.dll HINTS ${DLLPATH})
	if(NOT OPENGL_LIBRARY)
		message(FATAL_ERROR
			"libOpenGL not found"
		)
	endif()
endif()
find_path(GLEW_INCLUDE_DIR NAMES GL/glew.h)
if(NOT GLEW_INCLUDE_DIR)
	message(FATAL_ERROR
		"GL/glew.h not found"
	)
endif()
find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h)
if(NOT GLFW_INCLUDE_DIR)
	message(FATAL_ERROR
		"GLFW/glfw3.h not found"
	)
endif()
find_path(CGLM_INCLUDE_DIR NAMES cglm/cglm.h)
if(NOT CGLM_INCLUDE_DIR)
	message(FATAL_ERROR
		"cglm/cglm.h not found"
	)
endif()
add_executable(towerofthedead ${SOURCES})
target_link_libraries(towerofthedead ${M_LIBRARY})
target_link_libraries(towerofthedead ${GLFW_LIBRARY})
target_link_libraries(towerofthedead ${GLEW_LIBRARY})
target_link_libraries(towerofthedead ${OPENGL_LIBRARY})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CGLM_INCLUDE_DIR})
