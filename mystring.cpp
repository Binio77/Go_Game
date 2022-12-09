#include"mystring.h"
#include"conio2.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>


MyString::MyString() :my_string_size(0), size_bef_add(0), mystring(NULL) {};

MyString::MyString(int _my_string_size) :my_string_size(_my_string_size), size_bef_add(0)
{
	mystring = (char*)malloc(my_string_size * sizeof(char));
}

MyString::~MyString()
{
	free(mystring);
}


void MyString::AddElements(char* word) 
{
	int word_lenght = strlen(word);
	my_string_size += word_lenght;
	mystring = (char*)realloc(mystring, my_string_size * sizeof(MyString));

	for (int i = 0; i < word_lenght; i++)
	{
		*(mystring + size_bef_add + i) = *(word + i);
	}
	size_bef_add += word_lenght;
}


void MyString::AddLetter(char letter)
{
	my_string_size++;
	mystring = (char*)realloc(mystring, my_string_size * sizeof(MyString));
	*(mystring + my_string_size - 1) = letter;
	size_bef_add++;

}


void MyString::Display()
{
	for (int i = 0; i < my_string_size; i++)
		putch(*(mystring + i));
}
