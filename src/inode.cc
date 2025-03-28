#include <iostream>
#include <string>
#include <cstring>

#include "disk.h"
#include "blocks.h"

using namespace std;

Inode::Inode () {
	type = BLK_INODE;
	nextFreeBlock = 0x0;
	inode = 0x0;
	dirFile = TYPE_DIR;
	parentDirBlock = 0x0;
	size = 0x0;
	creation = 0x0;
	modification = 0x0;
	lastAccess = 0x0;
	readWrite = RW;
	itemCount = 0x0;
}

string Inode::getName () {
	return this->name;
}

void Inode::setName (const string& _name) {
	_name.copy(this->name, NAME_SIZE);
	this->name[NAME_SIZE] = '\0';
}

string Inode::getParentDir () {
	return this->parentDir;
}

void Inode::setParentDir (const string& _parentDir) {
	_parentDir.copy(this->parentDir, NAME_SIZE);
	this->parentDir[NAME_SIZE] = '\0';
}

