cmake_minimum_required(VERSION 3.16)
project(SkyDefender C CXX)

# ---------------------------------------------------------
#  Настройки проекта
# ---------------------------------------------------------
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Включаем папки с исходниками
include_directories(src)
include_directories(src/core)
include_directories(src/logic)
include_directories(src/lua)

# ---------------------------------------------------------
#  Опции для платформ
# ---------------------------------------------------------
option(BUILD_WEB "Build for WebAssembly" OFF)

# ---------------------------------------------------------
#  SDL2
# ---------------------------------------------------------
if (BUILD_WEB)
    message(STATUS "Building for WebAssembly (Emscripten)")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_SDL=2 -s USE_SDL_MIXER=2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
        -s USE_SDL=2 \
        -s USE_SDL_MIXER=2 \
        -s ALLOW_MEMORY_GROWTH=1 \
        -s WASM=1 \
        --preload-file assets@/assets \
    ")
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

# ---------------------------------------------------------
#  Lua
# ---------------------------------------------------------
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# ---------------------------------------------------------
#  Источники ядра и логики
# ---------------------------------------------------------
file(GLOB CORE_SRC
    src/core/*.c
    src/core/*.cpp
)

file(GLOB LOGIC_SRC
    src/logic/*.c
    src/logic/*.cpp
)

# ---------------------------------------------------------
#  Основной исполняемый файл
# ---------------------------------------------------------
add_executable(SkyDefender
    ${CORE_SRC}
    ${LOGIC_SRC}
)

if (BUILD_WEB)
    # WebAssembly: SDL уже встроен
    target_link_libraries(SkyDefender ${LUA_LIBRARIES})
else()
    target_link_libraries(SkyDefender ${SDL2_LIBRARIES} ${LUA_LIBRARIES})
endif()

# ---------------------------------------------------------
#  Тесты
# ---------------------------------------------------------
enable_testing()

file(GLOB TEST_SRC tests/unit/*.c tests/integration/*.c)

add_executable(SkyDefenderTests ${TEST_SRC})
target_link_libraries(SkyDefenderTests ${SDL2_LIBRARIES} ${LUA_LIBRARIES})

add_test(NAME RunTests COMMAND SkyDefenderTests)

# ---------------------------------------------------------
#  Установка
# ---------------------------------------------------------
install(TARGETS SkyDefender DESTINATION bin)
install(DIRECTORY assets DESTINATION bin)
