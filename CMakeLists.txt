cmake_minimum_required(VERSION 3.10)
project(OhNoRetroUFO C)

set(CMAKE_C_STANDARD 11)

# -----------------------------
# Raylib (MSYS2 package)
# -----------------------------
set(raylib_DIR "C:/msys64/mingw64/lib/cmake/raylib")
find_package(raylib REQUIRED)

# -----------------------------
# Lua 5.5 (твоя локальная сборка)
# -----------------------------
set(LUA_ROOT "C:/Lua")
set(LUA_INCLUDE_DIR "${LUA_ROOT}/include")
set(LUA_LIBRARIES "${LUA_ROOT}/lib/liblua55.a")

include_directories(${LUA_INCLUDE_DIR})
include_directories(src/core)
include_directories(src/logic)
include_directories(src/lua)

# -----------------------------
# Project sources
# -----------------------------
file(GLOB CORE_SRC "src/core/*.c")
file(GLOB LOGIC_SRC "src/logic/*.c")

add_executable(OhNoRetroUFO
    src/core/main.c
    ${CORE_SRC}
    ${LOGIC_SRC}
)

# -----------------------------
# Linking
# -----------------------------
target_link_libraries(OhNoRetroUFO
    raylib
    ${LUA_LIBRARIES}
)

if (WIN32)
    target_link_libraries(OhNoRetroUFO
        opengl32
        gdi32
        winmm
    )
endif()

# -----------------------------
# Copy assets after build
# -----------------------------
add_custom_command(TARGET OhNoRetroUFO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_BINARY_DIR}/assets"
)
