#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#define disc "hardDisk.hdd"
#define maxfiles 32
#define blocks(size) ((size/block_size)+!!(size%block_size))
#define disk_size (100*1024*1024)
#define block_size (16*1024)
#define start_offset (2*block_size+1)
#define bit_array_start (block_size+1)
#define maxblocks (disk_size/block_size)
#define magic 0x4D524E54

struct fileData{
	char filename[20];
	unsigned int fileSize;
	unsigned int noofblocks;
	unsigned int startBlock;
};

struct metaData{
	unsigned int magicno;
	unsigned int nooffiles;
	unsigned int freeblocks;
	char vector[maxblocks];
	struct fileData fileRecords[maxfiles];
};

void readBlock(int blockno, char buffer[])
{
	FILE * fp = fopen(disc, "rb+");
	if (fp == NULL)
	{
		printf("file not found");
	}
	fseek(fp, blockno*block_size, SEEK_SET);
	fread(buffer, block_size, 1, fp);
	fclose(fp);
}

void writeBlock(int blockno, char *buffer)
{
	FILE * fp = fopen(disc, "rb+");
	if (fp == NULL)
	{
		printf("file not found");
	}
	fseek(fp, blockno*block_size, SEEK_SET);
	fwrite(buffer, block_size, 1, fp);
	fclose(fp);
}

void printFileNames()
{
	int i;
	FILE *fptr = fopen(disc, "rb+");
	if (fptr == NULL)
	{
		printf("Error in opening disc");
		return;
	}
	struct metaData metaData;
	char * buffer = (char*)malloc(block_size);
	readBlock(0, buffer);
	memcpy(&metaData, buffer, block_size);
	for (i = 0; i < metaData.nooffiles; i++)
	{
		puts(metaData.fileRecords[i].filename);
	}
}

int get_file_length(char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("File Not Found!\n");
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	int length_of_file = ftell(fp);
	fclose(fp);
	return (length_of_file+1);
}


void format()
{
	struct metaData metaData;
	char * buffer = (char*)malloc(block_size);
	readBlock(0, buffer);
	puts(buffer);
	memcpy(&metaData, buffer, block_size);
	metaData.magicno = magic;
	metaData.nooffiles = 0;
	metaData.freeblocks = disk_size / block_size - 2;
	char *buff = (char*)calloc(sizeof(char), maxblocks);
	strcpy(metaData.vector, buff);
	memcpy(buffer, &metaData, block_size);
	writeBlock(0, buffer);
}

void debug()
{
	FILE *fptr = fopen(disc, "rb+");
	if (fptr == NULL)
	{
		printf("\nError in opening disc");
		return;
	}
	struct metaData metadata ;
	char * buffer = (char*)malloc(block_size);
	readBlock(0, buffer);
	puts(buffer);
	memcpy(&metadata, buffer, block_size);
	printf("\nMagic no. = %d", metadata.magicno);
	printf("\nFiles present = %d", metadata.nooffiles);
	printf("\nFree blocks = %d", metadata.freeblocks);
}

int isEqual(char *str1, char *str2)
{
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

void getNfreeBlocks(int n,int free[])
{
	int i = 0;
	struct metaData meta;
	char* buf = (char*)malloc(100000);
	readBlock(0, buf);
	memcpy(&meta, buf, sizeof(meta));
	for (i = 1;i<=n && i < blocks(16); i++)
	{
		if (meta.vector[i]==0)
			free[i++] = i;
	}
}

int getFileRecordNo()
{

}

void copyToDisk(char *src, char* dest)
{
	FILE * fp = fopen(src, "rb");
	int lastBlockfp,fileRecord;
	struct metaData temp ;
	int fileLength = get_file_length(src);
	int noOfBlocks = blocks(fileLength);
	int *freeBlocks = (int*)malloc(noOfBlocks);
	getNfreeBlocks(noOfBlocks,freeBlocks);
	char * buf = (char*)malloc(block_size);
	char * metaBuf = (char*)malloc(block_size);
	readBlock(0, metaBuf);
	memcpy(&temp, metaBuf, sizeof(temp));
	fileRecord = getFileRecordNo();
	strcpy(temp.fileRecords[fileRecord].filename, src);
	for (int i = 0; i < noOfBlocks; i++)
	{
		temp.vector[freeBlocks[i]] = 1;
	}
	temp.nooffiles += 1;
	temp.freeblocks -= noOfBlocks;
	for (int i = 0; i < noOfBlocks; i++)
	{
		if (i == noOfBlocks - 1)
		{

		}
		else
		{
			memcpy(buf, fp, sizeof(buf));
			writeBlock(freeBlocks[i], buf);
		}
	}

}

void copyFromDisk(char *src, char* dest)
{
	int start, blockCount;
	int i,j=0,l = get_file_length(src),temp;
	char * buf = (char*)malloc(block_size);
	readBlock(0, buf);
	metaData meta;
	memcpy(&meta, buf, sizeof(meta));
	FILE * fp = fopen(dest, "wb");
	for (i = 0;i< meta.nooffiles;i++)
	{
		if (!stricmp(meta.fileRecords[i].filename, src))
		{
			if(meta.fileRecords[i].noofblocks==1)
			{
				readBlock(meta.fileRecords[i].startBlock, buf);
				fwrite(buf, sizeof(buf), 1, fp);
				return;
			}
			else
			{
				char * temp = (char*)malloc(block_size);
				readBlock(meta.fileRecords[i].startBlock, buf);
				i = 0;
				unsigned int* nextb = (unsigned int*) buf;
				while (i < meta.fileRecords[i].noofblocks)
				{
					readBlock(nextb[i], temp);
					if (i == meta.fileRecords[i].noofblocks - 1)
					{
						if (meta.fileRecords[i].fileSize%block_size == 0)
						{
							fwrite(temp, sizeof(temp), 1, fp);
						}
						else
						{
							fwrite(temp,meta.fileRecords[i].fileSize%block_size, 1, fp);
						}
					}							
					fwrite(temp, sizeof(temp), 1, fp);
					i++;
				}
			}
		}
	}
	if (i == meta.nooffiles)
	{
		printf("No such File exists in Drive");
		return;
	}
}

int main()
{
	char * buffer = (char *)malloc(block_size);
	writeBlock(0, buffer);
	char *command = (char*)malloc(sizeof(char) * 100);
	while (1)
	{
		printf("\n>>");
		gets(command);
		char command1[20] = "", command2[30] = "", command3[30] = "";
		sscanf(command, "%s %s %s", command1, command2, command3);
		if (isEqual(command1, "format") && isEqual(command2, ""))
		{
			format();
		}
		else if (isEqual(command1, "copyToDisk"))
		{
			copyToDisk(command2, command3);
		}
		else if (isEqual(command1, "copyFromDisk"))
		{
			copyFromDisk(command2, command3);
		}
		else if (isEqual(command, "ls"))
		{
			printFileNames();
		}
		else if (isEqual(command1, "delete"))
		{
		    //int i = deletefile(command2);
			int i=0;
			if (i == -1)
				printf("Enter Valid File Name to delete...");
			else
				printf("%s deleted", command2);
		}
		else if (isEqual(command, "debug"))
		{
			debug();
		}
		else
		{
			exit(1);
		}
	}
	system("pause");
	return 0;
}