#ifndef mystring_h
#define mystring_h
class MyString
{
public:
	char* mystring;
	int my_string_size, size_bef_add;
	MyString();
	MyString(int);
	virtual ~MyString();
	void AddElements(char*);
	void AddLetter(char);
	void Display();
};

#endif