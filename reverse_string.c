#include <stdio.h>
#include "hw1.h"

char reverse_string(char* str, int length)
{
	char temp;
	char* start_ptr;
	char* end_ptr;
	int length_calculated;
	int compare;
	
	//calculate the input string length
	length_calculated = find_length(str);	
	
	//verify that the input length is correct
	compare = length_calculated - length;
	
	
	
	//if verification fails, return the code, and exit
	if (compare != 0)
	{
		printf("Return code = %d --> cannot reverse\n", compare);
		return compare;
	}
	
	//if verification succeeds, the result should be 0
	printf("Return code = 0 --> string will be reversed\n");

	//initialize 2 pointers, used to swap letters in the string
	start_ptr = str;
	end_ptr = str + length - 1;
	
	//swap letters in the string, until all is finished
	while(end_ptr > start_ptr)
	{
		temp = *start_ptr;
		*start_ptr = *end_ptr;
		*end_ptr = temp;
		start_ptr++;
		end_ptr--;
	}
	
	return 0;
}
