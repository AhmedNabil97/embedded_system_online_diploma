/*
 ============================================================================
 Name        : ex1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//c program to find the frequency of char. in a string
int main(void) {
	char sentence [100];
	char c;
	int i;
	int freq=0;
	printf("Enter a string : ");
	fflush(stdin); fflush(stdout);
	gets(sentence);
	printf("Enter a character to find frequency :" );
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	for(i=0; i<strlen(sentence); i++)
	{
		if (sentence[i]==c)
		{
			freq+=1;
		}
	}
	printf("frequency of %c = %d",c,freq);

}


