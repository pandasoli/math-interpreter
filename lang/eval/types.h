
#ifndef EVAL_TYPES
#define EVAL_TYPES

struct Eval_val {
  /*
    n - number
    e - error
  */
  char kind;
  char *err;
  double val;
};

#endif

