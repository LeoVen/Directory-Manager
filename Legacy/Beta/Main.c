/*
 * Main.c
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
 * Main entrance point to project
 *
 * Compiled in Visual Studio 2017
 *
 */

#include "include\Directory.h"

int main()
{
	printMenu();
	Directory *root = getDirectoryByName("/");
	Directory *curr = root;
	
	while (getUserInput(curr)) {}

	printf("\n");
	return 0;
}
