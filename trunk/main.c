#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

char *allowed = "><+-.,[]", *statements[MAX], *fileInput;
int statIndex;

int main (int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr,"Usage: bftoc <source file>\n");
		return 1;
	}
	int i;
	fileInput = calloc(MAX, sizeof *fileInput);
	for (i = 0; i < MAX; ++i) {
		statements[i] = calloc(MAX , sizeof(*statements[i]));
	}
	printPre();
	char *filename = *(argv+1), *line = calloc(MAX , sizeof *line), *copyFileInput = fileInput;
	FILE *bfl = fopen(filename, "r");
	while (fgets(line, MAX, bfl)) {
		fileInput = strconcat(fileInput, line);
	}
	fileInput = copyFileInput;
	char ch;
	while ((ch = *fileInput++)) {
		int isallowed = contains(ch, allowed);
		if (!isallowed) {
			continue;
		}
		int totalNumber = 0;
		int numsame = numberOfNextSame(fileInput, ch, &totalNumber);
		if (ch != '[' && ch != ']') {
			if (ch == '+' || ch == '-' || ch == '>' || ch == '<') {
				int setCheckOnBounds = 0;
				print("");
				if (!numsame) {
					if (ch == '+' || ch == '>') {
						printWithoutIndents("++");
					} else {
						printWithoutIndents("--");
						if (ch == '<')
							setCheckOnBounds = 1;
					}
				}
				if (ch == '+' || ch == '-') {
					printWithoutIndents("*");
				}
				printWithoutIndents("ptr");
				if (numsame) {
					if (ch == '+' || ch == '>') {
						printWithoutIndents(" += ");
					} else {
						printWithoutIndents(" -= ");
						if (ch == '<')
							setCheckOnBounds = 1;
					}
					printNumberWithoutIndents(numsame + 1);
					fileInput += totalNumber - 1;
				}
				printWithoutIndents(";\n");
				if (setCheckOnBounds)
					printCheckBounds();
			} else {
				printSingleStatement(ch);
			}
		} else if (ch == '[') {
			printLine("while (*ptr) {");
			indentLevel++;
		} else if (ch == ']') {
			indentLevel--;
			printLine("}\n");
		}
	}
	fclose(bfl);
	printPost();

	printStatements(statements);
	for (i = 0; i < MAX; ++i) {
		if (statements[i])
			free(statements[i]);
	}

	if (copyFileInput)
		free(copyFileInput);

	if (line)
		free(line);
	return 0;
}
