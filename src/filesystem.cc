#include <iostream>
#include <string>

#include "disk.h"
#include "blocks.h"

using namespace std;

FileSystem::FileSystem () {
	this->diskId = -1;
}

int FileSystem::mkfs (const string& filename, int size) {
	this->diskId = DiskManager::openDisk(filename, size);
	if ( this->diskId < 0 ) {
		cerr << "Error opening disk" << endl;
	}

	return 0;
}
