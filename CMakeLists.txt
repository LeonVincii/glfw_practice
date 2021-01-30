# ##################################################################################################
# @project  glfw_practice
# @author   Leon Vincii
#
# A GLFW practice project.
# ##################################################################################################
include(ExternalProject)
cmake_minimum_required(VERSION 3.12)

project(glfw_practice)

# ##################################################################################################
# Find Vulkan
# ##################################################################################################
set(Vulkan_DIR C:/VulkanSDK/1.2.154.1)

find_library(Vulkan_LIB
    NAMES vulkan-1.lib
    PATHS ${Vulkan_DIR}/Lib
    REQUIRED
    NO_DEFAULT_PATH
)

# ##################################################################################################
# Build GLFW
# ##################################################################################################
ExternalProject_Add(glfw
    SOURCE_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/3rd/glfw
    BINARY_DIR          ${CMAKE_CURRENT_BINARY_DIR}/3rd/glfw/bin
    CMAKE_ARGS          -DBUILD_SHARED_LIBS=ON
                        -DGLFW_BUILD_DOCS=OFF
                        -DGLFW_BUILD_TESTS=OFF
                        -DGLFW_BUILD_EXAMPLES=OFF
    INSTALL_COMMAND     cmake -E echo "Skip install step"
)

set_target_properties(glfw
    PROPERTIES
    COMPILE_DEFINITIONS _GLFW_BUILD_DLL
)

# ##################################################################################################
# Build main project
# ##################################################################################################
set(${PROJECT_NAME}_SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_compile_definitions(${PROJECT_NAME}
    PRIVATE GLFW_DLL
)

add_dependencies(${PROJECT_NAME}
    glfw
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${Vulkan_DIR}/Include
    PRIVATE 3rd/glfw/include/GLFW
    PRIVATE src
)

target_link_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/3rd/glfw/bin/src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${Vulkan_LIB}
    PRIVATE glfw3dll.lib
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/bin
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/3rd/glfw/bin/src/glfw3.dll
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/bin
    )
endif()