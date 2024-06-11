#include "codewriter.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>

void WriteArithmetic(enum operation op, FILE *outputFile) {
  // Writes to the output file the assembly code that
  // implements the given arithmetic command.
  switch (op) {
  case O_ADD:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=D+M\n");
    break;
  case O_SUB:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=M-D\n");
    break;
  case O_NEG:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=-M\n");
    break;
  case O_AND:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=D&M\n");
    break;
  case O_OR:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=D|M\n");
    break;
  case O_NOT:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=!M\n");
    break;
  case O_EQ:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M-D\n");
    fprintf(outputFile, "@EQUAL\n");
    fprintf(outputFile, "D;JEQ\n");
    fprintf(outputFile, "@NOTEQUAL\n");
    fprintf(outputFile, "0;JMP\n");
    fprintf(outputFile, "(EQUAL)\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=1\n");
    fprintf(outputFile, "(NOTEQUAL)\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=0\n");
    break;
  case O_GT:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M-D\n");
    fprintf(outputFile, "@GT\n");
    fprintf(outputFile, "D;JGT\n");
    fprintf(outputFile, "@NOTGT\n");
    fprintf(outputFile, "0;JMP\n");
    fprintf(outputFile, "(GT)\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=1\n");
    fprintf(outputFile, "(NOTGT)\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=0\n");
    break;
  case O_LT:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "D=M-D\n");
    fprintf(outputFile, "@LT\n");
    fprintf(outputFile, "D;JLT\n");
    fprintf(outputFile, "@NOTLT\n");
    fprintf(outputFile, "0;JMP\n");
    fprintf(outputFile, "(LT)\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=1\n");
    fprintf(outputFile, "(NOTLT)\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M-1\n");
    fprintf(outputFile, "M=0\n");
    break;
  case O_UNKNOWN:
    perror("ERROR: Unknown operation:");
    errno = 0;
    break;
  default:
    perror("ERROR: Operation not in enum:");
    errno = 0;
    break;
  }
}
void WritePushPop(enum cmdType commandT, enum segment seg, size_t index,
                  FILE *outputFile, char *const inputFilename) {
  // Writes to the ouptut file the assembly code that
  // implements the given command, where command is either
  // C_PUSH or C_POP.
  switch (commandT) {
  case C_PUSH:
    switch (seg) {
    case S_ARG:
      fprintf(outputFile, "@ARG\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R14\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M+1\n");
      break;
    case S_CST:
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=A\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M+1\n");
      break;
    case S_LCL:
      fprintf(outputFile, "@LCL\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R14\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M+1\n");
      break;
    case S_PTR:
      fprintf(outputFile, "@SP\n");
      break;
    case S_STC:
      fprintf(outputFile, "@SP\n");
      break;
    case S_TMP:
      fprintf(outputFile, "@SP\n");
      break;
    case S_THAT:
      fprintf(outputFile, "@THAT\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R14\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M+1\n");
      break;
    case S_THIS:
      fprintf(outputFile, "@THIS\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R14\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M+1\n");
      break;
    case S_UNKNOWN:
      fprintf(outputFile, "@SP\n");
      break;
    }
    break;
  case C_POP:
    switch (seg) {
    case S_ARG:
      fprintf(outputFile, "@ARG\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=A\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      break;
    case S_CST:
      perror("ERROR: Can't pop on constant segment.");
      errno = 0;
      break;
    case S_LCL:
      fprintf(outputFile, "@LCL\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=A\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      break;
    case S_PTR:
      switch (index) {
      case 0:
        fprintf(outputFile, "@SP\n");
        fprintf(outputFile, "M=M-1\n");
        fprintf(outputFile, "A=M\n");
        fprintf(outputFile, "D=M\n");
        fprintf(outputFile, "@THIS\n");
        fprintf(outputFile, "M=D\n");
        break;
      case 1:
        fprintf(outputFile, "@SP\n");
        fprintf(outputFile, "M=M-1\n");
        fprintf(outputFile, "A=M\n");
        fprintf(outputFile, "D=M\n");
        fprintf(outputFile, "@THAT\n");
        fprintf(outputFile, "M=D\n");
        break;
      default:
        perror("Invalid index for pointer segment.");
        errno = 0;
        break;
      }
      break;
    case S_STC: {
      char varName[strlen(inputFilename) + 10];
      size_t k;
      for (k = 0; k < strlen(inputFilename); ++k) {
        if (inputFilename[k] != '.') {
          varName[k] = inputFilename[k];
        } else {
          break;
        }
      }
      varName[k] = '.';
      int strIndexSize = (int)((ceil(log10(index)) + 1) * sizeof(char));
      char strindex[strIndexSize];
      snprintf(strindex, strIndexSize, "%zu", index);
      for (size_t l = 0; l < strIndexSize; ++l) {
        varName[k + l + 1] = strindex[l];
      }
      varName[k + strIndexSize + 1] = '\0';
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@%s\n", varName);
      fprintf(outputFile, "M=D\n");
    } break;
    case S_TMP:
      fprintf(outputFile, "@5\n");
      fprintf(outputFile, "D=A\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      break;
    case S_THAT:
      fprintf(outputFile, "@THAT\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=A\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      break;
    case S_THIS:
      fprintf(outputFile, "@THIS\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=A\n");
      fprintf(outputFile, "@%zu\n", index);
      fprintf(outputFile, "D=D+A\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@R13\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      break;
    case S_UNKNOWN:
      break;
    }
    break;
  case C_UNKNOWN:
    perror("ERROR: Unknown command:");
    errno = 0;
    break;
  default:
    perror("ERROR: Command not in enum:");
    errno = 0;
    break;
  }
}
