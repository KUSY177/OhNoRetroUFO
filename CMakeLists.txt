cmake_minimum_required(VERSION 3.10)
project(OhNoRetroUFO C)

set(CMAKE_C_STANDARD 11)

# Lua
set(LUA_ROOT "C:/Lua")
set(LUA_INCLUDE_DIR "${LUA_ROOT}/include")
set(LUA_LIBRARIES "${LUA_ROOT}/lib/liblua55.a")
include_directories(${LUA_INCLUDE_DIR})

# SDL2
set(SDL2_ROOT "C:/Users/kuzmi/OneDrive/Desktop/Crossplatform/SDL2/x86_64-w64-mingw32")
set(SDL2_INCLUDE_DIR "${SDL2_ROOT}/include/SDL2")
set(SDL2_LIB_DIR "${SDL2_ROOT}/lib")

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


# Project includes
include_directories(src src/core src/logic)

# Sources
file(GLOB CORE_SRC "src/core/*.c")
file(GLOB LOGIC_SRC "src/logic/*.c")

add_executable(OhNoRetroUFO
    ${CORE_SRC}
    ${LOGIC_SRC}
)

# Linking
target_link_libraries(OhNoRetroUFO
    SDL2main
    SDL2
    ${LUA_LIBRARIES}
    imm32
    winmm
    version
    setupapi
    user32
    gdi32
    advapi32
    shell32
)
