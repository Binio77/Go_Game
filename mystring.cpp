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

void MyString::Assignment(MyString s)
{
	my_string_size = s.my_string_size;
	size_bef_add = my_string_size;
	int sth = sizeof(char);
	mystring = (char*)realloc(mystring, my_string_size * sizeof(char));
	for (int i = 0; i < s.my_string_size; i++)
		*(mystring + i) = *(s.mystring + i);
}

void InttoString(MyString *s1, int num)
{
	while (num > 0)
	{
		s1->AddLetter(num % 10 + '0');
		num /= 10;
	}

	ReverseMyString(s1);
}

void ReverseMyString(MyString * s1)
{
	MyString my_string_2;
	my_string_2.Assignment(*s1);
	for (int i = 0; i < s1->my_string_size; i++)
		*(s1->mystring + i) = *(my_string_2.mystring + (my_string_2.my_string_size - 1) - i);

}

void DoubletoString(MyString * s1, double num)
{
	if (num > 0)
	{
		int num2 = (int)(num);
		double num3 = num - num2;
		InttoString(s1, num2);
		s1->AddLetter('.');
		if (num3 > 0 && num3 < 1)
			s1->AddLetter('5');
		else
		{
			s1->AddLetter('0');
		}
	}
	else
	{
		s1->AddLetter('0');
		s1->AddLetter('.');
		s1->AddLetter('0');
	}
	
	

}