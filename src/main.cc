#include <iostream>
#include <cstring>
#include "disk.h"
#include "blocks.h"
using namespace std;

int main () {
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

	FileSystem fs;
	fs.mkfs("Hello", 512);

	cout << "success" << endl;

	DiskManager::closeDisk(id2);

	return 0;
}

