#ifndef GLOBALS_H_
#define GLOBALS_H_

#define BUFFER_SIZE 2048
#define MAX_TOKENS_IN_CMD 3
#define PLACEHOLDER_SIZE 15

enum cmdType
{
  C_UNKNOWN = -1,
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL
};

enum segment
{
  S_UNKNOWN = -2,
  S_LCL = 9,
  S_ARG,
  S_THIS,
  S_THAT,
  S_CST,
  S_STC,
  S_TMP,
  S_PTR
};

enum operation
{
  O_UNKNOWN = -3,
  O_ADD = 17,
  O_SUB,
  O_NEG,
  O_LT,
  O_GT,
  O_EQ,
  O_AND,
  O_OR,
  O_NOT
};

#endif // GLOBALS_H_
