#include <stdio.h>

typedef struct Directory {
	long id;
	char *dirName;
	struct Directory *parent;
	struct DirList *directories[];
} Directory;

typedef struct DoublyLinkedList {
	// ?
} DirList;


// pwd
// mkdir dirName
// cd
// cd ..
// rm dir dirName
// ls -l

// Usar \b

// Pesquisar strtok()

// Prompt sempre com $

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}