#include "codewriter.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>

void BinaryOperationHelper(FILE *outputFile) {
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "A=M-1\n");
  fprintf(outputFile, "D=M\n");
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "M=M-1\n");
  fprintf(outputFile, "A=M-1\n");
}

void UnaryOperationHelper(FILE *outputFile) {
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "A=M-1\n");
}

void ComparisonOperationHelper(enum operation op, size_t *compIndex,
                               FILE *outputFile) {
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "A=M-1\n");
  fprintf(outputFile, "D=M\n");
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "M=M-1\n");
  fprintf(outputFile, "A=M-1\n");
  fprintf(outputFile, "D=M-D\n");
  switch (op) {
  case O_EQ:
    fprintf(outputFile, "@EQUAL.%zu\n", *compIndex);
    fprintf(outputFile, "D;JEQ\n");
    break;
  case O_GT:
    fprintf(outputFile, "@GT.%zu\n", *compIndex);
    fprintf(outputFile, "D;JGT\n");
    break;
  case O_LT:
    fprintf(outputFile, "@LT.%zu\n", *compIndex);
    fprintf(outputFile, "D;JLT\n");
    break;
  default:
    perror("Unhandled operation in comparison op helper:");
    break;
  }
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "A=M-1\n");
  fprintf(outputFile, "M=0\n");
  switch (op) {
  case O_EQ:
    fprintf(outputFile, "@NOTEQUAL.%zu\n", *compIndex);
    break;
  case O_GT:
    fprintf(outputFile, "@NOTGT.%zu\n", *compIndex);
    break;
  case O_LT:
    fprintf(outputFile, "@NOTLT.%zu\n", *compIndex);
    break;
  default:
    perror("Unhandled operation in comparison op helper:");
    break;
  }
  fprintf(outputFile, "0;JMP\n");
  switch (op) {
  case O_EQ:
    fprintf(outputFile, "(EQUAL.%zu)\n", *compIndex);
    break;
  case O_GT:
    fprintf(outputFile, "(GT.%zu)\n", *compIndex);
    break;
  case O_LT:
    fprintf(outputFile, "(LT.%zu)\n", *compIndex);
    break;
  default:
    perror("Unhandled operation in comparison op helper:");
    break;
  }
  fprintf(outputFile, "@SP\n");
  fprintf(outputFile, "A=M-1\n");
  fprintf(outputFile, "M=-1\n");
  switch (op) {
  case O_EQ:
    fprintf(outputFile, "(NOTEQUAL.%zu)\n", *compIndex);
    break;
  case O_GT:
    fprintf(outputFile, "(NOTGT.%zu)\n", *compIndex);
    break;
  case O_LT:
    fprintf(outputFile, "(NOTLT.%zu)\n", *compIndex);
    break;
  default:
    perror("Unhandled operation in comparison op helper:");
    break;
  }
  *compIndex += 1;
}

void WriteArithmetic(enum operation op, size_t *compIndex, FILE *outputFile) {
  // Writes to the output file the assembly code that
  // implements the given arithmetic command.
  switch (op) {
  case O_ADD:
    BinaryOperationHelper(outputFile);
    fprintf(outputFile, "M=D+M\n");
    break;
  case O_SUB:
    BinaryOperationHelper(outputFile);
    fprintf(outputFile, "M=M-D\n");
    break;
  case O_NEG:
    UnaryOperationHelper(outputFile);
    fprintf(outputFile, "M=-M\n");
    break;
  case O_AND:
    BinaryOperationHelper(outputFile);
    fprintf(outputFile, "M=D&M\n");
    break;
  case O_OR:
    BinaryOperationHelper(outputFile);
    fprintf(outputFile, "M=D|M\n");
    break;
  case O_NOT:
    UnaryOperationHelper(outputFile);
    fprintf(outputFile, "M=!M\n");
    break;
  case O_EQ:
    ComparisonOperationHelper(op, compIndex, outputFile);
    break;
  case O_GT:
    ComparisonOperationHelper(op, compIndex, outputFile);
    break;
  case O_LT:
    ComparisonOperationHelper(op, compIndex, outputFile);
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

void PushArgLclThisThatHelper(size_t index, FILE *outputFile) {
  fprintf(outputFile, "D=M\n");
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
}

void PopArgLclThisThatHelper(size_t index, FILE *outputFile) {
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
}

void ConvertNameStatic(enum cmdType commandT, size_t index, FILE *outputFile,
                       char *const inputFilename) {
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
  switch (commandT) {
  case C_PUSH:
    fprintf(outputFile, "@%s\n", varName);
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "A=M\n");
    fprintf(outputFile, "M=D\n");
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "@M=M+1\n");
    break;
  case C_POP:
    fprintf(outputFile, "@SP\n");
    fprintf(outputFile, "M=M-1\n");
    fprintf(outputFile, "A=M\n");
    fprintf(outputFile, "D=M\n");
    fprintf(outputFile, "@%s\n", varName);
    fprintf(outputFile, "M=D\n");
    break;
  default:
    break;
  }
}

void WriteEndFile(FILE *outputFile) {
  fprintf(outputFile, "(END)\n@END\n0;JMP\n");
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
      PushArgLclThisThatHelper(index, outputFile);
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
      PushArgLclThisThatHelper(index, outputFile);
      break;
    case S_PTR:
      switch (index) {
      case 0:
        fprintf(outputFile, "@THIS\n");
        break;
      case 1:
        fprintf(outputFile, "@THAT\n");
        break;
      default:
        perror("Invalid index for pointer segment.");
        errno = 0;
        break;
      }
      fprintf(outputFile, "D=M\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "M=D\n");
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M+1\n");
      break;
    case S_STC:
      ConvertNameStatic(commandT, index, outputFile, inputFilename);
      break;
    case S_TMP:
      fprintf(outputFile, "@5\n");
      fprintf(outputFile, "D=A\n");
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
    case S_THAT:
      fprintf(outputFile, "@THAT\n");
      PushArgLclThisThatHelper(index, outputFile);
      break;
    case S_THIS:
      fprintf(outputFile, "@THIS\n");
      PushArgLclThisThatHelper(index, outputFile);
      break;
    case S_UNKNOWN:
      perror("Unknown segment:");
      break;
    }
    break;
  case C_POP:
    switch (seg) {
    case S_ARG:
      fprintf(outputFile, "@ARG\n");
      PopArgLclThisThatHelper(index, outputFile);
      break;
    case S_CST:
      perror("ERROR: Can't pop on constant segment.");
      errno = 0;
      break;
    case S_LCL:
      fprintf(outputFile, "@LCL\n");
      PopArgLclThisThatHelper(index, outputFile);
      break;
    case S_PTR:
      fprintf(outputFile, "@SP\n");
      fprintf(outputFile, "M=M-1\n");
      fprintf(outputFile, "A=M\n");
      fprintf(outputFile, "D=M\n");
      switch (index) {
      case 0:
        fprintf(outputFile, "@THIS\n");
        break;
      case 1:
        fprintf(outputFile, "@THAT\n");
        break;
      default:
        perror("Invalid index for pointer segment.");
        errno = 0;
        break;
      }
      fprintf(outputFile, "M=D\n");
      break;
    case S_STC:
      ConvertNameStatic(commandT, index, outputFile, inputFilename);
      break;
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
      PopArgLclThisThatHelper(index, outputFile);
      break;
    case S_THIS:
      fprintf(outputFile, "@THIS\n");
      PopArgLclThisThatHelper(index, outputFile);
      break;
    case S_UNKNOWN:
      perror("ERROR: Unknown command:");
      errno = 0;
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
