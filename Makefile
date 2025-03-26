# Compiler and link editor
CC 	= g++
CFLAGS  = -Wall -g -pedantic -g -I include
LD 	= g++
LDFLAGS  = -Wall -g -I include

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Demo programs
PROGS	= diskDriver

# Object files
LIBDISK_OBJ = $(SRC_DIR)/disk.o

# Source files
SRCS = $(SRC_DIR)/disk.cc $(SRC_DIR)/main.cc

# Header files
HDRS = $(INCLUDE_DIR)/disk.h

# Programs
all:	$(PROGS)

clean:	
	rm -f $(OBJS) $(SRC_DIR)/*.o *~ TAGS
	rm -f $(PROGS)

diskDriver: $(SRC_DIR)/disk.o $(SRC_DIR)/main.o
	$(LD) $(LDFLAGS) -o diskDriver $(SRC_DIR)/main.o $(SRC_DIR)/disk.o

# Object files

$(SRC_DIR)/disk.o: $(SRC_DIR)/disk.cc $(INCLUDE_DIR)/disk.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/disk.cc -o $(SRC_DIR)/disk.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cc $(INCLUDE_DIR)/disk.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cc -o $(SRC_DIR)/main.o
