#ifndef BLOCKS_H
#define BLOCKS_H

#define WRITABLE 248

#define BLK_SUPER   1
#define BLK_INODE   2
#define BLK_EXTENT  3
#define BLK_FREE    4

#define TYPE_DIR    0
#define TYPE_FILE   1

#define RW	    0
#define RO	    1

#define NAME_SIZE   8

#pragma pack(push, 1)
class Block {
	protected:
		char type;
		char magicNumber = 0x44;
		char empty[2] = { 0, 0 };
		int nextFreeBlock; /* also first free block */

	public:
		static int getInodeNum ();
		static int getFreeBlock ();
		int getNextBlock ();
};
#pragma pack(pop)

#pragma pack(push, 1)
class Inode : public Block {
	public:
		Inode ();
//		~Inode ();

		string getName ();
		void setName (const string& _name);
		string getParentDir ();
		void setParentDir (const string& _parentDir);

	private:
		int inode;
		char dirFile;
		char name[9];
		char parentDir[9];
		int parentDirBlock;
		int size;
		int creation;
		int modification;
		int lastAccess;
		int readWrite;
		int itemCount;
};
#pragma pack(pop)

#pragma pack(push, 1)
class Super : public Block {
	private:
		int rootInode;
		int numFreeBlocks;
		int lastFreeBlock;
};
#pragma pack(pop)

#pragma pack(push, 1)
class Free : public Block {
};
#pragma pack(pop)

#pragma pack(push, 1)
class Extent : public Block {
	private:
		char file_data[WRITABLE];
};
#pragma pack(pop)

class FileSystem {
	private:
//		FileEntry *fileTable;
		int diskId;
		int diskMounted;
		int diskBlocks;
		int openFiles;

	public:
		FileSystem ();
//		~FileSystem ();

		int getDiskMounted ();
		int getDiskBlocks ();
		int getOpenFiles ();

		int mkfs (const string& filename, int size);
		int mount ();
		int unmount ();
};

class File {
	public:
		File ();
		~File ();

		int readFileInfo ();
		int rename ();
		int changePermission (char type);
		int write ();
		int read ();
		int open ();
		int close ();
		int seek ();
};

#endif
