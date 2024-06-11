#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

bool HasMoreCommands(char *currentCmd, FILE *inputFile);
enum cmdType GetCmdType(char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]);
enum segment GetSegment(char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]);
enum operation GetOperation(char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]);
char *const GetArg1(enum cmdType cmdT, char tokens[static 3][BUFFER_SIZE]);
int GetArg2(enum cmdType cmdT, char tokens[static 3][BUFFER_SIZE]);
void TokenizeCmd(char *currentCmd,
                 char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]);

#endif // SRC_PARSER_H_
