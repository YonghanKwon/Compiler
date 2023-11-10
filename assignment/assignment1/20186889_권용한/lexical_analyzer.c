#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char keyword[][20] = {
	"if","else","while","class","return"
};
char digits[11] = "0123456789";
char digits_nonzero[10] = "123456789";
char alpha[53] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char oper[5] = "+-*/";
char comparison[6][4] = { ">\n","<\n",">=\n","<=\n","==\n","!=\n" };
void tokenlize(char* input_t);
void classify(char* input_t);

int main(int argc,char * argv[]) {
	tokenlize(argv[1]);
	classify(argv[1]);
	remove("temp.txt");//input파일과 output파일 외에 임시로 작성한 파일을 삭제
	return 0;
}

void tokenlize(char* input_t) {
	FILE* input;
	FILE* output;
	char *input_s;
	char bp[1000];
	char temp[100] = "\0";
	char pre_tok[100]="\0";
	int tok_start = 0;
	int tok_end = 0;
	int tok_size = 0;
	int checker = 0;
	int equal_checker = 0;
	int dqm_checker = 0;//큰따옴표 체크
	int sqm_checker = 0;//작은따옴표 체크
	int line = 0;//몇째 줄인지 확인

	input = fopen(input_t, "rt");
	if (input == NULL) {
		printf("input파일을 열지 못하였습니다\n");
		return 1;
	}
	output = fopen("temp.txt", "wt");
	if (output == NULL) {
		printf("output파일을 열지 못하였습니다\n");
		return 1;
	}
	while (input_s = fgets(bp, 1000, input)) {
		line++;
		fprintf(output, "LINE %d\n", line);
		for (int i = 0; i < strlen(input_s); i++) {
			if ((dqm_checker==0||(dqm_checker == 1 && input_s[i] == '\"'))&& (sqm_checker == 0 || (sqm_checker == 1 && input_s[i] == '\''))) {
				char oper[3] = "\0";
				if (input_s[i] == '>' || input_s[i] == '<' || input_s[i] == '=' || input_s[i] == '!') {
					if (input_s[i + 1] == '=') {
						equal_checker = 1;
					}
				}
				if (input_s[i] == ' ' || input_s[i] == '\n' || input_s[i] == '\t' || input_s[i] == '{' || input_s[i] == '}' || input_s[i] == '(' || input_s[i] == ')' || input_s[i] == '\'' || input_s[i] == '\"' || input_s[i] == '\;' || input_s[i] == '\[' || input_s[i] == '\]' || input_s[i] == ',' || input_s[i] == '>' || input_s[i] == '<' || input_s[i] == '=' || input_s[i] == '+' || input_s[i] == '-' || input_s[i] == '*' || input_s[i] == '/' || equal_checker == 1)
				{
					equal_checker = 0;
					tok_size = tok_end - tok_start;
					tok_end++;
					tok_start++;
					if (tok_size) {
						tok_start--;
						memset(pre_tok, '\0',100 * sizeof(char));
						strcpy(pre_tok, temp);
						memset(temp, '\0',100*sizeof(char));
						strncpy(temp, input_s + tok_start, tok_size);
						tok_start = tok_end;
						fprintf(output, "%s\n", temp);
						checker = 1;
					}

					char sp;
					if (input_s[i] == '{')
					{
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "{");
						sp = '{';
						fprintf(output, "%c\n", sp);
						
					}
					else if (input_s[i] == '}') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "}");
						sp = '}';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '(') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "(");
						sp = '(';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == ')') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, ")");
						sp = ')';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '\'') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "\'");
						sqm_checker = (sqm_checker + 1) % 2;
						sp = '\'';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '\"') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "\"");
						dqm_checker = (dqm_checker + 1) % 2;
						sp = '\"';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '\;') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "\;");
						sp = '\;';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '[') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "[");
						sp = '[';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == ']') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "]");
						sp = ']';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == ',') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, ",");
						sp = ',';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '+') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "+");
						sp = '+';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '-') {
						if (strcmp(pre_tok, "=") == 0 || strcmp(pre_tok, "+") == 0 || strcmp(pre_tok, "-") == 0 || strcmp(pre_tok, "*") == 0 || strcmp(pre_tok, "/") == 0 || strcmp(pre_tok, "(") == 0 || strcmp(pre_tok, "return") == 0 || strcmp(pre_tok, ">=") == 0 || strcmp(pre_tok, "<=") == 0 || strcmp(pre_tok, ">") == 0 || strcmp(pre_tok, "<") == 0 || strcmp(pre_tok, "!=") == 0 || strcmp(pre_tok, "==") == 0 || strcmp(pre_tok, ",") == 0)
						{
							fprintf(output, "%c", '-');
						}
						else{
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, "-");
							sp = '-';
							fprintf(output, "%c\n", sp);
						}
					}
					else if (input_s[i] == '*') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "*");
						sp = '*';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '/') {
						memset(pre_tok, '\0', 100 * sizeof(char));
						strcpy(pre_tok, "/");
						sp = '/';
						fprintf(output, "%c\n", sp);
					}
					else if (input_s[i] == '>') {
						if (input_s[i + 1] == '=')
						{
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, ">=");
							char comp[3] = ">=";
							fprintf(output, "%s\n", comp);
							i++;
							tok_start++;
							tok_end++;
						}
						else {
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, ">");
							sp = '>';
							fprintf(output, "%c\n", sp);
						}
					}
					else if (input_s[i] == '<') {
						if (input_s[i + 1] == '=')
						{
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, "<=");
							char comp[3] = "<=";
							fprintf(output, "%s\n", comp);
							i++;
							tok_start++;
							tok_end++;

						}
						else {
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, "<");
							sp = '<';
							fprintf(output, "%c\n", sp);
						}
					}
					else if (input_s[i] == '=') {
						if (input_s[i + 1] == '=')
						{
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, "==");
							char comp[3] = "==";
							fprintf(output, "%s\n", comp);
							i++;
							tok_start++;
							tok_end++;
						}
						else {
							memset(pre_tok, '\0', 100 * sizeof(char));
							strcpy(pre_tok, "=");
							sp = '=';
							fprintf(output, "%c\n", sp);
						}
					}
					else if (input_s[i] == '!') {
					memset(pre_tok, '\0', 100 * sizeof(char));
					strcpy(pre_tok, "!=");
						char not_equal[3] = "!=";
						fprintf(output, "%s\n", not_equal);
						i++;
						tok_start++;
						tok_end++;

					}

				}
				else {
					tok_end++;
					if (checker != 0)
						checker = 0;
				}
			}
			else {
			tok_end++;
			}
		}
		tok_start = 0;
		tok_end = 0;
	}
	fclose(input);
	fclose(output);
}

void classify(char* input_t){
	FILE* input;
	FILE* output;
	char* input_s;
	char bp[100];

	char output_t[100]="\0";
	strncpy(output_t, input_t, strlen(input_t)-4);//.txt
	strcat(output_t, "_output.txt");

	int digit_checker = 0;
	int sQuatMark_checker = 0;
	int dQuatMark_checker = 0;
	int identifier_checker = 0;
	int line = 0;
	int brace_counter = 0;
	int paren_counter = 0;
	int squa_bracket_counter = 0;
	int string_checker = 0;
	int arithmetric_checker = 0;
	int compare_checker = 0;
	input= fopen("temp.txt", "rt");
	if (input == NULL) {
		printf("input파일을 열지 못하였습니다\n");
		return 1;
	}
	output = fopen(output_t, "wt");
	if (output == NULL) {
		printf("output파일을 열지 못하였습니다\n");
		return 1;
	}
	while (input_s = fgets(bp, 100, input)) {
		if (sQuatMark_checker == 0 && dQuatMark_checker == 0) {
			if (strstr(input_s, "LINE") != NULL) {//에러 검출시 몇째줄인지 체크하기 위해
				line++;
			}
			else {
				if (strcmp(input_s, "int\n") == 0)
				{
					fprintf(output, "INT\n");
				}
				else if (strcmp(input_s, "char\n") == 0)
				{
					fprintf(output, "CHAR\n");
				}
				else if (strcmp(input_s, "boolean\n") == 0)
				{
					fprintf(output, "BOOLEAN\n");
				}
				else if (strcmp(input_s, "string\n") == 0)
				{
					fprintf(output, "STRING\n");
				}
				else if (strcmp(input_s, "if\n") == 0)
				{
					fprintf(output, "IF\n");
				}
				else if (strcmp(input_s, "else\n") == 0)
				{
					fprintf(output, "ELSE\n");
				}
				else if (strcmp(input_s, "while\n") == 0)
				{
					fprintf(output, "WHILE\n");
				}
				else if (strcmp(input_s, "class\n") == 0)
				{
					fprintf(output, "CLASS\n");
				}
				else if (strcmp(input_s, "return\n") == 0)
				{
					fprintf(output, "RETURN\n");
				}
				else if (strcmp(input_s, "\;\n") == 0)
				{
					fprintf(output, "TERMINATING SYMBOL\n");
				}
				else if (strcmp(input_s, "(\n") == 0)
				{
					fprintf(output, "LPAREN\n");
					paren_counter++;
				}
				else if (strcmp(input_s, ")\n") == 0)
				{
					fprintf(output, "RPAREN\n");
					paren_counter--;
				}
				else if (strcmp(input_s, "{\n") == 0)
				{
					fprintf(output, "LBRACE\n");
					brace_counter++;
				}
				else if (strcmp(input_s, "}\n") == 0)
				{
					fprintf(output, "RBRACE\n");
					brace_counter--;
				}
				else if (strcmp(input_s, "[\n") == 0)
				{
					fprintf(output, "L SQUARE BRACKETS\n");
					squa_bracket_counter++;
				}
				else if (strcmp(input_s, "]\n") == 0)
				{
					fprintf(output, "R SQUARE BRACKETS\n");
					squa_bracket_counter--;
				}
				else if (strcmp(input_s, ",\n") == 0)
				{
					fprintf(output, "COMMA\n");
				}
				else if (strcmp(input_s, "true\n") == 0 || strcmp(input_s, "false\n") == 0)
				{
					fprintf(output, "BOOL STR\t%s", input_s);
				}
				else if (strcmp(input_s, "\'\n") == 0) {
					sQuatMark_checker = 1;
				}
				else if (strcmp(input_s, "\"\n") == 0) {
					dQuatMark_checker = 1;
				}
				else {
					arithmetric_checker = 0;
					compare_checker = 0;
					digit_checker = 0;
					identifier_checker = 0;
					for (int i = 0; i < 4; i++) {
						if (input_s[0] == oper[i] && input_s[1] == '\n') {
							fprintf(output, "ARITH OPER\t%s", input_s);
							arithmetric_checker = 1;
						}
					}
					
					for (int i = 0; i < 6; i++) {
						if (strcmp(input_s, comparison[i]) == 0) {
							fprintf(output, "COMP OPER\t%s", input_s);
							compare_checker = 1;
						}
					}
					if (input_s[0] == '=' && input_s[1] == '\n') {
						fprintf(output, "ASSIGN OPER\n");
					}
					else if ((input_s[0] == '-' && strchr(digits_nonzero, input_s[1]) != NULL) || strchr(digits, input_s[0]) != NULL) {//integer
						if (input_s[0] == '0' && input_s[1] == '\n') {
							digit_checker = 1;
						}
						else if (input_s[0] == '-' && strchr(digits_nonzero, input_s[1]) != NULL) {
							for (int i = 1; i < strlen(input_s) - 1; i++) {

								if (strchr(digits, input_s[i]) != NULL) {
									if (i == (strlen(input_s) - 2) && input_s[strlen(input_s) - 1] == '\n') {
										digit_checker = 1;
									}
								}
								else
								{
									digit_checker = 0;
									fclose(output);
									output = fopen(output_t, "wt");
									fprintf(output, "LINE %d \tNOT PERMITTED CHARACTER IN INTEGER", line);
									fclose(output);
									return;
									break;
								}
							}
						}
						else if (strchr(digits_nonzero, input_s[0]) != NULL) {
							for (int i = 0; i < strlen(input_s) - 1; i++) {
								if (strchr(digits, input_s[i]) != NULL) {

									if (i == (strlen(input_s) - 2) && input_s[strlen(input_s) - 1] == '\n') {
										digit_checker = 1;
									}
								}
								else
								{
									digit_checker = 0;
									fclose(output);
									output = fopen(output_t, "wt");
									fprintf(output, "LINE %d \tNOT PERMITTED CHARACTER IN INTEGER", line);
									fclose(output);
									return;
									break;
								}
							}
						}
						else {
							fclose(output);
							output = fopen(output_t, "wt");
							fprintf(output, "LINE %d \tIF THE FIRST NUMBER IS 0, THE ONLY PERMITTED INTEGER IS 0", line);
							fclose(output);
							return;
						}
						if (digit_checker == 1 && input_s[strlen(input_s) - 1] == '\n') {
							fprintf(output, "INTEGER\t%s", input_s);
						}
					}
					else if (input_s[0] == '_' || strchr(alpha, input_s[0]) != NULL) {//identifier
						for (int i = 0; i < strlen(input_s) - 1; i++) {
							if (strchr(digits, input_s[i]) != NULL || strchr(alpha, input_s[i]) != NULL || input_s[i] == '_') {
								if (i == strlen(input_s) - 2 && input_s[strlen(input_s) - 1] == '\n') {
									identifier_checker = 1;
								}
							}
							else {
								identifier_checker = 0;
								fclose(output);
								output = fopen(output_t, "wt");
								fprintf(output, "LINE %d \tNOT PERMITTED CHARACTER IN ID", line);
								fclose(output);
								return;
								break;
							}
						}
						if (identifier_checker == 1 && input_s[strlen(input_s) - 1] == '\n') {
							fprintf(output, "ID\t%s", input_s);
						}
					}
					else if(arithmetric_checker==0&&compare_checker==0) {
						fclose(output);
						output = fopen(output_t, "wt");
						fprintf(output, "LINE %d \tNOT PERMITTED CHARACTER. %s CAN NOT SPECIFICATE",line,input_s);
						fclose(output);
						return;
						break;
					}

				}
			}
		}
		
		else if (dQuatMark_checker == 1) {
			if (strcmp(input_s,"\"\n")==0) {
				dQuatMark_checker=0;
			}
			else {
				string_checker = 0;
				for (int i = 0; i < strlen(input_s) - 1; i++) {
					if (strchr(digits, input_s[i]) != NULL || strchr(alpha, input_s[i]) != NULL || input_s[i] == ' ' || input_s[i] == '\t') {
						if (i == strlen(input_s) - 2 && input_s[strlen(input_s) - 1] == '\n') {
							string_checker = 1;
						}
					}
					else {//literal string이 digits와 alphabet, blank로만 구성되기 때문
						string_checker = 0;
						fclose(output);
						output = fopen(output_t, "wt");
						fprintf(output, "LINE %d \tNOT PERMITTED CHARACTER IN LITERAL STRING", line);
						fclose(output);
						return;
						break;
					}
				}
		

				fprintf(output, "LITERALSTRING\t%s", input_s);
			}
		}
		else if (sQuatMark_checker == 1) {
			if (strcmp(input_s,"\'\n")==0) {
				sQuatMark_checker=0;
			}
			else {
				if(strlen(input_s)==2||input_s[0]=='\\')
					fprintf(output, "SINGLECHARATER\t%s", input_s);
				else {
					fclose(output);
					output = fopen(output_t, "wt");
					fprintf(output,"LINE %d\tSINGLE CHARACTER SHOULD BE CONSIST OF THE ONLY CHARACTER",line);
					fclose(output);
					return;
				}
			}
		}
	}
	
	fclose(input);
	fclose(output);
	if (paren_counter != 0) {
		output = fopen(output_t, "wt");
		fprintf(output,"PAREN'S PAIR IS NOT MATCHED");
		fclose(output);
	}
	if (brace_counter != 0) {
		output = fopen(output_t, "wt");
		fprintf(output,"BRACE'S PAIR IS NOT MATCHED");
		fclose(output);
	}
	if (squa_bracket_counter != 0) {
		output = fopen(output_t, "wt");
		fprintf(output, "SQUARE BRACKET'S PAIR IS NOT MATCHED");
		fclose(output);
	}if (dQuatMark_checker != 0) {
		output = fopen(output_t, "wt");
		fprintf(output, "DOUBLE QUATES MARK IS NOT MATCHED");
		fclose(output);
	}if (sQuatMark_checker != 0) {
		output = fopen(output_t, "wt");
		fprintf(output, "SINGLE QUATES MARK IS NOT MATCHED");
		fclose(output);
	}
	return ;
}