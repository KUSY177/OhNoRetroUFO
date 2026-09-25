cmake_minimum_required(VERSION 3.10)
project(OhNoRetroUFO C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/logic
)

# -----------------------------
# Detect Web (Emscripten)
# -----------------------------
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    message(STATUS "Building for Web (Emscripten)")

    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
        -s USE_GLFW=3 \
        -s FULL_ES3=1 \
        -s WASM=1 \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s ASYNCIFY \
        -s FORCE_FILESYSTEM=1 \
        -O3")

    FetchContent_Declare(
        raylib_web
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib_web)

    set(RAYLIB_LIB raylib)
    set(LUA_LIB "")

else()
    # -----------------------------
    # Raylib (auto-fetch if missing)
    # -----------------------------
    find_package(raylib QUIET)

    if (NOT raylib_FOUND)
        message(STATUS "Raylib not found — fetching automatically")

        FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.0
        )
        FetchContent_MakeAvailable(raylib)
        set(RAYLIB_LIB raylib)
    else()
        set(RAYLIB_LIB raylib)
    endif()

    # -----------------------------
    # Lua from apk (Alpine)
    # -----------------------------
    if (WIN32)
        include_directories("C:/lua/include")
        link_directories("C:/lua/lib")
        set(LUA_LIB lua)
    else()
        message(STATUS "Using system Lua 5.4 (apk)")

        include_directories(/usr/include/lua5.4)

        # Direct link to Alpine Lua
        set(LUA_LIB /usr/lib/liblua-5.4.so.0)
    endif()
endif()

# -----------------------------
# Sources
# -----------------------------
file(GLOB_RECURSE SOURCES
    src/*.c
    src/*.h
)

add_executable(OhNoRetroUFO ${SOURCES})

# -----------------------------
# Linking
# -----------------------------
target_link_libraries(OhNoRetroUFO
    ${RAYLIB_LIB}
    ${LUA_LIB}
)

if (UNIX AND NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    target_link_libraries(OhNoRetroUFO
        m pthread dl rt X11
    )
endif()

# -----------------------------
# Copy assets
# -----------------------------
add_custom_command(
    TARGET OhNoRetroUFO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_BINARY_DIR}/assets"
)

# -----------------------------
# Copy raylib.dll on Windows
# -----------------------------
# -----------------------------
# Copy DLLs from project folder (Windows)
# -----------------------------
if (WIN32)
    add_custom_command(
        TARGET OhNoRetroUFO POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/glfw3.dll"
            "${CMAKE_BINARY_DIR}/glfw3.dll"
    )

    add_custom_command(
        TARGET OhNoRetroUFO POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/libraylib.dll"
            "${CMAKE_BINARY_DIR}/libraylib.dll"
    )
endif()
