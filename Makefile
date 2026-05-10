
CXX := g++-15
AR :=  ar

TARGET := liblocation_tracker.a

SRC_DIR := src
INC_DIR := include
OBJ_DIR := build

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

MAX_DEPTH := 256

WARNING := -Wall -Wextra -Werror=return-type
DEFINES := -DMAX_DEPTH=$(MAX_DEPTH) -DLOCAL_DEBUG
CXXFLAGS := -std=c++23 -O3 -I$(INC_DIR) $(DEFINES) $(WARNING)
CPPFLAGS := -MMD -MP

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
	rm -rf $(OBJ_DIR) $(TARGET)

-include $(DEPS)
