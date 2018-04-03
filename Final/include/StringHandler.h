/*
 * StringHandler.h
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
 * Header for String handling functions
 *
 * Compiled in Visual Studio 2017
 *
 */

#include "Directory.h"

 /* Functions that prints first menu
  *
  * @Returns [ void ]
  */
void printMenu();

/* Functions that prints help menu
 *
 * @Returns [ void ]
 */
void printHelpMenu();

/* Function that gets user input and separates it to commands and arguments
 *
 * @Param [ Directory *current ] Current working directory
 *
 * @Returns [ bool ] breaks loop if command is exit
 */
bool getUserInput(Directory **current);

/* Function that gets user input and returns how many spaces are in the string
 *
 * @Param [ char *userInput ] User input string
 *
 * @Returns [ int ] How many spaces
 */
int checkUserInput(char *userInput);

/* Command switch
 *
 * @Param [ Directory **current ] Current working directory
 * @Param [ char *command ] Command string
 * @Param [ char *parameter ] Parameter string
 *
 * @Returns [ bool ] breaks loop if command is exit
 */
bool switchCommand(Directory **current, char *command, char *parameter);

/* Returns an integer that represents its hashcode for string comparison
 *
 * @Param [ char *command ] String to get hashcode
 *
 * @Returns [ int ] a number equivalent for a string
 */
int hashCode(char *command);

/* Tests if dir name does not contain spaces
 *
 * @Param [ char *cmd ] Directory name
 *
 * @Returns [ bool ] true if the string passed the test, else false
 */
bool dirNameTest(char *cmd);

/* Prints a line
 *
 * @Param [ const char *str ] String to be printed
 *
 * @Returns [ int ] a number equivalent for a string
 */
void println(const char *str);

char * strcat_head(char *str1, char *str2);