#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#define MATCH 0
#define INSERT 1
#define DELETE 2

#define MAXLEN 10000

typedef struct {
	int cost;
	int parent;
}cell;

//int MAXLEN = 5;
cell m[MAXLEN + 1][MAXLEN + 1]; //dynamic programming table
int opt[3];

void main() {
	int num;
	
	int i, j, k;

	for (i = 0; i < MAXLEN; i++) {
		row_init(i);
		column_init(i);
	}

	scanf("% d", &num);
	for (int i = 0; i < num; i++) {
		
	}
}


int string_compare(char* s, char* t) {
	for (int i = 1; i < strlen(s); i++) {
		for (int j = 1; j < strlen(t); j++) {
			opt[MATCH] = m[i - 1][j - 1].cost + match(s[i], t[j]);
		}
	}
}

//table init
void row_init(int i) {
	m[0][i].cost = i;

	if (i > 0)
		m[0][i].parent = INSERT;
	else
		m[0][i].parent = -1;
}
void column_init(int i) {
	m[i][0].cost = i;
	if (i > 0)
		m[i][0].parent = DELETE;
	else
		m[i][0].parent = -1;
}