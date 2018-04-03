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

#include <Directory.h>
#include <StringHandler.h>

int main()
{
	printMenu();
	Directory *root = getDirectoryByName("/");
	
	while (getUserInput(&root)) {}

	free(root);
	printf("\n");
	return 0;
}