#pragma once
#include "../parser/node.h"
#include "../error.h"
#include "./types.h"


#ifndef EVAL
#define EVAL

struct Eval {
  struct Parser *par;
  struct Error *err;

  struct Eval_val (*eval)(struct Eval *);

  struct Eval_val (*visit)(struct Eval *, const struct Node);
  struct Eval_val (*visit_n)(const struct Node);
  struct Eval_val (*visit_u)(struct Eval *, const struct Node);
  struct Eval_val (*visit_b)(struct Eval *, const struct Node);
};

#endif

struct Eval newEval(struct Parser *, struct Error *);

