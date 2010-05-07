#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "header.h"

char *allowed = "><+-.,[]", *statements[MAX], *fileInput;
int statIndex;

void usage()
{
	fprintf(stderr, "Usage: bftoc [-o output-file] <source file>\n");
	fprintf(stderr, " -o output-file\t\t Place the output in output-file\n");
	exit(1);
}

int main (int argc, char *argv[]) {
	int f_id = -1;

	if (argc == 1) {
		usage();
	}
	int c;
	while ((c = getopt (argc, argv, "o:")) != -1)
		if (c == 'o'){
			char *fname = optarg;
			f_id = open (fname, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP); 	
			dup2(f_id, STDOUT_FILENO);
			close(f_id);
		} else {
			usage();
		}
	if (optind < argc)
		argv += optind - 1;
	else 
		usage();
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
