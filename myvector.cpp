#include"conio2.h"
#include"myvector.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>


template <typename T>
MyVector<T>::MyVector():vector_size(0) {};

template <typename T>
MyVector<T>::MyVector(int _vector_size) :vector_size(_vector_size)
{
	myvector = (T*)malloc(vector_size * sizeof(T));
}
template<typename T>
MyVector<T>::~MyVector()
{
	delete(myvector);
}

template<typename T>
void MyVector<T>::PushBack(T element)
{
	vector_size++;
	myvector = (T*)realloc(myvector, vector_size * sizeof(MyVector));
	*(myvector + vector_size - 1) = element;
}



