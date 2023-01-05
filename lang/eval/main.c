#include <stdlib.h>
#include "../lexer/token.h"
#include "../parser/main.h"
#include "../parser/node.h"
#include "../error.h"
#include "./main.h"


struct Eval_val newEval_val(char kind, double val) {
  struct Eval_val res;

  res.kind = kind;
  res.val = val;

  return res;
}

struct Eval_val Eval_eval(struct Eval *self) {
  struct Node ast = self->par->parse(self->par);
  return self->visit(self, ast);
}

struct Eval_val Eval_visit(struct Eval *self, const struct Node node) {
  switch (node.kind) {
    case 'n': return self->visit_n(node);
    case 'u': return self->visit_u(self, node);
    case 'b': return self->visit_b(self, node);
    case 'e': {
      struct Eval_val res = newEval_val('e', 0);
      res.err = node.err;
      return res;
    }
  }
}

struct Eval_val Eval_visit_n(const struct Node node) {
  return newEval_val('n', atof(node.val.val));
}

struct Eval_val Eval_visit_u(struct Eval *self, const struct Node node) {
  struct Eval_val nume = self->visit(self, *node.right);
  if (nume.kind == 'e') return nume;
  double num = nume.val;

  switch (node.op.kind) {
    case DashTk: num = -num; break;

    case BangTk: {
      for (int i = num; i > 1; i++) {
        num *= i;
      }
    }
  }

  return newEval_val('n', num);
}

struct Eval_val Eval_visit_b(struct Eval *self, const struct Node node) {
  struct Eval_val lefte = self->visit(self, *node.left);
  if (lefte.kind == 'e') return lefte;
  double left = lefte.val;

  struct Eval_val righte = self->visit(self, *node.right);
  if (righte.kind == 'e') return righte;
  double
    right = righte.val,
    res;

  switch (node.op.kind) {
    case PlusTk : res = left + right; break;
    case DashTk : res = left - right; break;
    case StarTk : res = left * right; break;
    case SlashTk: res = left / right; break;
  }

  return newEval_val('n', res);
}


struct Eval newEval(struct Parser *par, struct Error *err) {
  struct Eval res;

  res.par = par;
  res.err = err;
  res.eval = &Eval_eval;
  res.visit = &Eval_visit;
  res.visit_n = &Eval_visit_n;
  res.visit_u = &Eval_visit_u;
  res.visit_b = &Eval_visit_b;

  return res;
}

