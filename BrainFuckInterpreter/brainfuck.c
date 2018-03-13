#include "stdafx.h"
#include "brainfuck.h"
#define DATA_TYPE size_t
#include "stack.h"
#undef DATA_TYPE
#define DATA_TYPE int
#include "cvector.h"
#include <stdio.h>
#include <stdlib.h>


#define DEFAULT_BLOCK_STACK_SIZE 100
void interpret(char const* instructions,size_t space) {
	char* buffer=(char*)malloc(space);
	for(size_t i=0;i<space;++i)
	{
		buffer[i]=0;
	}
	size_t pos_instr=0;
	size_t pos_buffer=0;
	stack_size_t block_stack=create_stack_size_t(DEFAULT_BLOCK_STACK_SIZE);
	while(instructions[pos_instr]!='\0')
	{
		switch(instructions[pos_instr])
		{
			case '>':
				++pos_buffer;
				break;
			case '<':
				--pos_buffer;
				break;
			case '+':
				++(buffer[pos_buffer]);
				break;
			case '-':
				--(buffer[pos_buffer]);
				break;
			case '.':
				putchar(buffer[pos_buffer]);
				break;
			case ',':
				buffer[pos_buffer]=getchar();
				break;
			case '[':
				if(buffer[pos_buffer]==0)
				{
					while(1)
					{
						if(instructions[++pos_instr]!=']')
						{
							break;
						}
						else if(instructions[pos_instr=='\0'])
						{
							return;
						}
					}
				}
				else
				{
					push_top_size_t(&block_stack,pos_instr);
				}
				break;
			case ']':
				if(buffer[pos_buffer]!=0)
				{
					pos_instr=get_top_size_t(&block_stack);
				}
				else
				{
					pop_top_size_t(&block_stack);
				}
				break;
		}
		++pos_instr;
	}
	//printf("%d\n",pos_instr);
	free(buffer);
	free_stack_size_t(&block_stack);
}

#define MAX_SIZE 0xFFFFFFFF
#define NONE 0
#define PLUS 1
#define MINUS 2
#define SHIFTF 3
#define SHIFTB 4
void add_to(char const* const prog,char const* const str,size_t* const progress) {
	size_t strl;
	memcpy(prog+*progress,str,strl=(strlen(str)));
	(*progress)+=strl;
}

char inline digit_to_char(unsigned int digit) {
	return '0'+digit;
}
void add_num(char const* prog,unsigned int num,size_t *progress) {
#define buff_size 25
	char buffer[buff_size];
	char* loc=buffer+buff_size;
	*(--loc)='\0';
	do
	{
		*(--loc)=digit_to_char(num%10);
	} while((num/=10)>0);
	add_to(prog,loc,progress);
#undef buff_size
}

void add_op(char const* prog,size_t op,size_t *num,size_t *progress) {
	switch(op)
	{
		case NONE: return;
		case PLUS: add_to(prog,"*pos_b+=",progress); break;
		case MINUS: add_to(prog,"*pos_b-=",progress); break;
		case SHIFTF: add_to(prog,"pos_b+=",progress); break;
		case SHIFTB: add_to(prog,"pos_b-=",progress); break;
	}
	add_num(prog,*num,progress);
	add_to(prog,";\n",progress);
	*num=0;
}

int compile_to_c(char const* inst) {
	char* prog=malloc(MAX_SIZE);
	size_t str_end=0;
	size_t back=0;
	add_to(prog,"#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\nint main(){\n#define buffer_size 10000\nchar buffer[buffer_size];\nchar* pos_b=buffer;\nmemset(buffer,0,buffer_size);\n",&str_end);
	int last_op=NONE;
	size_t op_count=0;
	while(inst[back]!='\0')
	{
		switch(inst[back])
		{
			case '+':
			{
				if(last_op!=PLUS)
				{
					add_op(prog,last_op,&op_count,&str_end);
					last_op=PLUS;
				}
				++op_count;
				break;
			}
			case '-': {
				if(last_op!=MINUS)
				{
					add_op(prog,last_op,&op_count,&str_end);
					last_op=MINUS;
				}
				++op_count;
				break;
			}
			case '>': {
				if(last_op!=SHIFTF)
				{
					add_op(prog,last_op,&op_count,&str_end);
					last_op=SHIFTF;
				}
				++op_count;
				break;
			}
			case '<': {
				if(last_op!=SHIFTB)
				{
					add_op(prog,last_op,&op_count,&str_end);
					last_op=SHIFTB;
				}
				++op_count;
				break;
			}
			default: {
				add_op(prog,last_op,&op_count,&str_end);
				last_op=NONE;
				switch(inst[back])
				{
					case '[': {
						add_to(prog,"while(*pos_b){\n",&str_end);
						break;
					}
					case ']': {
						add_to(prog,"}\n",&str_end);
						break;
					}
					case '.': {
						add_to(prog,"putchar(*pos_b);\n",&str_end);
						break;
					}
					case ',': {
						add_to(prog,"*pos_b=getchar();\n",&str_end);
						break;
					}
					default: free(prog); return 1;
				}
			}
		}
		++back;
	}
	add_to(prog,"return 0;}",&str_end);
	prog[str_end]='\0';
	FILE* file=fopen("mybrainfuck.c","w");
	if(!file)
	{
		free(prog);
		return 2;
	}
	if(fputs(prog,file)==EOF)
	{
		fclose(file);
		free(prog);
		return 3;
	}
	fclose(file);
	free(prog);
	return 0;
}

int compile_to_x86_unoptimized(char const* inst) {
	char* prog=malloc(MAX_SIZE);
	size_t back=0;
	add_to(prog,"global _main\n",13,&back);
	while(inst[back++]!='\0')
	{
	#define c (inst[back])
		switch(c)
		{
			//case '+': add_to(prog,"")
		}
	}
	return 0;
}

int compile_to_c_unoptimized(char const* inst) {
	char* prog=malloc(MAX_SIZE);
	size_t str_end=0;
	size_t back=0;
	add_to(prog,"#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\nint main(){\nsize_t buffer_size=1000;\nchar* buffer=(char*)malloc(buffer_size);\nsize_t pos_b=0;\nmemset(buffer,0,buffer_size);\n",&str_end);
	while(inst[back]!='\0')
	{
		switch(inst[back])
		{
			case '+': add_to(prog,"++buffer[pos_b];\n",&str_end); break;
			case '-': add_to(prog,"--buffer[pos_b];\n",&str_end); break;
			case '>': add_to(prog,"++pos_b;\n",&str_end); break;
			case '<': add_to(prog,"--pos_b;\n",&str_end); break;
			case '[': add_to(prog,"while(buffer[pos_b]){\n",&str_end); break;
			case ']': add_to(prog,"}\n",&str_end); break;
			case '.': add_to(prog,"putchar(buffer[pos_b]);\n",&str_end); break;
			case ',': add_to(prog,"buffer[pos_b]=getchar();\n",&str_end); break;
			default: free(prog); return 1;
		}
		++back;
	}
	add_to(prog,"return 0;}",&str_end);
	prog[str_end]='\0';
	FILE* file=fopen("mybrainfuck.c","w");
	if(!file)
	{
		free(prog);
		return 2;
	}
	if(fputs(prog,file)==EOF)
	{
		fclose(file);
		free(prog);
		return 3;
	}
	fclose(file);
	free(prog);
	return 0;
}