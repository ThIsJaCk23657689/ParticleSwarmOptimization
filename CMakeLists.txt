cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ==================== Define Variables ====================
set(MY_PROJECT "Particle Swarm Optimization")
set(MY_EXECUTABLE "particle-swarm-optimization")

# ==================== Define Project ====================
project(${MY_PROJECT}  VERSION 1.0 LANGUAGES CXX C)

# =================== Create Binary Targets ====================

## The executable
add_executable(${MY_EXECUTABLE})

# =================== Compiler Settings ====================

## Set C++ standard. Required C++17.
## Turn off compiler extensions for cross-platform portability.
set_target_properties(${MY_EXECUTABLE}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

## Compiler flags for different compilers and different build configurations.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND CompileOptions -Wall -Wextra -pedantic-errors)
    list(APPEND CompileOptions_Debug -ggdb)
    list(APPEND CompileOptions_Release)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    list(APPEND CompileOptions -Wall -Wextra -pedantic-errors)
    list(APPEND CompileOptions_Debug)
    list(APPEND CompileOptions_Release)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    list(APPEND CompileOptions /W4 /permissive-)
    list(APPEND CompileOptions_Debug)
    list(APPEND CompileOptions_Release)
endif ()

## Set the compile options of targets according to the "build configuration".
target_compile_options(${MY_EXECUTABLE} PRIVATE ${CompileOptions})
target_compile_options(${MY_EXECUTABLE} PRIVATE $<$<CONFIG:Debug>:${CompileOptions_Debug}>)
target_compile_options(${MY_EXECUTABLE} PRIVATE $<$<CONFIG:Release>:${CompileOptions_Release}>)

# =================== Build Information ====================
message(STATUS)
message(STATUS "========== Build Information ==========")
message(STATUS "\tHost System Name:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "\tHost System Version:      ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "\tHost System Processor:    ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS)
message(STATUS "\tC Compiler:               ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "\tC Compiler Path:          ${CMAKE_C_COMPILER}")
message(STATUS)
message(STATUS "\tC++ Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:        ${CMAKE_CXX_COMPILER}")
message(STATUS)
message(STATUS "\tVCPKG Path:               ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS)

if (MSVC)
    message(STATUS "\tMSVC Version:         ${MSVC_VERSION}")
    message(STATUS "\tMSVC Toolset:         ${MSVC_TOOLSET_VERSION}")
endif ()

if (CMAKE_GENERATOR MATCHES "Xcode")
    message(STATUS "\tXcode Version:        ${XCODE_VERSION}")
endif ()

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "\tMacOS SDK:         ${CMAKE_OSX_SYSROOT}")
endif ()
message(STATUS "========================================")

# =================== Find External Libraries ===================
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(sdl2-image REQUIRED)
find_package(glm REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)

# =================== Include Path ===================
target_include_directories(${MY_EXECUTABLE} PRIVATE "include")

# =================== Configure File ===================
## Let CMake define PROJECT_VERSION in C++ code for us,
## so we don't have to edit multiple files when bumping version.
configure_file(VERSION.hpp.in VERSION.hpp)
target_include_directories(${MY_EXECUTABLE} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

# =================== Source Files ===================
## Collect source files and assign them to a variable.
file(GLOB MY_SOURCE CONFIGURE_DEPENDS
    "src/*.cpp"
)

## Assign source files to the binary targets.
target_sources(${MY_EXECUTABLE} PRIVATE ${MY_SOURCE})

# =================== Link the Libraries ===================
target_link_libraries(${MY_EXECUTABLE} PRIVATE
    OpenGL::GL
    SDL2::SDL2 SDL2::SDL2_image
    glad::glad
    glm::glm
    imgui::imgui
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        target_link_libraries(${MY_EXECUTABLE} PRIVATE stdc++fs) # C++ filesystem
    endif ()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_link_libraries(${MY_EXECUTABLE} PRIVATE SDL2::SDL2main)
endif ()

if (MINGW)
    # https://github.com/msys2/MINGW-packages/issues/6380
    add_definitions(-DSDL_MAIN_HANDLED)
endif ()

# =================== Create Symlink to Project Resources ===================
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