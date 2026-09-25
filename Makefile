CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./src/core -I./src/logic

ifeq ($(OS),Windows_NT)
    LUA_INC = C:/lua/include
    LUA_LIBDIR = C:/lua/lib
    LUA_LIB = -llua
    CFLAGS += -I$(LUA_INC)
    LDFLAGS = -L$(LUA_LIBDIR) -lraylib -lm -lpthread -ldl
endif

# Linux / macOS
ifeq ($(shell uname),Linux)
    LUA_LIB = -llua
    LDFLAGS = -lraylib -lm -lpthread -ldl
endif

ifeq ($(shell uname),Darwin)
    LUA_LIB = -llua
    LDFLAGS = -lraylib -lm -lpthread -ldl
endif

# Исходники игры
CORE_SRC = \
    src/core/main.c \
    src/core/update.c \
    src/core/entities.c \
    src/core/collision.c \
    src/core/resources.c \
    src/core/renderer.c \
    src/core/input.c \
    src/core/timer.c \
    src/core/lua_bridge.c

LOGIC_SRC = src/logic/lua_bindings.c

SRC = $(CORE_SRC) $(LOGIC_SRC)
OBJ = $(SRC:.c=.o)

# Тесты
UNIT_TESTS = tests/unit/test_collision tests/unit/test_entities
INTEGRATION_TESTS = tests/integration/test_wave

# ------------------------------------------------------------
# Сборка игры
# ------------------------------------------------------------
game: $(OBJ)
	$(CC) $(OBJ) -o game $(LDFLAGS) $(LUA_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------------
# Сборка модульных тестов
# ------------------------------------------------------------
tests/unit/test_collision: tests/unit/test_collision.c src/core/collision.c
	$(CC) $(CFLAGS) $^ -o $@

tests/unit/test_entities: tests/unit/test_entities.c src/core/entities.c src/core/collision.c src/logic/lua_bindings.c
	$(CC) $(CFLAGS) $^ -o $@ $(LUA_LIB)

# ------------------------------------------------------------
# Сборка интеграционных тестов
# ------------------------------------------------------------
tests/integration/test_wave: tests/integration/test_wave.c src/core/entities.c src/core/collision.c src/logic/lua_bindings.c
	$(CC) $(CFLAGS) $^ -o $@ $(LUA_LIB)

# ------------------------------------------------------------
# Запуск всех тестов
# ------------------------------------------------------------
test: $(UNIT_TESTS) $(INTEGRATION_TESTS)
	@echo "=== UNIT TESTS ==="
	@./tests/unit/test_collision || exit 1
	@./tests/unit/test_entities || exit 1
	@echo "=== INTEGRATION TESTS ==="
	@./tests/integration/test_wave || exit 1
	@echo "=== ALL TESTS PASSED ==="

# ------------------------------------------------------------
# Очистка
# ------------------------------------------------------------
clean:
	rm -f $(OBJ) game
	rm -f tests/unit/test_collision tests/unit/test_entities
	rm -f tests/integration/test_wave
