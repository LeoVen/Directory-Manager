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
 * Last modified by Leonardo Vencovsky
 *
 * Directory Structure implementations for Directory Manager Project
 *
 * Compiled in Visual Studio 2017
 *
 */

// For Visual Studio (strcpy)
#pragma warning(disable : 4996)

#include "..\include\Directory.h"
#include "..\include\StringHandler.h"

Directory * getDirectoryByName(char *name)
{
	Directory *dir = (Directory *)malloc(sizeof(Directory));
	dir->parent = NULL;
	dir->list = NULL;
	dir->next = NULL;
	time_t now = time(NULL);
	dir->time = strdup(ctime(&now));
	dir->time[strlen(dir->time) - 1] = '\0';
	changeDirName(dir, name);
	return dir;
}

void changeDirName(Directory *dir, char *name)
{
	dir->name = (char *)malloc(sizeof(char) * strlen(name) + 1);
	strcpy(dir->name, name);
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
	time_t now = time(NULL);
	newDir->time = strdup(ctime(&now));
	newDir->time[strlen(newDir->time) - 1] = '\0';
}

int removeDirectory(Directory **curr, char *param)
{
	if (dirExists((*curr), param)) {
		Directory *scanner = (*curr)->list;
		if (hashCode(scanner->name) == hashCode(param)) {
			if (scanner->list == NULL) {
				// Remove first
				(*curr)->list = (*curr)->list->next;
				free(scanner);
			}
			else return 1;
		}
		else {
			Directory *before = scanner;
			scanner = scanner->next;
			while (hashCode(scanner->name) != hashCode(param))
			{
				before = scanner;
				scanner = scanner->next;
			}
			if (scanner->list == NULL) {
				// Jump
				before->next = scanner->next;
				free(scanner);
			}
			else return 1;
		}
	}
	else
		printf("Directory with specified name doesn't exist\n");
	return 0;
}

int forceRemoveDirectory(Directory **curr, char *param)
{
	if (dirExists((*curr), param)) {
		Directory *scanner = (*curr)->list;
		if (hashCode(scanner->name) == hashCode(param)) {
			// Remove first
			(*curr)->list = (*curr)->list->next;
			free(scanner);
		}
		else {
			Directory *before = scanner;
			scanner = scanner->next;
			while (hashCode(scanner->name) != hashCode(param))
			{
				before = scanner;
				scanner = scanner->next;
			}
			// Jump
			before->next = scanner->next;
			free(scanner);
		}
	}
	else
		printf("Directory with specified name doesn't exist\n");
	return 0;
}

int listDirectory(Directory *curr)
{
	Directory *head = curr->list;
	while (head != NULL)
	{
		printf(" %s/\t", head->name);
		head = head->next;
	}
	return 0;
}

int listCompleteDirectory(Directory *curr)
{
	Directory *head = curr->list;
	while (head != NULL)
	{
		printf(" d %s\t%s/\n", head->time, head->name);
		head = head->next;
	}
	return 0;
}

bool dirExists(Directory *curr, char *param)
{
	Directory *scanner = curr->list;
	while (scanner != NULL)
	{
		if (hashCode(param) == hashCode(scanner->name))
			return true;
		scanner = scanner->next;
	}
	return false;
}

int changeDirectory(Directory **curr, char *param)
{
	if (dirExists((*curr), param)) {
		Directory *scanner = (*curr)->list;
		while (scanner != NULL)
		{
			if (hashCode(scanner->name) == hashCode(param)) {
				(*curr) = scanner;
				break;
			}
		}
	}
	else
		printf("Directory with specified name doesn't exist\n");
	return 0;
}

int changeToParent(Directory **curr)
{
	if ((*curr)->parent != NULL)
		(*curr) = (*curr)->parent;
}

int printWorkingDirectory(Directory *curr)
{
	if (hashCode(curr->name) == hashCode("/"))
		printf("/");
	else {
		printWorkingDirectory(curr->parent);
		printf("%s/", curr->name);
	}
	return 0;
}

int printfBeforePrompt(Directory *curr)
{
	if (hashCode(curr->name) == hashCode("/"))
		printf("directory@manager:~/");
	else {
		printfBeforePrompt(curr->parent);
		printf("%s/", curr->name);
	}
	return 0;
}
