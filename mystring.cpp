#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<windows.h>
#include"conio2.h"
#include<stdlib.h>
#include"mystring.h"




MyString::MyString() :string_size(0) {};

MyString::MyString(int _string_size):string_size(_string_size)
{
	mystring = (char*)malloc(string_size * sizeof(char));
}

