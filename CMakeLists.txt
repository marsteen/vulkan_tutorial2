cmake_minimum_required(VERSION 3.10)
project("vktriangle")

message("System: ${CMAKE_SYSTEM_NAME}")


SET(VULKAN_SDK_WINDOWS "/c/VulkanSDK/1.2.162.1")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17 -O2")
include_directories(./source/include)
add_executable(${CMAKE_PROJECT_NAME}
    ./source/main.cpp
    ./source/CVulkanBase.cpp
    ./source/shader/simple.frag
    ./source/shader/simple.vert
)
target_link_libraries(${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME vktriangle)

#
#
#
set(PROJECT_BINARY_DIR ".")

if (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "AMD64")
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
else()
  set(GLSL_VALIDATOR "$ENV{VULKAN_SDK}/Bin32/glslangValidator.exe")
endif()

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "./source/shader/*.frag"
    "./source/shader/*.vert"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/shader/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shader/"
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )

add_dependencies(${CMAKE_PROJECT_NAME} Shaders)

#
#
#


