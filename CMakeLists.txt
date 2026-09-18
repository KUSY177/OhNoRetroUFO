cmake_minimum_required(VERSION 3.10)
project(OhNoRetroUFO C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/logic
)

# -----------------------------
# RAYLIB
# -----------------------------
if (WIN32)
    include_directories("C:/msys64/mingw64/include")
    link_directories("C:/msys64/mingw64/lib")
    set(RAYLIB_LIB raylib)
endif()

if (UNIX)
    find_package(raylib REQUIRED)
    set(RAYLIB_LIB raylib)
endif()

# -----------------------------
# LUA
# -----------------------------
if (WIN32)
    include_directories("C:/lua/include")
    link_directories("C:/lua/lib")
    set(LUA_LIB lua)
endif()

if (UNIX)
    find_package(Lua REQUIRED)
    include_directories(${LUA_INCLUDE_DIR})
    set(LUA_LIB ${LUA_LIBRARIES})
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

add_custom_command(TARGET OhNoRetroUFO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/raylib.dll"
        $<TARGET_FILE_DIR:OhNoRetroUFO>
)
add_custom_command(TARGET OhNoRetroUFO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/libraylib.dll"
        $<TARGET_FILE_DIR:OhNoRetroUFO>
)

add_custom_command(TARGET OhNoRetroUFO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/glfw3.dll"
        $<TARGET_FILE_DIR:OhNoRetroUFO>
)
# Копирование ассетов в папку сборки
add_custom_command(
    TARGET OhNoRetroUFO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "${CMAKE_BINARY_DIR}/assets"
)

