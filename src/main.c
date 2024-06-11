/* Copyright 2024 Eloi DIEME */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codewriter.h"
#include "globals.h"
#include "parser.h"

int main(int argc, char *argv[argc + 1]) {
  FILE *inputVM;
  char currentCmd[BUFFER_SIZE];
  char tokens[MAX_TOKENS_IN_CMD][BUFFER_SIZE];
  size_t compIndex = 0;

  inputVM = fopen(argv[1], "r");
  if (inputVM == NULL) {
    perror("Error opening input file:");
    errno = 0;
    fclose(inputVM);
    return EXIT_FAILURE;
  }

  FILE *outputASM;

  outputASM = fopen(argv[2], "w");
  if (outputASM == NULL) {
    perror("Error opening output file:");
    errno = 0;
    fclose(outputASM);
    return EXIT_FAILURE;
  }

  while (HasMoreCommands(currentCmd, inputVM)) {
    printf("%s", currentCmd);
    TokenizeCmd(currentCmd, tokens);
    enum cmdType cmdT = GetCmdType(tokens);
    printf("%d ", cmdT);
    if (cmdT != C_RETURN && cmdT != C_UNKNOWN) {
      char *const arg1 = GetArg1(cmdT, tokens);
      char *loc = strchr(arg1, '\n');
      if (loc) {
        *(loc - 1) = '\0';
      }
      printf("%s ", arg1);
      if (cmdT == C_ARITHMETIC) {
        enum operation op = GetOperation(tokens);
        fprintf(outputASM, "// %s", currentCmd);
        WriteArithmetic(op, &compIndex, outputASM);
      }
    } else {
      printf("(na1) ");
    }
    if (cmdT == C_POP || cmdT == C_PUSH || cmdT == C_CALL ||
        cmdT == C_FUNCTION) {
      int arg2 = GetArg2(cmdT, tokens);
      enum segment seg = GetSegment(tokens);
      fprintf(outputASM, "// %s", currentCmd);
      WritePushPop(cmdT, seg, arg2, outputASM, "BasicTest.vm");
      printf("%d\n", arg2);
    } else {
      printf("(na2)\n");
    }
  }

  fclose(inputVM);
  return EXIT_SUCCESS;
}
