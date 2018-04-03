/*
 * StringHandler.c
 *
 * EEP
 *
 * Created on 01/04/2018
 * by Leonardo Vencovsky 201710276
 * by Guilherme Pinazza  201710351
 * by Vitor Facioli      201710292
 *
 * Last modified by Leonardo Vencovsky
 *
 * String Handling functions
 *
 * Compiled in Visual Studio 2017
 *
 */

#include "..\include\StringHandler.h"

int hashCode(char *command)
{
	int i, hash = 0;
	for (i = 0; i < strlen(command); i++) {
		// Avoiding \0 and \n
		if (command[i] != '\0' && command[i] != '\n')
			hash += command[i] * i;
	}
	return hash;
}

void println(const char *str)
{
	printf("\n%s", str);
}

int checkUserInput(char *userInput)
{
	int i, sp = 0;
	for (i = 0; i < strlen(userInput); i++) {
		// Space
		if (userInput[i] == 32)
			sp++;
	}
	return sp;
}

bool dirNameTest(char *cmd)
{
	// Dir name must not contain spaces
	int i;
	for (i = 0; i < strlen(cmd); i++) {
		if (cmd[i] == ' ')
			return false;
	}
	return true;
}

int normalizeString(char *param)
{
	int i;
	for (i = 0; i < strlen(param); i++)
		if (param[i] == '\n')
			param[i] = '\0';
}

// +-------------------------------------------------------------------------------------------------+
// |                                              Menu                                               |
// +-------------------------------------------------------------------------------------------------+

void printHelpMenu()
{
	println("HelpMenu");
}

void printMenu()
{
	println(" ");
	println(" +-------------------------------------------------------------------+");
	println(" |                                                                   |");
	println(" |                         Directory Manager                         |");
	println(" |                                                                   |");
	println(" |  Created By:                                                      |");
	println(" |                                                                   |");
	println(" |  Guilherme Pinazza                                                |");
	println(" |  Leonardo Vencovsky                                               |");
	println(" |  Vitor Facioli                                                    |");
	println(" |                                                                   |");
	println(" +-------------------------------------------------------------------+");
	println(" ");

	println("Enter 'help' to see command list\n");
}

bool getUserInput(Directory *current)
{
	printf("$ ");
	char *userInput = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
	fgets(userInput, MAX_NAME_SIZE, stdin);
	int sp = checkUserInput(userInput);
	char *next, *command, *param;
	if (sp == 0) {
		// Only one command
		command = strtok_s(userInput, "\0", &next);
		param = NULL;
		return switchCommand(&current, command, param);
	}
	else if (sp == 1) {
		command = strtok_s(userInput, " ", &next);
		param = strtok_s(NULL, "\0", &next);
		return switchCommand(&current, command, param);
	}
	else {
		println("More than two commands is not supported yet");
	}
}

bool switchCommand(Directory **current, char *command, char *parameter)
{
	int hash = hashCode(command);
	if (hash == hashCode("mkdir")) {
		if (parameter != NULL && dirNameTest(parameter)) {
			normalizeString(parameter);
			makeDirectory(current, parameter);
		}
		else
			printf("Directory name must not be empty\n");
	}
	else if (hash == hashCode("ls")) {
		listDirectory(current);
		printf("\n");
	}
	else if (hash == hashCode(CLEAR_SCREEN)) {
		system(CLEAR_SCREEN);
	}
	else if (hash == hashCode("help")) {
		printHelpMenu();
		printf("\n");
	}
	else if (hash == hashCode("exit")) {
		printf("Goodbye!\n");
		return false;
	}
	else {
		printf("No such command. Enter 'help' to see command list\n");
	}
	return true;
}
