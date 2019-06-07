#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define disc "hardDisk.hdd"
#define maxfiles 32
#define blocks(size) ((size/block_size)+(size%block_size))
#define disk_size (100*1024*1024)
#define block_size (16*1024)
#define start_offset (2*block_size+1)
#define bit_array_start (block_size+1)
#define maxblocks (disk_size/block_size)
#define magic 0x4D524E54

struct fileinfo{
	char name[20];
	int startingblock;
	int noofblocks;
	int filelength;
};

struct metaData{
	int magicno;
	int nooffiles;
	int freeblocks;
	char vector[maxfiles];
	struct fileinfo filedata[maxfiles];
};

int readblock(int blockno, char buffer[])
{
	FILE * fp = fopen(disc, "rb+");
	if (fp == NULL)
	{
		printf("file not found");
		return -1;
	}
	fseek(fp, blockno*block_size, SEEK_SET);
	fread(buffer, block_size, 1, fp);
	fclose(fp);
	return 1;
}

int writeblock(int blockno, char *buffer)
{
	FILE * fp = fopen(disc, "rb+");
	if (fp == NULL)
	{
		printf("file not found");
		return -1;
	}
	fseek(fp, blockno*block_size, SEEK_SET);
	fwrite(buffer, block_size, 1, fp);
	fclose(fp);
	return 1;
}

int getFileDetails(char *filename, int *startingblock, int *blockcount)
{
	FILE *fptr = fopen(disc, "rb+");
	if (fptr == NULL)
	{
		printf("error in opening disc");
		return -1;

	}
	struct metaData metaData;
	char * buffer = (char *)malloc(block_size);
	int i = readblock(0, buffer);
	memcpy(&metaData, buffer, block_size);
	for (int i = 0; i < metaData.nooffiles; i++)
	{
		if (strcmp(metaData.filedata[i].name, filename) == 0)
		{
			*startingblock = metaData.filedata[i].startingblock;
			*blockcount = metaData.filedata[i].noofblocks;
			return 1;
		}
	}
	fclose(fptr);
	return 0;
}

void printFileNames()
{
	FILE *fptr = fopen(disc, "rb+");
	if (fptr == NULL)
	{
		printf("Error in opening disc");
		return;
	}
	struct metaData metaData;
	char * buffer = (char*)malloc(block_size);
	int i = readblock(0, buffer);
	memcpy(&metaData, buffer, block_size);
	for (i = 0; i < metaData.nooffiles; i++)
	{
		puts(metaData.filedata[i].name);
	}
}

int deletefile(char* filename)
{
	FILE *fptr = fopen(disc, "rb+");
	if (fptr == NULL)
	{
		printf("error in opening disc");
		return -1;

	}
	struct metaData metaData;
	char * buffer = (char*)malloc(block_size);
	int i = readblock(0, buffer);
	memcpy(&metaData, buffer, block_size);
	for (int i = 0; i < metaData.nooffiles; i++)
		if (strcmp(metaData.filedata[i].name, filename) == 0)
			break;
		else
			return -1;
	int startingblock = 0, blockcount = 0;
	i = getFileDetails(metaData.filedata[i].name, &startingblock, &blockcount);
	for (int k = 0; k < blockcount; k++)
		metaData.vector[k + startingblock] = 0;
	memcpy(&metaData.filedata[i], &metaData.filedata[metaData.nooffiles - 1], 32);
	metaData.nooffiles--;
	memcpy(buffer, &metaData, block_size);
	i = writeblock(0, buffer);
	return 1;
}

/*int getFreeBlocks()
{
FILE *fptr = fopen(disc, "rb+");
if (fptr == NULL)
{
printf("error in opening disc");
return -1;
}
struct metadata metadata;
void * buffer = malloc(block_size);
int i = readblock(0, buffer);
memcpy(&metadata, buffer, block_size);
return metadata.freeblocks;
}*/

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
	return length_of_file;
}


void format()
{
	struct metaData metaData;
	char * buffer = (char*)malloc(block_size);
	int i = readblock(0, buffer);
	puts(buffer);
	memcpy(&metaData, buffer, block_size);
	metaData.magicno = magic;
	metaData.nooffiles = 0;
	metaData.freeblocks = disk_size / block_size - 2;
	char *buff = (char*)calloc(sizeof(char), maxblocks);
	strcpy(metaData.vector, buff);
	memcpy(buffer, &metaData, block_size);
	i = writeblock(0, buffer);
}

void debug()
{
	FILE *fptr = fopen(disc, "rb+");
	if (fptr == NULL)
	{
		printf("\nError in opening disc");
		return;
	}
	struct metaData metaData;
	char * buffer = (char*)malloc(block_size);
	int i = readblock(0, buffer);
	puts(buffer);
	memcpy(&metaData,buffer, block_size);
	puts(buffer);
	printf("\nMagic no. = %d", metaData.magicno);
	printf("\nFiles present = %d", metaData.nooffiles);
	printf("\nFree blocks = %d", metaData.freeblocks);
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

void copyToDisk(char *src, char* dest)
{
	struct metaData temp;

}

void copyFromDisk(char *src, char* dest)
{
	int start, blockCount;
	int l = get_file_length(src);
	getFileDetails(src,&start,&blockCount);
	char * metaBuf = (char*)malloc(block_size);
	char * buf = (char*)malloc(block_size);
	FILE * fp = fopen(dest, "wb");
	for (int i = start; i < start + blockCount-1; i++)
	{
		readblock(i, buf);
		//memset()
	}
}

int main()
{
	char * buffer = (char *)malloc(block_size);
	buffer = "Surya";
	writeblock(0, buffer);
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
			int i = deletefile(command2);
			if (i == -1)
				printf("Enter Valid File Name to delete...");
			else
				printf("%s deleted",command2);
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