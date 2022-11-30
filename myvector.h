#ifndef myvector_h
#define myvector_h
template <typename T>
class MyVector
{
public:
	T* myvector;
	int vector_size;
	MyVector();
	MyVector(int);
	virtual ~MyVector();
	void PushBack(T);
	void Delete(int);
	void ChangeSize(int);


};
#endif