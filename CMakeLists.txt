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
	set(CMAKE_EXE_LINKER_FLAGS
		"${CMAKE_EXE_LINKER_FLAGS} -Lvendor/windows/x86_64/lib/"
	)
	set(EXTRA_LIBS gdi32)
	find_library(GDI32_LIBARY gdi32)
	if(NOT GDI32_LIBRARY)
		message(FATAL_ERROR
			"gdi32 library not found, necessary for OpenGL w/ Windows"
		)
	endif()
	set(WINDRES
		"$ENV{MINGW_PREFIX}/bin/${CMAKE_C_COMPILER_PREFIX}-windres"
	)
	find_program(WINDRES_PROGRAM WINDRES)
	if(NOT WINDRES_PROGRAM)
		message(FATAL_ERROR
			"windres not found, necessary for compiling rc files"
		)
	endif()
	add_custom_command(
		OUTPUT totd-pubinfo.o
		COMMAND ${WINDRES} -o totd-pubinfo.o src/totd-pubinfo.rc
		DEPENDS src/totd-pubinfo.rc
		COMMENT "Compiling resource file"
	)
	list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/totd-pubinfo.o)
endif()
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
target_link_libraries(towerofthedead ${M_LIBRARY})
target_link_libraries(towerofthedead ${GLFW_LIBRARY})
target_link_libraries(towerofthedead ${GLEW_LIBRARY})
target_link_libraries(towerofthedead ${OPENGL_LIBRARY})
target_include_directories(${GLEW_INCLUDE_DIR})
target_include_directories(${GLFW_INCLUDE_DIR})
target_include_directories(${CGLM_INCLUDE_DIR})
if(MINGW_W64)
	target_link_libraries(towerofthedead ${EXTRA_LIBS})
endif()
add_executable(towerofthedead ${SOURCES})
