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


STACK_NAME(DATA_TYPE) CREATE_STACK(DATA_TYPE)(size_t capacity) {
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
PUSH_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack,DATA_TYPE value) {
#ifdef SAFE_STACK
	if(stack->top==capacity)
		return 1;
#endif //SAFE_STACK
	stack->data[++stack->back]=value;
#ifdef SAFE_STACK
	return 0;
#endif //SAFE_STACK
}

DATA_TYPE GET_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
	return stack->data[stack->back];
}

void POP_TOP(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
	--stack->back;
}

void FREE_STACK(DATA_TYPE)(STACK_NAME(DATA_TYPE)* stack) {
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
