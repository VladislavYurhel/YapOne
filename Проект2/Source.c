#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "states.h"

void getTokens();
void get_token(void);
char *deleteCommentary(char *thisString);
char *getTokenType(char *thisToken);
int isDelim(char c);

char *prog;  /* ��������� �� ������������� ��������� */
char token[80];
char tok_type;

void main() {
	setlocale(LC_ALL, "RUS");
	char newText[300] = { "\0" }, fromFile[100] = { "\0" };

	/* ���������� � ����� */

	FILE *fileForRead;
	fileForRead = fopen("newFile.txt", "r");

	while (!feof(fileForRead)) {
		fscanf(fileForRead, "%c", &fromFile);
		strcat(newText, fromFile);
	}
	fclose(fileForRead);

	/* ����� ���������� */

	newText[strlen(newText) - 1] = NULL;

	strcpy(newText, deleteCommentary(newText));
	prog = &newText;
	getTokens();

	expressionIsTrue();

	system("pause");
}

void getTokens() {
	char temp[30] = { "\0" }, newString[300] = { "\0" };
	int counter = strlen(prog);
	char *token;
	int j = 0;
	printf("%s\n\nALL TOKENS:\n\n", prog);
	for (int i = 0; i < counter; i++) {
		while (*prog && !(isspace(*prog)) && !(isDelim(*prog))) {
			temp[j] = *prog;
			*prog++;
			i++; j++;
		}
		if (strlen(temp) > 0) {
			strcpy(myTokens[countTokens].tokenName, &temp);
			countTokens++;
		}
	

		memset(temp, 0, sizeof(temp));

		if (isDelim(*prog) && ((int)(*prog) != 0)) {
			if ((int)(*prog) == 58) {
				strcpy(temp, ":=");
				*prog++;
			}
			else {
				temp[0] = *prog;
			}
			strcpy(myTokens[countTokens].tokenName, &temp);
			countTokens++;

			memset(temp, 0, sizeof(temp));
		}

		*prog++;
		j = 0;
	}

	for (int i = 0; i < countTokens; i++) {
		printf("<%s>", myTokens[i].tokenName);
		strcpy(myTokens[i].tokenType, getTokenType(myTokens[i].tokenName));
		printf("[%s:%d] ", myTokens[i].tokenType, i);
	}

	printf("\n");

}

char *getTokenType(char *thisToken) {
	char tokenType[30];
	int flag = 1;
	for (int i = 0; i < 2; i++) {
		if (strcmp(thisToken, cycleTokens[i]) == 0) {
			strcpy(tokenType, "CYCLE");
			return tokenType;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (strcmp(thisToken, arithTokens[i]) == 0) {
			strcpy(tokenType, "ARITH");
			return tokenType;
		}
	}
	for (int i = 0; i < strlen(thisToken); i++) {
		if (!isdigit(thisToken[i]))
			flag = 0;
	}
	if (flag == 1) {
		return "CONST";
	}
	if ((strcmp(thisToken, "for")) == 0)
		return "FOR";
	if ((strcmp(thisToken, "do")) == 0)
		return "DO";
	if ((strcmp(thisToken, "begin")) == 0)
		return "BEGIN";
	if ((strcmp(thisToken, "end")) == 0)
		return "END";
	if ((strcmp(thisToken, ":=")) == 0)
		return "ASSIGN";
	if ((strcmp(thisToken, "=")) == 0)
		return "EQUAL";
	if ((strcmp(thisToken, "(")) == 0)
		return "OPEN";
	if ((strcmp(thisToken, ")")) == 0)
		return "CLOSE";
	if ((strcmp(thisToken, ";")) == 0)
		return "ENDEXP";
	return "VAR";
}

int isDelim(char c) {
	if (strchr("+-/*:==();", c))
		return 1;
	return 0;
}

char *deleteCommentary(char *thisString) {
	// 47 - /, 42 - *
	char newString[300] = { "\0" };
	int k = 0;
	int isCommentary = 0;
	for (int j = 0; j < strlen(thisString); j++) {
		if (((int)thisString[j] == 47) && ((int)thisString[j+1] == 42)) {
			isCommentary = 1;
			while (isCommentary && (j < strlen(thisString))) {
				j++;
				if (((int)thisString[j] == 42) && ((int)thisString[j + 1] == 47)) {
					isCommentary = 0;
					j++;
				}
			}
		}
		else {
			newString[k] = thisString[j];
			k++;
		}
	}
	return newString;
}
