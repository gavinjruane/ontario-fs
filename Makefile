# Compiler and link editor
CC 	= g++
CFLAGS  = -Wall -g -pedantic -g -I include
LD 	= g++
LDFLAGS  = -Wall -g -I include

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Demo programs
PROGS	= diskDriver diskTest

# Object files
LIBDISK_OBJ = $(SRC_DIR)/disk.o

# Source files
SRCS = $(SRC_DIR)/disk.cc $(SRC_DIR)/main.cc
LIBS = libDisk.a

# Header files
HDRS = $(INCLUDE_DIR)/disk.h $(INCLUDE_DIR)/blocks.h

# Programs
all:	$(PROGS)

clean:	
	rm -f $(OBJS) $(SRC_DIR)/*.o *~ TAGS
	rm -f $(PROGS)
	rm -f $(LIBS)
	rm -f *.dsk

diskDriver: libDisk.a $(SRC_DIR)/main.o $(SRC_DIR)/filesystem.o $(SRC_DIR)/inode.o
	$(LD) $(LDFLAGS) -o diskDriver $(SRC_DIR)/filesystem.o $(SRC_DIR)/main.o $(SRC_DIR)/inode.o -L . -lDisk

diskTest: libDisk.a $(SRC_DIR)/diskTest.o
	$(LD) $(LDFLAGS) -o diskTest $(SRC_DIR)/diskTest.o -L . -lDisk

# Libraries
libDisk.a: $(SRC_DIR)/disk.o
	ar rcs libDisk.a $(SRC_DIR)/disk.o

# Object files
$(SRC_DIR)/disk.o: $(SRC_DIR)/disk.cc $(INCLUDE_DIR)/disk.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/disk.cc -o $(SRC_DIR)/disk.o

$(SRC_DIR)/diskTest.o: $(SRC_DIR)/diskTest.cc $(INCLUDE_DIR)/disk.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/diskTest.cc -o $(SRC_DIR)/diskTest.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cc $(INCLUDE_DIR)/disk.h $(INCLUDE_DIR)/blocks.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cc -o $(SRC_DIR)/main.o

$(SRC_DIR)/filesystem.o: $(SRC_DIR)/filesystem.cc $(INCLUDE_DIR)/disk.h $(INCLUDE_DIR)/blocks.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/filesystem.cc -o $(SRC_DIR)/filesystem.o

$(SRC_DIR)/inode.o: $(SRC_DIR)/inode.cc $(INCLUDE_DIR)/disk.h $(INCLUDE_DIR)/blocks.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/inode.cc -o $(SRC_DIR)/inode.o

