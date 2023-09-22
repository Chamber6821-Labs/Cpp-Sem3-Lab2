
CONFIG ?= config/release.mk
include $(CONFIG) # user configuration for user platform

BUILD_DIR ?= build
FAST_BUILD_DIR ?= $(BUILD_DIR)-fast
CACHE_DIR = $(BUILD_DIR)/make-cache

HEADERS = $(wildcard src/**/*.h)
SOURCES = $(wildcard src/**/*.cpp tests/**/*.cpp)
CODES   = $(HEADERS) $(SOURCES)
CONFIGS = $(wildcard CMakeLists.txt **/CMakeLists.txt)

CLANG_FORMAT_CACHE_FOLDER = $(CACHE_DIR)/clang-format
CLANG_FORMAT_CACHE_FILES = $(foreach x,$(CODES),$(CLANG_FORMAT_CACHE_FOLDER)/$(x).label)

.PHONY: all cmake cmake-fast format test it lint clean all-formatted build-all
all: format test it lint

# Unix Makefiles because CMAKE_EXPORT_COMPILE_COMMAND supported by Makefiles and Ninja
cmake: $(CONFIGS) $(SOURCES) .clang-tidy
	cmake -B $(BUILD_DIR) -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $(CMAKE_OPTIONS)

cmake-fast: $(CONFIGS) $(SOURCES)
	cmake -B $(FAST_BUILD_DIR) -D FAST=ON $(CMAKE_OPTIONS)

format: $(CLANG_FORMAT_CACHE_FILES)

test: TARGET = tests
test: EXECUTABLE = $(FAST_BUILD_DIR)/bin/$(TARGET)
test: cmake-fast $(CODES)
	cmake --build $(FAST_BUILD_DIR) -t $(TARGET) $(CMAKE_BUILD_OPTIONS)
	$(EXECUTABLE) --order-by=rand

it: TARGET = it
it: EXECUTABLE = $(FAST_BUILD_DIR)/bin/$(TARGET)
it: cmake-fast $(CODES)
	cmake --build $(FAST_BUILD_DIR) -t $(TARGET) $(CMAKE_BUILD_OPTIONS)
	$(EXECUTABLE) --order-by=rand

lint: all-formatted build-all

clean:
	cmake -D PATH:STRING=$(BUILD_DIR) -P ./cmake/rm.cmake

all-formatted:
	clang-format --dry-run -Werror $(CODES)

build-all: cmake
	cmake --build $(BUILD_DIR) $(CMAKE_BUILD_OPTIONS)

$(CACHE_DIR):
	cmake -D PATH:STRING=$(CACHE_DIR) -P ./cmake/mkdir-p.cmake

$(CLANG_FORMAT_CACHE_FILES): $(CLANG_FORMAT_CACHE_FOLDER)/%.label: % .clang-format
	cmake -D PATH:STRING=$(dir $@) -P ./cmake/mkdir-p.cmake
	clang-format -i $<
	echo "" > $@
