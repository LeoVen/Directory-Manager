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

#include <StringHandler.h>

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

int normalizeString(char *param)
{
	int i;
	for (i = 0; i < strlen(param); i++)
		if (param[i] == '\n')
			param[i] = '\0';
	return 0;
}

// +-------------------------------------------------------------------------------------------------+
// |                                              Menu                                               |
// +-------------------------------------------------------------------------------------------------+

void printHelpMenu()
{
	println("  Command List                                                     ");
	println("                                                                   ");
	println("  help                Shows this help menu                         ");
	println("  exit                Exits program                                ");
	println("  clear               Clears screen                                ");
	println("  ls                  Lists directory content                      ");
	println("  ls -l               Lists directory content with more datail     ");
	println("  mkdir [dir_name]    Makes a directory of name dir_name           ");
	println("  rmdir [dir_name]    Removes directory of name dir_name           ");
	println("  rm [dir_name]       Removes directory either empty or not        ");
	println("  pwd                 Print working directory                      ");
	println("  cd ..               Change directory to parent directory         ");
	println("  cd [dir_name]       Change to directory of name dir_name         ");
	println("                                                                   ");

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

// +-------------------------------------------------------------------------------------------------+
// |                                           User Input                                            |
// +-------------------------------------------------------------------------------------------------+

bool getUserInput(Directory **current)
{
	printfBeforePrompt((*current));
	printf(" $ ");
	char *userInput = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
	fgets(userInput, MAX_NAME_SIZE, stdin);
	int sp = checkUserInput(userInput);
	char *command, *param;
	if (sp == 0) {
		// Only one command
		command = strtok(userInput, "\0");
		param = NULL;
		return switchCommand(current, command, param);
	}
	else if (sp == 1) {
		command = strtok(userInput, " ");
		param = strtok(NULL, "\0");
		return switchCommand(current, command, param);
	}
	else {
		printf("More than two arguments is not supported\n");
	}
	return true;
}

bool switchCommand(Directory **current, char *command, char *parameter)
{
	int hash = hashCode(command);
	if (hash == hashCode("mkdir")) {
		if (parameter != NULL && dirNameTest(parameter)) {
			if (!dirExists((*current), parameter)) {
				if (hashCode(parameter) == hashCode("/")) {
					printf("Directory with name / not allowed\n");
					return 1;
				}
				normalizeString(parameter);
				makeDirectory(current, parameter);
			}
			else
				printf("Directory with specified name already exists\n");
		}
		else
			printf("Directory name must not be empty\n");
	}
	else if (hash == hashCode("pwd")) {
		printf("\t");
		printWorkingDirectory((*current));
		printf("\n");
	}
	else if (hash == hashCode("rmdir")) {
		if (removeDirectory(current, parameter) == 1) {
			printf("Not possible to remove a non-empty directory\n");
		}
	}
	else if (hash == hashCode("rm")) {
		forceRemoveDirectory(current, parameter);
	}
	else if (hash == hashCode("ls")) {
		if (parameter == NULL) {
			listDirectory((*current));
			printf("\n");
		}
		else if (hashCode(parameter) == hashCode("-l")) {
			listCompleteDirectory((*current));
		}
		else {
			printf("Invalid ls parameter");
			printf("\n");
		}
	}
	else if (hash == hashCode(CLEAR_SCREEN)) {
		system(CLEAR_SCREEN);
	}
	else if (hash == hashCode("help")) {
		printHelpMenu();
		printf("\n");
	}
	else if (hash == hashCode("exit")) {
		printf("Goodbye!");
		return false;
	}
	else if (hash == hashCode("cd")) {
		if (hashCode(parameter) == hashCode(".."))
			changeToParent(current);
		else
			changeDirectory(current, parameter);
	}
	else {
		printf("No such command. Enter 'help' to see command list\n");
	}
	return true;
}

// +-------------------------------------------------------------------------------------------------+
// |                                               Checks                                            |
// +-------------------------------------------------------------------------------------------------+

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