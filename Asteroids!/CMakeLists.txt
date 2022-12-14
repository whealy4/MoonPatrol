cmake_minimum_required(VERSION 2.8)
PROJECT(ASTEROIDS)
SET(CMAKE_BUILD_TYPE "Release")

if (!MSVC)
SET(CMAKE_CXX_FLAGS "-Wno-deprecated")
endif()

#Compile and Link GLFW
ADD_SUBDIRECTORY(glfw-3.3.7)
link_libraries(glfw)
include_directories(${glfw_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/glfw-3.3.7/deps")

add_library(glad "${CMAKE_SOURCE_DIR}/glfw-3.3.7/deps/glad/gl.h"
         		  "${CMAKE_SOURCE_DIR}/glfw-3.3.7/deps/glad_gl.c"
				     "${CMAKE_SOURCE_DIR}/glfw-3.3.7/deps/glad_vulkan.c"
				     "${CMAKE_SOURCE_DIR}/glfw-3.3.7/deps/tinycthread.c")	 
					  
link_libraries(glad)


SET(MY_SHADER_PATH ${CMAKE_SOURCE_DIR}/shaders/)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/shaders/shader.cpp.in ${CMAKE_SOURCE_DIR}/shaders/shader.cpp)	


include_directories(${CMAKE_SOURCE_DIR}/source
					${CMAKE_SOURCE_DIR}/source/common
					${CMAKE_SOURCE_DIR}/shaders)
					
add_executable(asteroids WIN32 MACOSX_BUNDLE 
	source/common.h
	source/utils/shader_process.h
	source/utils/u8names.h
	source/utils/u8names.cpp
	source/utils/loadTexture.h
	source/utils/lodepng.cpp
	source/utils/lodepng.h
	shaders/shader.cpp
	source/main.cpp
	source/Game.h
	source/Game.cpp
	source/Ship.h
	source/Ship.cpp
	source/Asteroid.h
	source/Asteroid.cpp
	source/Alien1.h
	source/Alien1.cpp
	source/Car.h
	source/Car.cpp
	source/Ground.cpp
	source/Ground.h
	source/Wheel.cpp
	source/Wheel.h
	source/WheelCheck.cpp
	source/WheelCheck.h
		source/Bullets.h
		source/Bullets.cpp
	shaders/fshader_Ship.glsl
    shaders/vshader_Ship.glsl
	shaders/fshader_Asteroid.glsl
	shaders/vshader_Asteroid.glsl
	shaders/fshader_Car.glsl
	shaders/vshader_Car.glsl
	shaders/fshader_Ground.glsl
	shaders/vshader_Ground.glsl
	shaders/fshader_Texture.glsl
	shaders/vshader_Texture.glsl
	shaders/fshader_WheelCheck.glsl
	shaders/vshader_WheelCheck.glsl
	shaders/fshader_Bullets.glsl
	shaders/vshader_Bullets.glsl
	)
	
#Windows cleanup
if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(asteroids PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

#Apple cleanup
if (APPLE)
    set_target_properties(asteroids PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "simple")
	
    set_target_properties(asteroids PROPERTIES
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL}
    					  MACOSX_BUNDLE_ICON_FILE glfw.icns)
endif()
