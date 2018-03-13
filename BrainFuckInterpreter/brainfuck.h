#pragma once
#ifndef BRAINFUCK_H
#define BRAINFUCK_H
#include <stdlib.h>
#include <stdio.h>
void interpret(char const* instructions,size_t space);

int compile_to_c(char const* input,char const* output);

int compile_to_x86_unoptimized(char const* inst,char const* output);
int compile_to_c_unoptimized(char const* inst,char const* output);
#endif //BRAINFUCK_H
#pragma once
