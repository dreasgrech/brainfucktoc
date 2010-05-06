#include <string.h>
#include "header.h"


int isAllowed (char c) {
	return strchr(allowed, c) != NULL; 
}

int numberOfNextSame(char *line, char c) {
	int t = 0;
	while (*(line++) == c) {
		t++;
	}
	return t;
}
