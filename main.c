#include <stdio.h>
#include "hw1.h"

int main()
{
	char output;
	char str1[] = "This is a string.";
	char str2[] = "some NUMmbers 12345";
	char str3[] = "Does it reverse \n\0\t correctly?";
	
	//test the first string
	printf("before: %s\n", str1);
	output = reverse_string(str1, 17);
	printf("after: %s\n\n", str1);
	
	//test the second string
	printf("before: %s\n", str2);
	output = reverse_string(str2, 19);
	printf("after: %s\n\n", str2);
	

	//test the third string
	printf("before: %s\n", str3);
	output = reverse_string(str3, 30);
	printf("after: %s\n\n", str3);

	return 0;
}

