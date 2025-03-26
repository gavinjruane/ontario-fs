#include <iostream>
#include <cstring>
#include "disk.h"
using namespace std;

int main () {
	/*
	Disk *disk_fun = new Disk("disk1", 256);

	cout << "Size: " << disk_fun->getSize() << endl;
	cout << "Name: " << disk_fun->getName() << endl;
	cout << "ID: " << disk_fun->getId() << endl;

	Disk *disk_lol = new Disk("disk2", 513);

	cout << "Size: " << disk_lol->getSize() << endl;
	cout << "Name: " << disk_lol->getName() << endl;
	cout << "ID: " << disk_lol->getId() << endl;

	disk_fun->openDisk();

	delete disk_fun;
	delete disk_lol;
	*/

	int id = DiskManager::openDisk("disk1", 256);
	cout << id << endl;
	int id2 = DiskManager::openDisk("disk2", 513);
	cout << id2 << endl;

	auto disk = DiskManager::findDisk(id2);
	cout << disk->getName() << endl;

	char bufferin[BLOCKSIZE], bufferout[BLOCKSIZE];
	memset(bufferin, '\0', BLOCKSIZE);
	memset(bufferout, '\0', BLOCKSIZE);
	memcpy(bufferout, "clarice wong\n", 13);
	DiskManager::writeBlock(id2, 0, bufferout);
	DiskManager::readBlock(id2, 0, bufferin);

	cout << bufferin << endl;

	DiskManager::closeDisk(id2);

	return 0;
}

