#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <cstring>
#include <list>
#include <memory>
#include <algorithm>

#include "disk.h"

using namespace std;

std::list<std::unique_ptr<Disk>> DiskManager::diskList;

Disk::Disk () {
	this->name = "";
	this->size = 0;
	this->id = updateDiskId();
}

Disk::Disk (string name, int size) {
	this->name = name;
	
	if ( (size < BLOCKSIZE) && (size != 0) ) {
		throw invalid_argument("Size must be greater than BLOCKSIZE");
	} else if ( (size % BLOCKSIZE) != 0 ) {
		size = (size >> 8) * 256;
	}
	this->size = size;

	this->id = updateDiskId();
}

Disk::~Disk () {
	if ( diskStream.is_open() ) {
		diskStream.close();
	}
}

string Disk::toString () {
	return "ID: " + std::to_string(this->id) + "\nSize: " + std::to_string(this->size) + "\nName: " + this->name + "\n\n";
}

int Disk::updateDiskId () {
	static int globalId = 0;

	return globalId++;
}

int Disk::getSize () {
	return this->size;
}

void Disk::setSize (int _size) {
	this->size = _size;
}

int Disk::getId () {
	return this->id;
}

string Disk::getName () {
	return this->name;
}

fstream& Disk::getDiskStream () {
	return this->diskStream;
}

int DiskManager::openDisk (const string &name, int size) {
	/* Variable Declarations */
	int currentDiskId = 0;
	unique_ptr<Disk> newDisk = make_unique<Disk>(name, size);
	fstream &diskStream = newDisk->getDiskStream();

	/* Copy disk ID into temp variable */
	currentDiskId = newDisk->getId();

	/* Open existing disk/create new disk */
	if ( newDisk->getSize() == 0 ) {
		diskStream.open(newDisk->getName(), ios::in | ios::out | ios::binary);
	} else {
		diskStream.open(newDisk->getName(), ios::in | ios::out | ios::binary | ios::trunc);

		/* Initialize disk to 0 */
		for ( int i = 0; i < newDisk->getSize(); i++ ) {
			diskStream.write("\0", 1);
			if ( diskStream.fail() ) {
				cerr << "Error setting up disk" << endl;
				return -1;
			}
		}
	}

	/* Check if there was an issue opening the disk file */
	if ( diskStream.fail() ) {
		cerr << "Error opening disk " << newDisk->getName() << endl;
		return -1;
	}

	/* Add the disk to the list */
	diskList.push_back(move(newDisk));

	return currentDiskId;
}

int DiskManager::closeDisk (int diskId) {
	auto found = std::find_if(diskList.begin(), diskList.end(), 
			[&diskId](const auto& disk) { return disk->getId() == diskId; });

	diskList.erase(found);

	return 0;
}

int DiskManager::readBlock (int diskId, int blockNum, void *block) {
	int offset;
	auto disk_read = findDisk(diskId);
	fstream &diskStream = disk_read->getDiskStream();

	offset = blockNum * BLOCKSIZE;

	diskStream.seekg(offset, ios::beg);

	char buffer[BLOCKSIZE];
	diskStream.read(buffer, BLOCKSIZE);
	memcpy(block, buffer, BLOCKSIZE);

	return BLOCKSIZE;
}

int DiskManager::writeBlock (int diskId, int blockNum, void *block) {
	int offset;
	auto disk_read = findDisk(diskId);
	fstream &diskStream = disk_read->getDiskStream();

	offset = blockNum * BLOCKSIZE;

	diskStream.seekp(offset, ios::beg);

	diskStream.write((char *) block, BLOCKSIZE);

	return BLOCKSIZE;
}

Disk* DiskManager::findDisk (int id) {
	auto found = std::find_if(diskList.begin(), diskList.end(), 
			[&id](const auto& disk) { return disk->getId() == id; });

	if ( found != diskList.end() ) {
		return found->get();
	} else {
		return nullptr;
	}
}

