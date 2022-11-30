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
	void Assignment(MyString);
};

void ReverseMyString(MyString);
