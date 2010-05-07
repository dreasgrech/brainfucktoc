#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int statIndex = 0, indentLevel = 0;
char *statements[MAX], *indent = "    ";

void printStatements(char * const *stats) {
	int i;
	for (i = 0; i < statIndex; ++i) {
		printf("%s\n", stats[i]);
	}
}

void printIndents() {
	int i;
	for (i = 0; i < indentLevel; ++i) {
		strncat(statements[statIndex], indent, strlen(indent));
	}
}

void printLine(char *line) {
	printIndents();
	strncat(statements[statIndex++], line, strlen(line));
}

void printWithoutIndents(char *line) {
	strncat(statements[statIndex], line, strlen(line));
}

void print(char *line) {
	printIndents();
	printWithoutIndents(line);
}

void printNumberWithoutIndents(int n) {
	char numbuf[5];
	sprintf(numbuf, "%d", n);
	strncat(statements[statIndex], numbuf, strlen(numbuf));
}

void printExitFunc() {
	printLine("void exitWithStatus(int stat) {");
	indentLevel++;
	printLine("if (start) {");
	indentLevel++;
	printLine("free(start);");
	indentLevel--;
	printLine("}\n");
	printLine("if (stat == 1)");
	indentLevel++;
	printLine("fprintf(stderr,\"\\nError: Out of bounds\\n\");");
	indentLevel--;
	printLine("exit(stat);");
	indentLevel--;
	printLine("}\n");
}

void printPre() {
	printLine("#include <stdio.h>");
	printLine("#include <stdlib.h>\n");
	printLine("char *ptr, *start;\n");
	printExitFunc();
	printLine("int main () {");
	indentLevel++;
	printLine("ptr = calloc(10000, sizeof *ptr);");
	printLine("start = ptr;");
	printLine("int i = 0;\n");
}

void printPost() {
	printLine("");
	printLine("exitWithStatus(0);");
	printLine("return 0;");
	indentLevel--;
	printLine("}");
}

void printSingleStatement (char c) {
	if (c == '.') {
		printLine("putchar(*ptr);");
	} else if (c == ',') {
		printLine("*ptr = getch();");
	}
}

void printCheckBounds() {
	printLine("if ((ptr - start) < 0)");
	indentLevel++;
	printLine("exitWithStatus(1);");
	indentLevel--;
	printLine("");
}
