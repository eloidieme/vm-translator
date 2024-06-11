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
  char *const inputFileName = argv[1];
  char currentCmd[BUFFER_SIZE];
  char tokens[MAX_TOKENS_IN_CMD][BUFFER_SIZE];
  size_t compIndex = 0;

  inputVM = fopen(inputFileName, "r");
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
    TokenizeCmd(currentCmd, tokens);
    enum cmdType cmdT = GetCmdType(tokens);
    if (cmdT != C_RETURN && cmdT != C_UNKNOWN) {
      if (cmdT == C_ARITHMETIC) {
        enum operation op = GetOperation(tokens);
        fprintf(outputASM, "// %s", currentCmd);
        WriteArithmetic(op, &compIndex, outputASM);
      }
    }
    if (cmdT == C_POP || cmdT == C_PUSH || cmdT == C_CALL ||
        cmdT == C_FUNCTION) {
      int arg2 = GetArg2(cmdT, tokens);
      enum segment seg = GetSegment(tokens);
      fprintf(outputASM, "// %s", currentCmd);
      WritePushPop(cmdT, seg, arg2, outputASM, inputFileName);
    }
  }

  fclose(inputVM);
  return EXIT_SUCCESS;
}
