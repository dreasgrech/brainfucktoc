#include <string.h>
#include <stdio.h>
#include "header.h"

int contains(char c, char *source) {
	int i, sourceLength = strlen(source);
	for (i = 0; i < sourceLength; ++i) {
		if (c == source[i]) {
			return 1;
		}
	}
	return 0;
}

int numberOfNextSame(char *line, char c, int *totalNumber) {
	*totalNumber = 0;
	int t = 0, lineLength = strlen(line), i;
	char ch;
	for (i = 0; i < lineLength; ++i) {
		(*totalNumber)++;
		ch = line[i];
		int isallowed = contains(ch, allowed);
		if (!isallowed) {
			continue;
		}
		if (ch == c) {
			t++;
		} else {
			break;
		}
	}
	return t;
}

char * strconcat(char *dest, char *src) {
	while (*dest) dest++;
	while ((*dest++ = *src++));
	return --dest;
}
