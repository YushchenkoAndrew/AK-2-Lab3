# Compiler
CC = g++

# the build target
TARGET = Main

OBJS = Main.o

all: $(TARGET)
	echo Compiled

# Using some built-in Make Macros command
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# Same as: g++ -o Main.out Main.o calculator.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET).out $^

# Applicable for create .o object file.
# '%' matches filename.
# $< is the first pre-requisite
# Same as: g++ -c Main.cpp
#          g++ -c calculator.cpp
%.o: %.c*
	$(CC) -c $<

clean:
	rm $(OBJS) $(TARGET).out
	echo Cleaned