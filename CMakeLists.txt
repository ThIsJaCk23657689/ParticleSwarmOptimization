cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Define Variables
set(MY_PROJECT "Particle Swarm Optimization")
set(MY_EXECUTABLE "particle-swarm-optimization")

# Define Project
project(${MY_PROJECT} VERSION 0.1)

# Create Binary Target
add_executable(${MY_EXECUTABLE})

# Set C++ standard. Required C++17
# Turn off compiler extensions for cross-platform portability.
set_target_properties(${MY_EXECUTABLE}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# Build Information
message(STATUS)
message(STATUS "========== Build Information ==========")
message(STATUS "\tHost System Name:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "\tHost System Version:      ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "\tHost System Processor:    ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS)
message(STATUS "\tC++ Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:        ${CMAKE_CXX_COMPILER}")
message(STATUS)

if (MSVC)
    message(STATUS "\tMSVC Version:             ${MSVC_VERSION}")
    message(STATUS "\tMSVC Toolset:             ${MSVC_TOOLSET_VERSION}")
endif ()

if (CMAKE_GENERATOR MATCHES "Xcode")
    message(STATUS "\tXcode Version:        ${XCODE_VERSION}")
endif ()

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "\tMacOS SDK:         ${CMAKE_OSX_SYSROOT}")
endif ()
message(STATUS)

message(STATUS "\tVCPKG Path:               ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS)
message(STATUS "========================================")

# Find External Libraries
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)

# Include Path
target_include_directories(${MY_EXECUTABLE} PRIVATE "include")

# Configure File
## Let CMake define PROJECT_VERSION in C++ code for us,
## so we don't have to edit multiple files when bumping version.
configure_file(VERSION.hpp.in VERSION.hpp)
target_include_directories(${MY_EXECUTABLE} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

# Source Files
## Collect source files and assign them to a variable.
file(GLOB MY_SOURCE CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/Geometry/*.cpp"
    "src/Geometry/2D/*.cpp"
    "src/Geometry/3D/*.cpp"
    "src/Light/*.cpp"
    "src/Shader/*.cpp"
    "src/Util/*.cpp"
    "src/World/*.cpp"
)

## Assign source files to the binary targets.
target_sources(${MY_EXECUTABLE} PRIVATE ${MY_SOURCE})

# =================== Link the Libraries ===================
target_link_libraries(${MY_EXECUTABLE} PRIVATE
    OpenGL::GL
    SDL2::SDL2
    glad::glad
    glm::glm
    imgui::imgui
)

# Setting different compiler configurations on different devices/platforms.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        target_link_libraries(${MY_EXECUTABLE} PRIVATE stdc++fs) # C++ filesystem
    endif ()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(${MY_EXECUTABLE} PRIVATE SDL2::SDL2main)
endif ()

if (MINGW)
    # https://github.com/msys2/MINGW-packages/issues/6380
    add_definitions(-DSDL_MAIN_HANDLED)
endif ()

# Create Symlink to Project Resources
add_custom_command(TARGET ${MY_EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${MY_EXECUTABLE}>/assets"
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    COMMENT
        "Creating symlinks to project resources..."
    VERBATIM
)

# =================== CPack ===================
include(CMakeCPack.cmake)