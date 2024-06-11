#include "parser.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>

bool HasMoreCommands(char *currentCmd, FILE *inputFile) {
  // Are there more commands in the input?
  return (fgets(currentCmd, BUFFER_SIZE, inputFile) != NULL);
}

void TokenizeCmd(char *currentCmd,
                 char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]) {
  for (size_t l = 0; l < MAX_TOKENS_IN_CMD; ++l) {
    memset(tokens[l], '0', PLACEHOLDER_SIZE);
  }
  if (currentCmd[0] == '/') {
    return;
  }
  char remainingCmd[strlen(currentCmd)];
  unsigned readBytes = 0;
  size_t idx = 0;
  strncpy(remainingCmd, currentCmd, strlen(currentCmd));
  while (1) {
    readBytes = strcspn(remainingCmd, " ");
    for (size_t i = 0; i < readBytes; ++i) {
      tokens[idx][i] = remainingCmd[i];
    }
    tokens[idx][readBytes] = '\0';
    if (readBytes == strlen(remainingCmd)) {
      break;
    } else {
      unsigned currLength = strlen(remainingCmd);
      for (size_t j = readBytes + 1; j < currLength; ++j) {
        remainingCmd[j - (readBytes + 1)] = remainingCmd[j];
      }
      unsigned newLength = currLength - (readBytes + 1);
      remainingCmd[newLength] = '\0';
    }
    idx++;
  }
}

enum cmdType GetCmdType(char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]) {
  // Returns a cst representing the type of the current command.
  // C_ARITHMETIC is returned for all the arithmetic/logical commands.
  if (!strncmp(tokens[0], "push", strlen("push"))) {
    return C_PUSH;
  }
  if (!strncmp(tokens[0], "pop", strlen("pop"))) {
    return C_POP;
  }
  if (!strncmp(tokens[0], "add", strlen("add")) ||
      !strncmp(tokens[0], "sub", strlen("sub")) ||
      !strncmp(tokens[0], "neg", strlen("neg")) ||
      !strncmp(tokens[0], "eq", strlen("eq")) ||
      !strncmp(tokens[0], "gt", strlen("gt")) ||
      !strncmp(tokens[0], "lt", strlen("lt")) ||
      !strncmp(tokens[0], "and", strlen("and")) ||
      !strncmp(tokens[0], "not", strlen("not")) ||
      !strncmp(tokens[0], "or", strlen("or"))) {
    return C_ARITHMETIC;
  }
  return C_UNKNOWN;
}

enum segment GetSegment(char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]) {
  char *const segName = tokens[1];
  if (!strncmp(segName, "local", strlen("local")))
    return S_LCL;
  if (!strncmp(segName, "argument", strlen("argument")))
    return S_ARG;
  if (!strncmp(segName, "this", strlen("this")))
    return S_THIS;
  if (!strncmp(segName, "that", strlen("that")))
    return S_THAT;
  if (!strncmp(segName, "constant", strlen("constant")))
    return S_CST;
  if (!strncmp(segName, "static", strlen("static")))
    return S_STC;
  if (!strncmp(segName, "temp", strlen("temp")))
    return S_TMP;
  if (!strncmp(segName, "pointer", strlen("pointer")))
    return S_PTR;
  return S_UNKNOWN;
}

enum operation
GetOperation(char tokens[static MAX_TOKENS_IN_CMD][BUFFER_SIZE]) {
  char *const opName = tokens[0];
  if (!strncmp(opName, "add", strlen("add")))
    return O_ADD;
  if (!strncmp(opName, "sub", strlen("sub")))
    return O_SUB;
  if (!strncmp(opName, "neg", strlen("neg")))
    return O_NEG;
  if (!strncmp(opName, "eq", strlen("eq")))
    return O_EQ;
  if (!strncmp(opName, "lt", strlen("lt")))
    return O_LT;
  if (!strncmp(opName, "gt", strlen("gt")))
    return O_GT;
  if (!strncmp(opName, "and", strlen("and")))
    return O_AND;
  if (!strncmp(opName, "or", strlen("or")))
    return O_OR;
  if (!strncmp(opName, "not", strlen("not")))
    return O_NOT;
  return O_UNKNOWN;
}

char *const GetArg1(enum cmdType cmdT, char tokens[static 3][BUFFER_SIZE]) {
  // Returns the first arg of the current command.
  // In the case of C_ARITHMETIC, the command itself is returned.
  // Should not be called if the current command is C_RETURN.
  switch (cmdT) {
  case C_PUSH:
    return tokens[1];
  case C_POP:
    return tokens[1];
  case C_ARITHMETIC:
    return tokens[0];
  case C_RETURN:
    perror("ERROR: GetArg1 should not be called with C_RETURN!\n");
    exit(EXIT_FAILURE);
  default:
    return NULL;
  }
}

int GetArg2(enum cmdType cmdT, char tokens[static 3][BUFFER_SIZE]) {
  // Returns the second argument of the current command.
  // Should be called only if the current command is C_PUSH,
  // C_POP, C_FUNCTION, or C_CALL.
  switch (cmdT) {
  case C_PUSH:
    return strtol(tokens[2], 0, 10);
  case C_POP:
    return strtol(tokens[2], 0, 10);
  case C_FUNCTION:
    return strtol(tokens[2], 0, 10);
  case C_CALL:
    return strtol(tokens[2], 0, 10);
  default:
    perror("ERROR: GetArg1 should not be called with C_RETURN!\n");
    exit(EXIT_FAILURE);
  }
}
