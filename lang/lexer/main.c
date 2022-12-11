#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./tokens.c"


struct Lexer {
  char *text;
  int counter;
  char current;

  struct Token (*lex)(struct Lexer *);
  char *(*next)(struct Lexer *);
};

struct Token Lexer_lex(struct Lexer *lex) {
  lex->next(lex);

  char buff[255] = { lex->current, '\0' };
  const int pos = lex->counter - 1;
  int len = 1;

  if (strchr("0123456789", lex->current) != NULL)
  {
    while (strchr("0123456789.", *lex->next(lex)) != NULL) {
      buff[len] = lex->current;
      buff[len + 1] = '\0';
      len++;
    }

    return newToken(NumTk, buff, pos, len);
  }

  printf("Illegal character '%c'\n", lex->current);
  return newToken(ErrTk, buff, pos, len);
}

char *Lexer_next(struct Lexer *lex) {
  if (lex->counter >= strlen(lex->text)) {
    lex->current = '\0';

    if (lex->counter > strlen(lex->text))
      printf("Warning: Passed text end\n");
  }
  else
    lex->current = lex->text[lex->counter];

  lex->counter++;

  return &lex->current;
}

struct Lexer newLexer(const char *text) {
  struct Lexer res;

  res.text = (char*) malloc(255);
  strcpy(res.text, text);
  res.counter = 0;
  res.current = ' ';
  res.next = &Lexer_next;
  res.lex = &Lexer_lex;

  return res;
}

