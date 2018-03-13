#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
#define buffer_size 10000
	char buffer[buffer_size];
	char* pos_b=buffer;
	memset(buffer,0,buffer_size);
	*pos_b+=10;
	while(*pos_b)
	{
		pos_b+=1;
		*pos_b+=1;
		pos_b+=1;
		*pos_b+=3;
		pos_b+=1;
		*pos_b+=7;
		pos_b+=1;
		*pos_b+=10;
		pos_b-=4;
		*pos_b-=1;
	}
	pos_b+=3;
	*pos_b+=2;
	putchar(*pos_b);
	pos_b+=1;
	*pos_b+=1;
	putchar(*pos_b);
	*pos_b+=7;
	putchar(*pos_b);
	putchar(*pos_b);
	*pos_b+=3;
	putchar(*pos_b);
	pos_b-=2;
	*pos_b+=2;
	putchar(*pos_b);
	pos_b+=1;
	*pos_b+=15;
	putchar(*pos_b);
	pos_b+=1;
	putchar(*pos_b);
	*pos_b+=3;
	putchar(*pos_b);
	*pos_b-=6;
	putchar(*pos_b);
	*pos_b-=8;
	putchar(*pos_b);
	pos_b-=2;
	*pos_b+=1;
	putchar(*pos_b);
	pos_b-=1;
	putchar(*pos_b);
	return 0;
}