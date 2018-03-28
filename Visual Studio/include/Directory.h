/*
* Directory.h
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
* Header for Directory Structure implementations
*
* Compiled in Visual Studio 2017
*
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRNAME_SIZE 20


	typedef struct Directory {
		char *name;
		struct Directory *parent;
		struct Directory *list;
		struct Directory *next;
	} Directory;

	Directory * getDirectoryByName(char *name);

	void changeDirName(Directory *dir, char *name);

	int makeDirectory(Directory **current, char *name);
	
	int listDirectory(Directory **current);

#ifdef __cplusplus
}
#endif