/*
Copyright(C) 2018 Edward Xie

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
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
