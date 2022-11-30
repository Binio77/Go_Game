#include"mystring.h"
#include"conio2.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>


MyString::MyString() :my_string_size(0), size_bef_add(0), mystring(NULL) {};

MyString::MyString(int _my_string_size) :my_string_size(_my_string_size)
{
	mystring = (char*)malloc(my_string_size * sizeof(char));
}

MyString::~MyString()
{
	delete(mystring);
}

void MyString::AddElements(char* word) {
	
	int word_size = sizeof(word) / sizeof(char);
	my_string_size += word_size;
	mystring = (char*)realloc(mystring, my_string_size * sizeof(MyString));

	for (int i = 0; i < word_size; i++)
	{
		*(mystring + size_bef_add + i) = *(word + i);
	}
	size_bef_add += word_size;
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

void MyString::Assignment(MyString my_string_2)
{
	my_string_size = sizeof(my_string_2.mystring) / sizeof(char);
	size_bef_add = my_string_size;
	mystring = (char*)realloc(mystring, my_string_size * sizeof(char));
	for (int i = 0; i < my_string_size; i++)
		*(mystring + i) = *(my_string_2.mystring + i);
}


void ReverseMyString(MyString my_string)
{
	MyString my_string_2;
	my_string_2.Assignment(my_string);
	for (int i = 0; i < my_string.my_string_size; i++)
		*(my_string.mystring + i) = *(my_string_2.mystring + (my_string_2.my_string_size - 1) - i);

}

