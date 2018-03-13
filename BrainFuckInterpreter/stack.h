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
/*
	define DATA_TYPE to a type to use as a generic
*/
#include "nameconcat.h"
#ifdef DATA_TYPE
#include <stdlib.h>
	
#define STACK_NAME(T) NAME_CONCAT(stack_,T)
typedef struct {
#ifdef SAFE_STACK
	size_t	capacity;
#endif //SAFE_STACK
	DATA_TYPE* data;
	size_t	back;
} STACK_NAME(DATA_TYPE);

#define CREATE_STACK(T) NAME_CONCAT(create_stack_,T)
STACK_NAME(DATA_TYPE) CREATE_STACK(DATA_TYPE)(size_t capacity);

#define PUSH_TOP(T) NAME_CONCAT(push_top_,T)
#ifdef SAFE_STACK
int
#else
void
#endif
PUSH_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack,DATA_TYPE value);

#define GET_TOP(T) NAME_CONCAT(get_top_,T)
DATA_TYPE GET_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack);

#define POP_TOP(T) NAME_CONCAT(pop_top_,T)
void POP_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack);

#define FREE_STACK(T) NAME_CONCAT(free_stack_,T)
void FREE_STACK(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack);

#define IS_EMPTY(T) NAME_CONCAT(is_empty_,T)
_Bool IS_EMPTY(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack);


STACK_NAME(DATA_TYPE) inline CREATE_STACK(DATA_TYPE)(size_t capacity) {
	STACK_NAME(DATA_TYPE) toret={
	#ifdef SAFE_STACK
		.capacity=capacity,
		#endif //SAFE_STACK
			.back=0
	};
	toret.data=malloc(capacity*sizeof(DATA_TYPE));
	return toret;
}

#ifdef SAFE_STACK
int
#else
void
#endif
inline PUSH_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack,DATA_TYPE value) {
#ifdef SAFE_STACK
	if(stack->top==capacity)
		return 1;
#endif //SAFE_STACK
	stack->data[++stack->back]=value;
#ifdef SAFE_STACK
	return 0;
#endif //SAFE_STACK
}

DATA_TYPE inline GET_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
	return stack->data[stack->back];
}

void inline POP_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
	--stack->back;
}

void inline FREE_STACK(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
	free(stack->data);
}

_Bool inline IS_EMPTY(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
	return stack->back==0;
}
#undef STACK_NAME
#undef CREATE_STACK
#undef POP_TOP
#undef GET_TOP
#undef PUSH_TOP
#undef IS_EMPTY
#undef FREE_STACK
#undef DATA_TYPE
#endif //DATA_TYPE
