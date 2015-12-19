#define MAX 30

int countTokens = 0;

struct tokensStruct {
	char tokenName[30];
	char tokenType[30];
} myTokens[MAX];

char cycleTokens[2][10] = {
	"downto", "to"
};

char arithTokens[5][3] = {
	"+", "-", "*", "/"
};

void expressionIsTrue();
int E(); int E1(); int E2();
int T();
int EXP(); int EXP1(); int EXP2(); int EXP3(); int EXP4(); int EXP5(); int EXP6(); int EXP7(); int EXP8();
int BRACKETS(); int BRACKETS1(); int BRACKETS2();
int BODY(); int INBODY1(); int INBODY2();
int CYCLEXP();
int term(char *token); int termM(char *token);

int next = 0;
int result;

void expressionIsTrue() {
	result = E();
	char resultS[30];
	if (result == 1) {
		strcpy(resultS, "Okay");
	}
	else
		strcpy(resultS, "Error");
	printf("\nRESULT: %s\n\n", resultS);
	if (next < countTokens - 1)
		printf("Error about [%d] token [%s]\n\n", next, myTokens[next].tokenName);
}

int E() {
	int save = next;
	return E1() || (next = save, E2());
}

int E1() {
	return T() && BODY();
}

int E2() {
	return T() && term("BEGIN") && BODY() && term("END") && ("ENDEXP");
}

int T() {
	return term("FOR") && term("VAR") && term("ASSIGN") && EXP() && term("CYCLE") && EXP() && term("DO");
}

int EXP() {
	int save = next;
	return EXP1() || (next = save, EXP2()) || (next = save, EXP3()) || (next = save, EXP4()) ||
		(next = save, EXP5()) || (next = save, EXP6()) || (next = save, EXP7()) || (next = save, EXP8());
}

int EXP1() {
	return BRACKETS();
}

int EXP2() {
	return BRACKETS() && term("ARITH") && term("CONST");
}

int EXP3() {
	return BRACKETS() && term("ARITH") && EXP();
}

int EXP4() {
	return BRACKETS() && term("ARITH") && term("VAR");
}

int EXP5() {
	return term("VAR") && term("ARITH") && EXP();
}

int EXP6() {
	return term("CONST") && term("ARITH") && EXP();
}

int EXP7() {
	int save = next;
	return term("VAR") || (next = save, (termM("-") && (term("VAR")))) || (next = save, (termM("-") && (term("CONST"))));
}

int EXP8() {
	return term("CONST");
}

int BRACKETS() {
	int save = next;
	return BRACKETS1() || (next = save, BRACKETS2());
}

int BRACKETS1() {
	return term("OPEN") && EXP() && term("CLOSE") && term("ARITH") && EXP();
}

int BRACKETS2() {
	return term("OPEN") && EXP() && term("CLOSE");
}

int BODY() {
	int save = next;
	return INBODY1() || (next = save, INBODY2());
}

int INBODY1() {
	return term("VAR") && term("ASSIGN") && EXP() && term("ENDEXP") && BODY();
}

int INBODY2() {
	return term("VAR") && term("ASSIGN") && EXP() && term("ENDEXP");
}

int CYCLEXP() {
	return EXP();
}

int term(char *token) {
	return !strcmp(myTokens[next++].tokenType, token);
}

int termM(char *token) {
	return !strcmp(myTokens[next++].tokenName, token);
}