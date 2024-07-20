#ifndef SRC_CODEWRITER_H_
#define SRC_CODEWRITER_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>
#include <stdlib.h>

#include "globals.h"

void BinaryOperationHelper(FILE *outputFile);
void UnaryOperationHelper(FILE *outputFile);
void ComparisonOperationHelper(enum operation op, size_t *compIndex,
                               FILE *outputFile);
void PushArgLclThisThatHelper(size_t index, FILE *outputFile);
void PopArgLclThisThatHelper(size_t index, FILE *outputFile);
void ConvertNameStatic(enum cmdType commandT, size_t index, FILE *outputFile,
                       char *const inputFilename);
void WriteEndFile(FILE *outputFile);
void WriteArithmetic(enum operation op, size_t *compIndex, FILE *outputFile);
void WritePushPop(enum cmdType commandT, enum segment seg, size_t index,
                  FILE *outputFile, char *const inputFilename);

#endif // SRC_CODEWRITER_H_
