#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

char *allowed = "><+-.,[]", *statements[MAX];
int statIndex;


int main (int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr,"Usage: bftoc <source file>\n");
		return 1;
	}
	int i;
	for (i = 0; i < MAX; ++i) {
		statements[i] = calloc(MAX , sizeof(*statements[i]));
	}
	printPre();
	char *filename = *(argv+1), *line = calloc(MAX , sizeof *line);
	FILE *bfl = fopen(filename, "r");
	while (fscanf(bfl, "%s", line) != EOF) {
		for (; *line; line++) {
			if (!isAllowed(*line)) {
				continue;
			}
			int numsame = numberOfNextSame(line + 1, *line);
			if (*line != '[' && *line != ']') {
				if (*line == '+' || *line == '-' || *line == '>' || *line == '<') {
					print("");
					if (!numsame) {
						if (*line == '+' || *line == '>') {
							printWithoutIndents("++");
						} else {
							printWithoutIndents("--");
						}
					}
					if (*line == '+' || *line == '-') {
						printWithoutIndents("*");
					}
					printWithoutIndents("ptr");
					if (numsame) {
						if (*line == '+' || *line == '>') {
							printWithoutIndents(" += ");
						} else {
							printWithoutIndents(" -= ");
						}
						printNumberWithoutIndents(numsame + 1);
						line += numsame;
					}
					printWithoutIndents(";\n");
				} else {
					printSingleStatement(*line);
				}
			} else if (*line == '[') {
				printLine("while (*ptr) {");
				indentLevel++;
			} else if (*line == ']') {
				indentLevel--;
				printLine("}\n");
			}

		}	
	}
	fclose(bfl);
	printPost();

	printStatements(statements);
	for (i = 0; i < MAX; ++i) {
		free(statements[i]);
	}
	return 0;
}
