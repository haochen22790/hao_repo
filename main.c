#include <stdio.h>

//prototypes
char reverse_string(char* str, int length);
char find_length(char* str);

int main()
{
	char output;
	char str[] = "hello world";
	
	//call function to reverse string, input length will be verified
	output = reverse_string(str, 11);

	//print the new string in memory
	printf("%s\n", str);

	return 0;
}

//function that reverses the array elements in memory
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
	
	//if verification succeeds, the result should be 0
	printf("Return code = %d\n", compare);
	
	//if verification fails, return the code, and exit
	if (compare != 0)
	{
		return compare;
	}
	
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
