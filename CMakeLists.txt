cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(FetchContent)

project(RayTracer VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_C_STANDARD 11)
SET(CMAKE_C_STANDARD_REQUIRED ON)
SET(CMAKE_C_EXTENSIONS OFF)

#############################################################################
# Import GoogleTest
#############################################################################
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
	message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
	${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	EXCLUDE_FROM_ALL)
#############################################################################
#############################################################################


#############################################################################
# Import Microsoft GSL Implementation
#############################################################################
FetchContent_Declare(GSL
	GIT_REPOSITORY "https://github.com/microsoft/GSL"
	GIT_TAG "v3.1.0"
	)

FetchContent_MakeAvailable(GSL)

add_executable(RayTracer src/main.cpp)

if(MSVC)
	target_compile_options(RayTracer PRIVATE /WX /W4 /std:c++20)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "clang")
	if(NOT WIN32)
		target_compile_options(RayTracer PRIVATE
			-std=c++20
			-Wall
			-Wextra
			-Wpedantic
			-Weverything
			-Werror
			-Wno-c++98-compat
			-Wno-c++98-compat-pedantic
			-Wno-c++98-c++11-c++14-compat-pedantic
			-Wno-c++20-compat
			)
	else()
		target_compile_options(RayTracer PRIVATE
			-std=c++20
			-Wall
			-Wextra
			-Wpedantic
			-Weverything
			-Werror
			-Wno-c++98-compat
			-Wno-c++98-compat-pedantic
			-Wno-c++98-c++11-c++14-compat-pedantic
			-Wno-c++20-compat
			)
	endif()
else()
	target_compile_options(RayTracer PRIVATE
		-std=c++20
		-Wall
		-Wextra
		-Wpedantic
		-Werror
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-c++98-c++11-c++14-compat-pedantic
		-Wno-c++20-compat
		)
endif()

target_include_directories(RayTracer BEFORE INTERFACE
	"${CMAKE_SOURCE_DIR}/src/base"
	"${CMAKE_SOURCE_DIR}/src/math"
	"${CMAKE_SOURCE_DIR}/src/graphics"
	"${CMAKE_SOURCE_DIR}/src/graphics/utils"
	"${CMAKE_SOURCE_DIR}/src/utils"
	)

###### We add headers to sources sets because it helps with `#include` lookup for some tooling #####

set(BASE
	"${CMAKE_SOURCE_DIR}/src/base/StandardIncludes.h"
	)

set(MATH
	"${CMAKE_SOURCE_DIR}/src/math/General.h"
	"${CMAKE_SOURCE_DIR}/src/math/Exponentials.h"
	"${CMAKE_SOURCE_DIR}/src/math/TrigFuncs.h"
	"${CMAKE_SOURCE_DIR}/src/math/Random.h"
	"${CMAKE_SOURCE_DIR}/src/math/Vec2.h"
	"${CMAKE_SOURCE_DIR}/src/math/Vec3.h"
	)

set(UTILS
	"${CMAKE_SOURCE_DIR}/src/utils/Concepts.h"
	"${CMAKE_SOURCE_DIR}/src/utils/RingBuffer.h"
	"${CMAKE_SOURCE_DIR}/src/utils/TypeTraits.h"
	)

set(GRAPHICS
	"${CMAKE_SOURCE_DIR}/src/graphics/Camera.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/Color.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/Geometry.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/GeometryList.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/materials/Lambertian.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/materials/Material.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/materials/Metal.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/Ray.h"
	"${CMAKE_SOURCE_DIR}/src/graphics/Sphere.h"
	)

target_sources(RayTracer PUBLIC
	${BASE}
	${MATH}
	${UTILS}
	${GRAPHICS}
	)

target_link_libraries(RayTracer PRIVATE
	GSL)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "clang" OR APPLE)
	set_target_properties(RayTracer PROPERTIES CXX_CLANG_TIDY clang-tidy)
endif()


add_executable(RayTracerTest "${CMAKE_SOURCE_DIR}/src/test/RayTracerTest.cpp")

if(MSVC)
	target_compile_options(RayTracerTest PRIVATE /WX /W4 /std:c++20)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "clang")
	if(NOT WIN32)
		target_compile_options(RayTracerTest PRIVATE
			-std=c++20
			-Wall
			-Wextra
			-Wpedantic
			-Weverything
			-Werror
			-Wno-c++98-compat
			-Wno-c++98-compat-pedantic
			-Wno-c++98-c++11-c++14-compat-pedantic
			-Wno-c++20-compat
			-Wno-global-constructors
			)
	else()
		target_compile_options(RayTracerTest PRIVATE
			-std=c++20
			-Wall
			-Wextra
			-Wpedantic
			-Weverything
			-Werror
			-Wno-c++98-compat
			-Wno-c++98-compat-pedantic
			-Wno-c++98-c++11-c++14-compat-pedantic
			-Wno-c++20-compat
			-Wno-global-constructors
			)
	endif()
else()
	target_compile_options(RayTracerTest PRIVATE
		-std=c++20
		-Wall
		-Wextra
		-Wpedantic
		-Werror
		-Wno-c++98-compat
		-Wno-c++98-compat-pedantic
		-Wno-c++98-c++11-c++14-compat-pedantic
		-Wno-c++20-compat
		-Wno-global-constructors
		)
endif()

target_include_directories(RayTracerTest BEFORE INTERFACE
	"${CMAKE_SOURCE_DIR}/src/test"
	"${CMAKE_SOURCE_DIR}/src/math/test"
	"${CMAKE_SOURCE_DIR}/src/graphics/test"
	"${CMAKE_SOURCE_DIR}/src/graphics/utils/test"
	"${CMAKE_SOURCE_DIR}/src/utils/test"
	)

if(UNIX AND NOT APPLE)
	target_link_libraries(RayTracerTest PRIVATE
		curl
		GSL
		gtest)
else()
	target_link_libraries(RayTracerTest PRIVATE
		GSL
		gtest)
endif()
