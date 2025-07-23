cmake_minimum_required(VERSION 3.24.0)
project(EJFF VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

include(cmake/compiler_flags.cmake)
include(cmake/external.cmake)
include(cmake/sources.cmake)

add_executable(${PROJECT_NAME} ${EJFF_SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} 
    PRIVATE "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE external::external
)