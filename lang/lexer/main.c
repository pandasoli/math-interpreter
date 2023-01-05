#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./token.h"
#include "../error.h"
#include "./main.h"


struct Token Lexer_lex(struct Lexer *lex) {
  lex->next(lex);

  if (lex->current == ' ') return lex->lex(lex);

  char buff[255] = { lex->current, '\0' };
  const int pos = lex->counter - 1;
  int len = 1;

  if (lex->current == '+' ) return newToken(PlusTk      , buff, pos, len);
  if (lex->current == '-' ) return newToken(DashTk      , buff, pos, len);
  if (lex->current == '*' ) return newToken(StarTk      , buff, pos, len);
  if (lex->current == '/' ) return newToken(SlashTk     , buff, pos, len);
  if (lex->current == '!' ) return newToken(BangTk      , buff, pos, len);
  if (lex->current == '(' ) return newToken(OpenParenTk , buff, pos, len);
  if (lex->current == ')' ) return newToken(CloseParenTk, buff, pos, len);
  if (lex->current == '\0') return newToken(EOFTk       , buff, pos, len);

  if (strchr("0123456789", lex->current) != NULL)
    return lex->num(lex, buff, pos, &len);

  strcpy(buff, "Illegal character '");
  strcat(buff, (char []) { lex->current, '\'', '\0' });
  strcpy(
    buff,
    lex->err->throw_(lex->err, buff, pos, len)
  );

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

struct Lexer newLexer(const char *text, struct Error *err) {
  struct Lexer res;

  res.text = (char*) malloc(255);
  strcpy(res.text, text);
  res.counter = 0;
  res.current = ' ';
  res.err = err;
  res.next = &Lexer_next;
  res.back = &Lexer_back;
  res.lex = &Lexer_lex;
  res.num = &Lexer_num;

  return res;
}

