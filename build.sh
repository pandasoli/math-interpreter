#!/bin/bash

mkdir build
gcc -g main.c lang/main.c lang/error.c lang/eval/main.c lang/lexer/main.c lang/lexer/token.c lang/parser/main.c lang/parser/node.c -o build/main

