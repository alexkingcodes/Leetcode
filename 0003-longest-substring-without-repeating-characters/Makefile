CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2

TARGET := longest_substring_without_repeating_characters
SOURCES := main.cpp solution.cpp

ifeq ($(OS),Windows_NT)
    EXE := .exe
    RUN_PREFIX :=
else
    EXE :=
    RUN_PREFIX := ./
endif

BINARY := $(TARGET)$(EXE)

all: $(BINARY)

$(BINARY): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(BINARY)
	$(RUN_PREFIX)$<

clean:
	rm -f $(BINARY)

.PHONY: all run clean
