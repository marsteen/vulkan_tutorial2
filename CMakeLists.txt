cmake_minimum_required(VERSION 3.10)
project("vktriangle")

message("System: ${CMAKE_SYSTEM_NAME}")

SET(VULKAN_SDK_WINDOWS "/c/VulkanSDK/1.2.162.1")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")
include_directories(./source/include)

add_executable(vktriangle
    ./source/main.cpp
    ./source/CVulkanBase.cpp
)

target_link_libraries(vktriangle)

set_target_properties(vktriangle PROPERTIES OUTPUT_NAME vktriangle)
