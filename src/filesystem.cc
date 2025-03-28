#include <iostream>
#include <string>
#include <cstring>

#include "disk.h"
#include "blocks.h"

using namespace std;

FileSystem::FileSystem () {
	this->diskId = -1;
}

char* Block::serialize (Block block) {
	char *blockArray = new char[BLOCKSIZE];

	

	return blockArray;
}

int FileSystem::mkfs (const string& filename, int size) {
	this->diskId = DiskManager::openDisk(filename, size);
	if ( this->diskId < 0 ) {
		cerr << "Error opening disk" << endl;
	}

	Inode inode;
	inode.setName("root");

	return 0;
}
