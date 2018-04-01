/*
* Directory.c
*
* EEP
*
* Created on 27/03/2018
* by Leonardo Vencovsky 201710276
* by Guilherme Pinazza  201710351
* by Vitor Facioli      201710292
*
* Last modified on 27/03/2018
* by Leonardo Vencovsky
*
* Directory Structure implementations for Directory Manager Project
*
* Compiled in Visual Studio 2017
*
*/

#include "..\include\Directory.h"

Directory * getDirectoryByName(char *name)
{
	Directory *dir = (Directory *)malloc(sizeof(Directory));
	dir->parent = NULL;
	dir->list = NULL;
	dir->next = NULL;
	changeDirName(dir, name);
	return dir;
}

void changeDirName(Directory *dir, char *name)
{
	dir->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
	int i;
	for (i = 0; i <= strlen(name); i++) {
		dir->name[i] = name[i];
	}
}

int makeDirectory(Directory **current, char *name)
{
	Directory *curr = *current;
	Directory *newDir = (Directory *)malloc(sizeof(Directory));
	changeDirName(newDir, name);
	newDir->list = NULL;
	newDir->parent = curr;
	newDir->next = curr->list;
	curr->list = newDir;
}

int listDirectory(Directory **current)
{
	Directory *curr = *current;
	Directory *head = curr->list;
	printf("\n");
	while (head != NULL)
	{
		printf("\t%s", head->name);
		head = head->next;
	}
	printf("\n");
	return 0;
}