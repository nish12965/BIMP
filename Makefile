# ============================
#  Makefile for BIMP Project
#  Author: Alok Kumar (MCA, MNNIT)
# ============================

# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
LDFLAGS = 

# Executable name
TARGET  = bimp

# Source files
SRCS = main.c tools.c

# Object files (automatically generated from SRCS)
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Build complete! Run with ./$(TARGET)"

# Compile .c to .o
%.o: %.c tools.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "🧹 Cleaned up object files and executable."

# Run the program
run: all
	./$(TARGET)

# Debug build
debug: CFLAGS += -g
debug: clean all
	@echo "🐞 Debug build complete. Use gdb ./$(TARGET)"

.PHONY: all clean run debug
