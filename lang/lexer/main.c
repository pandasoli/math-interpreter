#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./tokens.c"

#ifndef LEXER
#define LEXER 1

struct Lexer {
  char *text;
  int counter;
  char current;

  struct Token (*lex)(struct Lexer *);

  char *(*next)(struct Lexer *);
  char *(*back)(struct Lexer *);

  struct Token (*num)(struct Lexer *, char *, const int, int *);
};

struct Token Lexer_lex(struct Lexer *lex) {
  lex->next(lex);

  if (lex->current == ' ') return lex->lex(lex);

  char buff[255] = { lex->current, '\0' };
  const int pos = lex->counter - 1;
  int len = 1;

  if (lex->current == '+' ) return newToken(PlusTk , buff, pos, len);
  if (lex->current == '-' ) return newToken(DashTk , buff, pos, len);
  if (lex->current == '*' ) return newToken(StarTk , buff, pos, len);
  if (lex->current == '/' ) return newToken(SlashTk, buff, pos, len);
  if (lex->current == '\0') return newToken(EOFTk  , buff, pos, len);

  if (strchr("0123456789", lex->current) != NULL)
    return lex->num(lex, buff, pos, &len);

  printf("Illegal character '%c'\n", lex->current);
  return newToken(ErrTk, buff, pos, len);
}

struct Token Lexer_num(struct Lexer *lex, char *buff, const int pos, int *len) {
  while (strchr("0123456789.", *lex->next(lex)) != NULL && lex->current != '\0') {
    buff[*len] = lex->current;
    buff[*len + 1] = '\0';
    (*len)++;
  }
  lex->back(lex);

  return newToken(NumTk, buff, pos, *len);
}

char *Lexer_next(struct Lexer *lex) {
  if (lex->counter == strlen(lex->text)) {
    lex->current = '\0';
  }
  else if (lex->counter > strlen(lex->text)) {
    printf("Warning: Passed text end\n");
    abort();
  }
  else
    lex->current = lex->text[lex->counter];

  lex->counter++;

  return &lex->current;
}

char *Lexer_back(struct Lexer *lex) {
  lex->counter -= 2;
  lex->next(lex);

  return &lex->current;
}

struct Lexer newLexer(const char *text) {
  struct Lexer res;

  res.text = (char*) malloc(255);
  strcpy(res.text, text);
  res.counter = 0;
  res.current = ' ';
  res.next = &Lexer_next;
  res.back = &Lexer_back;
  res.lex = &Lexer_lex;
  res.num = &Lexer_num;

  return res;
}

#endif

