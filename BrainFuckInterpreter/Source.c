#include "stdafx.h"
#include "brainfuck.h"
//#include <stdio.h>
int main(int argc,char** argv) {
	if(argc<3)
	{
		return 1;
	}
	compile_to_c(argv[1],argv[2]);
	//printf("%d",compile_to_c("++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<++.>+++++++++++++++.>.+++.------.--------.<<+.<."));
	//getchar();
	//while(1);
	return 0;
}