#ifndef SRC_CODEWRITER_H_
#define SRC_CODEWRITER_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>

#include "globals.h"

void WriteArithmetic(enum operation op, size_t *compIndex, FILE *outputFile);
void WritePushPop(enum cmdType commandT, enum segment seg, size_t index,
                  FILE *outputFile, char *const inputFilename);

#endif // SRC_CODEWRITER_H_
