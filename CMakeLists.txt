cmake_minimum_required(VERSION 3.14)
project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(INCLUDE_VULKAN "Active Vulkan" OFF)

if(INCLUDE_VULKAN)
	set(VULKAN_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/VulkanSDK-<versione>")
	include_directories("${VULKAN_SDK_DIR}/Include")
	link_directories("${VULKAN_SDK_DIR}/Lib")
endif()

include_directories(external/glad/include)
add_library(glad STATIC external/glad/src/glad.c)

set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "Disable Wayland backend in GLFW")
set(GLFW_BUILD_X11     ON  CACHE BOOL "Enable X11 backend in GLFW")

add_subdirectory(external/glfw)

add_subdirectory(external/glm)

include_directories(external/stb)

file(GLOB PROJECT_SOURCES src/*.cpp)

add_executable(OpenGLTemplate 
               main.cpp
               ${PROJECT_SOURCES})

if(OpenGLTemplate)
	target_include_directories(OpenGLTemplate PRIVATE
	    external/glad/include
	    ${VULKAN_SDK_DIR}/Include
	    external/glfw/include
	    external/glm
	    external/stb
	    ${CMAKE_CURRENT_SOURCE_DIR}/include
	)
else()
	target_include_directories(OpenGLTemplate PRIVATE
	    external/glad/include
	    external/glfw/include
	    external/glm
	    external/stb
	    ${CMAKE_CURRENT_SOURCE_DIR}/include
	)
endif()

target_link_libraries(OpenGLTemplate
    glad
    glfw
    glm
)
if(OpenGLTemplate)
	if(WIN32)
	    target_link_libraries(OpenGLTemplate vulkan-1)
	elseif(UNIX)
	    target_link_libraries(OpenGLTemplate vulkan ${CMAKE_DL_LIBS})
	endif()
endif()
