#define MAX 1000

extern int statIndex;
extern int indentLevel;
extern char *allowed;

extern char *statements[MAX];

void printStatements(char * const *statements);
void printIndents(); 
void printLine(char *line);
void printWithoutIndents(char *line); 
void print(char *line);
void printNumberWithoutIndents(int n);
void printPre();
void printPost();
void printSingleStatement (char c);

int contains (char c, char *source);
int numberOfNextSame(char *line, char c, int *totalNumber);
char *strconcat(char *dest, char *source);
