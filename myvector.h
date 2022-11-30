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


};
