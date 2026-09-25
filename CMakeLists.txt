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
# RAYLIB (auto-install if missing)
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
# LUA (your settings preserved)
# -----------------------------
if (WIN32)
    include_directories("C:/lua/include")
    link_directories("C:/lua/lib")
    set(LUA_LIB lua)
endif()

if (UNIX)
    find_package(Lua QUIET)

    if (NOT LUA_FOUND)
        message(STATUS "Lua not found — fetching automatically")

        FetchContent_Declare(
            lua54
            URL https://www.lua.org/ftp/lua-5.4.6.tar.gz
        )

        FetchContent_MakeAvailable(lua54)

        add_library(lua STATIC
            ${lua54_SOURCE_DIR}/src/lapi.c
            ${lua54_SOURCE_DIR}/src/lcode.c
            ${lua54_SOURCE_DIR}/src/lctype.c
            ${lua54_SOURCE_DIR}/src/ldebug.c
            ${lua54_SOURCE_DIR}/src/ldo.c
            ${lua54_SOURCE_DIR}/src/ldump.c
            ${lua54_SOURCE_DIR}/src/lfunc.c
            ${lua54_SOURCE_DIR}/src/lgc.c
            ${lua54_SOURCE_DIR}/src/llex.c
            ${lua54_SOURCE_DIR}/src/lmem.c
            ${lua54_SOURCE_DIR}/src/lobject.c
            ${lua54_SOURCE_DIR}/src/lopcodes.c
            ${lua54_SOURCE_DIR}/src/lparser.c
            ${lua54_SOURCE_DIR}/src/lstate.c
            ${lua54_SOURCE_DIR}/src/lstring.c
            ${lua54_SOURCE_DIR}/src/ltable.c
            ${lua54_SOURCE_DIR}/src/ltm.c
            ${lua54_SOURCE_DIR}/src/lundump.c
            ${lua54_SOURCE_DIR}/src/lvm.c
            ${lua54_SOURCE_DIR}/src/lzio.c
            ${lua54_SOURCE_DIR}/src/lauxlib.c
            ${lua54_SOURCE_DIR}/src/lbaselib.c
            ${lua54_SOURCE_DIR}/src/lcorolib.c
            ${lua54_SOURCE_DIR}/src/ldblib.c
            ${lua54_SOURCE_DIR}/src/lmathlib.c
            ${lua54_SOURCE_DIR}/src/lstrlib.c
            ${lua54_SOURCE_DIR}/src/ltablib.c
            ${lua54_SOURCE_DIR}/src/lutf8lib.c
            ${lua54_SOURCE_DIR}/src/loadlib.c
            ${lua54_SOURCE_DIR}/src/loslib.c
        )

        set(LUA_LIB lua)
    else()
        include_directories(${LUA_INCLUDE_DIR})
        set(LUA_LIB ${LUA_LIBRARIES})
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

if (UNIX)
    target_link_libraries(OhNoRetroUFO
        m pthread dl rt X11
    )
endif()

# -----------------------------
# Copy DLLs (Windows only)
# -----------------------------
if (WIN32)
    foreach(DLL raylib.dll libraylib.dll glfw3.dll lua.dll)
        set(DLL_PATH "C:/msys64/mingw64/bin/${DLL}")
        if (EXISTS ${DLL_PATH})
            add_custom_command(TARGET OhNoRetroUFO POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${DLL_PATH}
                    $<TARGET_FILE_DIR:OhNoRetroUFO>
            )
        endif()
    endforeach()
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
