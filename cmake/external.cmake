set(CPM_DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")

if (NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
        ${CPM_DOWNLOAD_LOCATION}
        EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17ejffd7b06ad9e26a6add69de8f3ae4791
    )
endif()

include(${CPM_DOWNLOAD_LOCATION})

add_library(external INTERFACE)
add_library(external::external ALIAS external)

set(SDLIMAGE_VENDORED OFF CACHE BOOL "Disable vendored dependencies in SDL_image")

CPMAddPackage("gh:libsdl-org/SDL#release-3.2.16")
CPMAddPackage("gh:libsdl-org/SDL_image#release-3.2.0")
CPMAddPackage("gh:g-truc/glm#1.0.1")
CPMAddPackage("gh:fmtlib/fmt#11.2.0")

list(APPEND EJFF_EXTERNAL_LIBRARIES
    SDL3::SDL3
    SDL3_image::SDL3_image
    glm::glm
    fmt::fmt
)

target_link_libraries(external INTERFACE ${EJFF_EXTERNAL_LIBRARIES})