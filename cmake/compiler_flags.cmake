string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)

if(BUILD_TYPE_UPPER STREQUAL "DEBUG")
    add_compile_options(-Wall -Wextra -Wpedantic -O0)
elseif(BUILD_TYPE_UPPER STREQUAL "RELEASE")
    add_compile_options(-O3)
else()
    message(WARNING "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()