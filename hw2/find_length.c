#include <stdio.h>
#include "hw1.h"

//find the length of a string or array
char find_length(char* str)
{
	int length = 0;
	
	while(str[length] != '\0')
	{
		length++;
	}
	
	return length;
}
