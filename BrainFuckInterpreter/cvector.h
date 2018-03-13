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

#define VECTOR_NAME(T) NAME_CONCAT(vector_,T)
typedef struct {
	DATA_TYPE* data;
	size_t back;
	size_t capacity;
} VECTOR_NAME(DATA_TYPE);

#define CREATE_VECTOR(T) NAME_CONCAT(create_vector_,T)
VECTOR_NAME(DATA_TYPE) CREATE_VECTOR(DATA_TYPE)(size_t capacity);

#define PUSH_BACK(T) NAME_CONCAT(push_back_,T)
int PUSH_BACK(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* VECTOR,DATA_TYPE value);

#define BACK(T) NAME_CONCAT(back_,T)
DATA_TYPE BACK(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* vector);

#define POP_TOP(T) NAME_CONCAT(pop_top_,T)
void POP_TOP(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* vector);

#define FREE_VECTOR(T) NAME_CONCAT(free_VECTOR_,T)
void FREE_VECTOR(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* vector);

#define IS_EMPTY(T) NAME_CONCAT(is_empty_,T)
_Bool IS_EMPTY(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* vector);

#define INSERT(T) NAME_CONCAT(insert_,T)
void INSERT(DATA_TYPE) (VECTOR_NAME(DATA_TYPE)* vector,DATA_TYPE,size_t);

#define REMOVE(T) NAME_CONCAT(remove_,T)
void REMOVE(DATA_TYPE) (VECTOR_NAME(DATA_TYPE)* vector,size_t);

#define REALLOCATE(T) NAME_CONCAT(reallocate_,T)
void REALLOCATE(DATA_TYPE) (VECTOR_NAME(DATA_TYPE)* vector,size_t new_size);

#define AT(T) NAME_CONCAT(at_,T)
DATA_TYPE* AT(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* vector,size_t i);

VECTOR_NAME(DATA_TYPE) CREATE_VECTOR(DATA_TYPE)(size_t capacity) {
	VECTOR_NAME(DATA_TYPE) toret={
		.capacity=capacity,
		.back=0
	};
	toret.data=malloc(capacity*sizeof(DATA_TYPE));
	return toret;
}

int PUSH_BACK(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* vector,DATA_TYPE value) {
	if(vector->back>=vector->capacity)
	{
		REALLOCATE(DATA_TYPE)(vector,vector->capacity<<1);
	}
	vector->data[++vector->back]=value;
}

DATA_TYPE BACK(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* VECTOR) {
	return VECTOR->data[VECTOR->back];
}

void POP_TOP(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* VECTOR) {
	--VECTOR->back;
}

void FREE_VECTOR(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* VECTOR) {
	free(VECTOR->data);
}

_Bool inline IS_EMPTY(DATA_TYPE)(VECTOR_NAME(DATA_TYPE)* VECTOR) {
	return VECTOR->back==0;
}

void INSERT(DATA_TYPE) (VECTOR_NAME(DATA_TYPE)* vector,DATA_TYPE a,size_t i) {
	if(vector->back>=vector->capacity)
	{
		REALLOCATE(DATA_TYPE)(vector,vector->capacity<<1);
	}
	memcpy(vector->data+i+1,vector->data+i,vector->back-i);
	*(vector->data)=a;
}

void REMOVE(DATA_TYPE) (VECTOR_NAME(DATA_TYPE)* vector,size_t i) {
	memcpy(vector->data+i,vector->data,vector->back-i);
}

void REALLOCATE(DATA_TYPE) (VECTOR_NAME(DATA_TYPE)* vector,size_t new_size) {
	DATA_TYPE* temp=malloc(new_size*sizeof(DATA_TYPE));
	memcpy(temp,vector->data,vector->capacity);
	free(vector->data);
	vector->data=temp;
	vector->capacity=new_size;
}

DATA_TYPE* AT(T)(VECTOR_NAME(DATA_TYPE)* vector,size_t i) {
	if(i>=vector->capacity)
	{
		REALLOCATE(DATA_TYPE)(vector,i<<2);
	}
	return(vector->data+i);
}

#undef VECTOR_NAME
#undef CREATE_VECTOR
#undef POP_TOP
#undef BACK
#undef PUSH_BACK
#undef IS_EMPTY
#undef FREE_VECTOR
#undef DATA_TYPE
#undef REMOVE
#undef INSERT
#undef REALLOCATE
#undef AT
#endif //DATA_TYPE
