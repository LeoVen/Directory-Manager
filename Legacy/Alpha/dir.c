#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Directory {
	char *name;
	struct Directory *parent;
	struct Directory *list;
	struct Directory *next;
} Directory;

Directory* getDirectoryByName(char *name);

int main(int argc, char const *argv[])
{
	Directory *root = getDirectoryByName("Hello World");
	printf("Valor: %s", root->name);
	

	return 0;
}

Directory* getDirectoryByName(char *name)
{
	Directory *dir = (Directory *) malloc(sizeof(Directory));
	dir->name = (char *) malloc(sizeof(char) * strlen(name) + 1);
	dir->parent = NULL;
	dir->list = NULL;
	dir->next = NULL;
	int i;
	for (i = 0; i <= strlen(name); i++) {
		dir->name[i] = name[i];
	}
	return dir;
}