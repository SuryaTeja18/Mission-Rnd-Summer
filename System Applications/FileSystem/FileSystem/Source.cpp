#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct fileNode
{
	char fileName[16];
	unsigned start;
	unsigned length;
	int unused;
	struct fileNode* next;
}*head=NULL,*tail=NULL;

int getLength(struct fileNode* head)
{
	if (head == NULL)
		return 0;
	return (1 + getLength(head->next));
}

char * removeSpaces(char ip[])
{
	char *res = (char*)malloc(50);
	char *commands[] = { "copy", "list", "format", "delete","exit"};
	char * temp = (char*)malloc(50);
	int i = 0, j, cmdFlag = 0, resSize = 0;
	while (ip[i] == ' ')
	{
		i++;
	}
	ip = ip + i;
	for (i = 0; i < 5; i++)
	{
		//if (isSub(ip, commands[i]))
		{
			cmdFlag = 1;
			break;
		}
	}
	if (cmdFlag)
	{
		i = 0;
		while (ip[i] != ' ')
		{
			i++;
		}
		i += 1;
		while (ip[i])
		{
			if (ip[i] == ' ')
				ip[i] = '@';
			i++;
		}
	}
	else
	{
		for (i = 0; ip[i]; i++)
			if (ip[i] == ' ')
				ip[i] = '@';
	}
	for (i = 0; ip[i]; i++)
	{
		if (ip[i] != '@')
			res[resSize++] = ip[i];
	}
	res[resSize] = '\0';
	return res;
}

void  implementFormat(FILE * fp)
{
	int n = 0x444E4524D;
	fwrite(&n, sizeof(n), 1, fp);
}

void implementInit()
{
	
}

void implementLs()
{
	struct fileNode temp;
	int t;
	FILE *fp = fopen("hardDisk.hdd", "r");
	if (fp)
	{
		t = ftell(fp);
		while (t<=32)
		{
			fread(&temp, sizeof(temp), 1, fp);
			printf("\nName: %s\tStart: %d\tLengthL %d", temp.fileName, temp.start, temp.length);
		}
	}
	else
	{
		exit(0);
	}
}

/*void * readBlock(int n,int size)
{
	void * buf = malloc(size);
	//memcpy(buf);
}*/

void appendFileNode(char * file,unsigned off,unsigned len,struct fileNode* newNode)
{
	struct fileNode * temp = (struct fileNode*)malloc(sizeof(struct fileNode));
	strcpy(temp->fileName , file);
	temp->length = len;
	temp->next = NULL;
	temp->start = off;
	if (head == NULL)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
	newNode = temp;
}

void updateMeta(FILE *fp, struct fileNode* newFileNode)
{
	int l = getLength(head);
	struct fileNode temp;
	while (fread(&temp, sizeof(temp), 1, fp));
	//fwrite(&newFileNode, sizeof(temp), 1, fp);
}

unsigned int toBlockN(int n)
{
	unsigned int off;
	//fseek(fp, 0, SEEK_CUR);
	off = n * 16384;
	//fseek(fp,off,SEEK_SET);
	return off;
}

void check(FILE *fp)
{
	char ch[100];
	fseek(fp, 0, SEEK_SET);
	struct fileNode temp;
	fread(&temp, sizeof(temp), 1, fp);
	printf("\nName: %s\nStart: %d\nLength: %d", temp.fileName, temp.start, temp.length);
	printf("%s", head->fileName);
	while (!feof(fp))
	{
		printf("%s", fgets(ch, 100, fp));
	}
}

void fromHdd(int bno, char *dest, char* src)
{
	FILE * fp = fopen("hardDisk.hdd","rb");
	//FILE* dp = fopen(dest, "wb");
	if (fp)
	{
		toBlockN(bno);
	}
	_fcloseall();
}

void writeFile(unsigned offset, char* data, char * dest)
{
	FILE * fp = fopen("hardDisk.hdd","w+");
	if (fp)
	{
		struct fileNode newNode;
		printf("\n%s", data);
		appendFileNode(dest, offset, strlen(data),&newNode);
		updateMeta(fp,&newNode);
		check(fp);
		printf("\nFILE ptr present pos.:%d\n", ftell(fp));
		fclose(fp);
		return;
	}
	else
	{
		exit(0);
	}
}

void implementCopy(char* source, char* dest)
{
	char * temp = (char*)malloc(1000);
	char * buf = (char*)malloc(10000);
	FILE * srcFP = fopen(source, "rb");
	if (srcFP != NULL)
	{
		FILE * destFP;
		while (!feof(srcFP))
		{
			fgets(temp, 1000, srcFP);
			buf = strcat(buf, temp);
		}
		unsigned off = 33;
		writeFile(off, buf, dest);
	}
	else
	{
		printf("No such File to copy");
	}
}

void getParameters(char* cmd,char src[], char dest[])
{
	int l = strlen(cmd);
	int i = l-1,srcSize=0,destSize=0;
	while (cmd[i] != ' ')
	{ 
		i--;
	}
	i += 1;
	while (cmd[i])
	{
		dest[destSize++] = cmd[i++];
	}
	dest[destSize] = '\0';
	i = 5;
	while (i<l-destSize)
	{
		src[srcSize++] = cmd[i++];
	}
	src[srcSize] = '\0';
}

void executeCommand(char command[])
{
	//removeSpaces(command);
	char* src = (char*)malloc(100);
	char* dest = (char*)malloc(100);
	switch (command[0])
	{
	case 'c':
		getParameters(command, src, dest);
		implementCopy(src, dest);
		break;
	case 'l':
		implementLs();
		break;
	}
}

int main()
{
		char command[100] = "\0";
		while (1)
		{
			printf("\n>");
			fflush(stdin);
			command[0] = '\0';
			scanf("%[^\n]s", &command);
			executeCommand(command);
		}
	return 0;
}