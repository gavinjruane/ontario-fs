#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <memory>
#include <algorithm>

#define BLOCKSIZE 256

using namespace std;

class Disk {
	private:
		int id;
		int size;
		string name;
		fstream diskStream;

	public:
		Disk ();
		Disk (string name, int size);
		~Disk ();

		int getSize ();
		void setSize (int _size);
		string getName ();
		int getId ();
		fstream& getDiskStream ();

		string toString ();

	private:
		static int updateDiskId ();
};

class DiskManager {
	private:
		static list<unique_ptr<Disk>> diskList;
	
	public:
		static int openDisk (const string &name, int size);
		static int readBlock (int diskId, int blockNum, void *block);
		static int writeBlock (int diskId, int blockNum, void *block);
		static int closeDisk (int diskId);
		static Disk* findDisk (int id);

	private:
		DiskManager ();
};

#endif
