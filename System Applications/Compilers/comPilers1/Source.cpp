#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct variable{
	char name[10];
	int address;
	int size;
};

struct label{
	char name[10];
	int address;
};

struct interlanguage{
	int slno;
	int opcode;
	int parameters[4];
};

int isEqual(char *str1, char *str2)
{
	if (strlen(str1) != strlen(str2))
		return 0;
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

int opcode(char * cmd)
{
	if (isEqual(cmd, "MOVM"))
		return 1;
	if (isEqual(cmd, "MOV"))
		return 2;
	if (isEqual(cmd, "ADD"))
		return 3;
	if (isEqual(cmd, "SUB"))
		return 4;
	if (isEqual(cmd, "MUL"))
		return 5;
	if (isEqual(cmd, "JMP"))
		return 6;
	if (isEqual(cmd, "IF"))
		return 7;
	if (isEqual(cmd, "EQ"))
		return 8;
	if (isEqual(cmd, "LT"))
		return 9;
	if (isEqual(cmd, "GT"))
		return 10;
	if (isEqual(cmd, "LTEQ"))
		return 11;
	if (isEqual(cmd, "GTEQ"))
		return 12;
	if (isEqual(cmd, "PRINT"))
		return 13;
	if (isEqual(cmd, "READ"))
		return 14;
	return 0;
}

int regcode(char * cmd)
{
	if (isEqual(cmd, "AX"))
		return 0;
	if (isEqual(cmd, "BX"))
		return 1;
	if (isEqual(cmd, "CX"))
		return 2;
	if (isEqual(cmd, "DX"))
		return 3;
	if (isEqual(cmd, "EX"))
		return 4;
	if (isEqual(cmd, "FX"))
		return 5;
	if (isEqual(cmd, "GX"))
		return 6;
	if (isEqual(cmd, "HX"))
		return 7;
	return 0;
}

char* getstr(int arr)
{
	int i = 0;
	char* st = (char *)malloc(sizeof(char) * 10);
	char *s = (char *)malloc(sizeof(char) * 10);
	while (arr > 0)
	{
		s[i++] = arr % 10 + '0';
		arr /= 10;
	}
	s[i] = '\0';
	int l = strlen(s);
	for (i = 0; i < l; i++)
		st[i] = s[l - 1 - i];
	st[i] = '\0';
	return st;
}

int getaddress(struct variable variables[], int n, char* name)
{
	for (int i = 0; i < n; i++)
	{
		if (isEqual(variables[i].name, name))
			return variables[i].address;
	}
	return -1;
}

int getlabeladdress(struct label labels[], int labeltop, char * name)
{
	for (int i = labeltop - 1; i >= 0; i--)
	{
		if (isEqual(labels[i].name, name))
			return labels[i].address;
	}
	return -1;
}

int islabel(char *string)
{
	if (string[strlen(string) - 1] == ':')
		return 1;
	return 0;
}
int getnum(char*s)
{
	int l = strlen(s);
	int num = 0;
	for (int i = 0; i < l; i++)
	{
		num = (num * 10) + s[i] - '0';
	}
	return num;
}

int isarray(char* cmd, char * name)
{
	int i, size = 1;
	char num[5] = "";
	int k = 0;
	for (i = 0; cmd[i] != '[' && cmd[i] != '\0' && cmd[i] != '='; i++)
		name[i] = cmd[i];
	if (cmd[i] != '[')
		return 1;
	i++;
	for (i; cmd[i] != ']' && cmd[i] != '\0'; i++)
		num[k++] = cmd[i];
	size = getnum(num);
	return size;
}
char* remco(char * str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == ':' || str[i] == ',')
			str[i] = '\0';
	return str;
}
void write(struct interlanguage intlang[], int instrns, struct variable variables[], int n, struct label labels[], int labeltop, int stack[], int *top, int ocode, char* command2, char *command3, char * command4)
{
	switch (ocode)
	{
	case 1:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = getaddress(variables, n, remco(command2));
		intlang[instrns].parameters[1] = regcode(remco(command3));
		intlang[instrns].parameters[2] = -1;
		intlang[instrns].parameters[3] = -1;
		break;
	case 2:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = regcode(remco(command2));
		intlang[instrns].parameters[1] = getaddress(variables, n, remco(command3));
		intlang[instrns].parameters[2] = -1;
		intlang[instrns].parameters[3] = -1;
		break;
	case 3:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = regcode(remco(command2));
		intlang[instrns].parameters[1] = regcode(remco(command3));
		intlang[instrns].parameters[2] = regcode(remco(command4));
		intlang[instrns].parameters[3] = -1;
		break;
	case 4:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = regcode(remco(command2));
		intlang[instrns].parameters[1] = regcode(remco(command3));
		intlang[instrns].parameters[2] = regcode(remco(command4));
		intlang[instrns].parameters[3] = -1;
		break;
	case 5:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = regcode(remco(command2));
		intlang[instrns].parameters[1] = regcode(remco(command3));
		intlang[instrns].parameters[2] = regcode(remco(command4));
		intlang[instrns].parameters[3] = -1;
		break;
	case 6:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = getlabeladdress(labels, labeltop, command2);
		intlang[instrns].parameters[1] = -1;
		intlang[instrns].parameters[2] = -1;
		intlang[instrns].parameters[3] = -1;
		break;
	case 7:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = regcode(remco(command2));
		intlang[instrns].parameters[1] = regcode(remco(command4));
		intlang[instrns].parameters[2] = regcode(remco(command3));
		intlang[instrns].parameters[3] = 9999;
		stack[*top] = instrns;
		*top += 1;
		break;
	case 13:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = getaddress(variables, n, command2);
		intlang[instrns].parameters[1] = -1;
		intlang[instrns].parameters[2] = -1;
		intlang[instrns].parameters[3] = -1;
		break;
	case 14:
		intlang[instrns].slno = instrns;
		intlang[instrns].opcode = ocode;
		intlang[instrns].parameters[0] = regcode(command2);
		intlang[instrns].parameters[1] = -1;
		intlang[instrns].parameters[2] = -1;
		intlang[instrns].parameters[3] = -1;
		break;
	default:
		printf("error no opcode matched");
		break;
	}
}

void print(struct interlanguage intlang[], int instrns)
{
	for (int i = 0; i < instrns; i++)
	{
		printf("%d	", intlang[i].slno);
		printf("%d	", intlang[i].opcode);
		if (intlang[i].parameters[0] != -1)
			printf("%d	", intlang[i].parameters[0]);
		if (intlang[i].parameters[1] != -1)
			printf("%d	", intlang[i].parameters[1]);
		if (intlang[i].parameters[2] != -1)
			printf("%d	", intlang[i].parameters[2]);
		if (intlang[i].parameters[3] != -1)
			printf("%d	", intlang[i].parameters[3]);
		printf("\n");
	}
}

void updatesymboltable(struct variable variables[], int n, char* command3, int size)
{
	strcpy(variables[n].name, command3);
	int prevsize = 1;
	(variables[n - 1].size == 0 && n>0) ? prevsize = 1 : prevsize = variables[n - 1].size;
	variables[n].address = variables[n - 1].address + prevsize;
	variables[n].size = size;
}

void updatelabeltable(struct label labels[], int labeltop, char* command2, int instrns)
{
	strcpy(labels[labeltop].name, command2);
	labels[labeltop].address = instrns;
}
int main()
{
	char s[20];
	gets(s);
	FILE* fname = fopen(s, "r+");
	//FILE* fout = fopen("out.txt", "w+");
	if (!(fname))
		exit(1);
	char command1[7] = "", command2[7] = "", command3[7] = "", command4[7] = "";
	struct variable variables[25];
	struct label labels[10];
	struct interlanguage intlang[50];
	int stack[10];
	int n = 0, symbolsize = 1, labeltop = 0, instrns = 0, top = 0;
	while (fgets(s, 20, fname))
	{
		sscanf(s, "%s %s %s %s", command1, command2, command3, command4);
		if (isEqual(command1, "DATA"))
		{
			symbolsize = isarray(command2, command3);
			if (n == 0)
			{
				strcpy(variables[0].name, command3);
				variables[0].address = 0;
				variables[0].size = symbolsize;
				n++;
			}
			else
			{
				updatesymboltable(variables, n, command3, symbolsize);
				n++;
			}
		}
		else if (isEqual(command1, "CONST"))
		{
			symbolsize = isarray(command2, command3);
			if (n == 0)
			{
				strcpy(variables[0].name, command3);
				variables[0].address = 0;
				variables[0].size = 0;
				n++;
			}
			else
			{
				updatesymboltable(variables, n, command3, 0);
				n++;
			}
		}
		else if (opcode(command1))
		{
			int ocode = opcode(command1);
			write(intlang, instrns, variables, n, labels, labeltop, stack, &top, ocode, command2, command3, command4);
			instrns++;
		}
		else if (islabel(command1) && !isEqual(command1, "START:") && !isEqual(command1, "END"))
		{
			updatelabeltable(labels, labeltop, remco(command1), instrns);
			labeltop++;
		}
		else if (isEqual(command1, "ELSE"))
		{
			intlang[instrns].slno = instrns;
			intlang[instrns].opcode = 6;
			intlang[instrns].parameters[0] = 9999;
			intlang[instrns].parameters[1] = -1;
			intlang[instrns].parameters[2] = -1;
			intlang[instrns].parameters[3] = -1;
			stack[top] = instrns;
			top++;
			updatelabeltable(labels, labeltop, "ELSE", instrns + 1);
			labeltop++;
			instrns++;
		}
		else if (isEqual(command1, "ENDIF"))
		{
			updatelabeltable(labels, labeltop, "ENDIF", instrns);
			labeltop++;
			int in = stack[--top];
			if (intlang[in].opcode == 6)
			{
				intlang[in].parameters[0] = labels[--labeltop].address;
				int x = stack[--top];
				intlang[x].parameters[3] = labels[--labeltop].address;
			}
			if (intlang[in].opcode == 7)
			{
				intlang[in].parameters[0] = labels[--labeltop].address;
			}
		}
	}
	print(intlang, instrns);
	fclose(fname);
	getchar();
}
