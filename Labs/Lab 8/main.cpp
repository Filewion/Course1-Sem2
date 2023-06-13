#include<iostream>
#include<Windows.h>
#include<fstream>
using std::cout;
using std::endl;

template<typename T>
class Stack
{
private:
	T* m_data = nullptr;
	int m_size = 0; // размер
	int m_topIndex = -1; // индекс верхнего элемента
public:
	Stack(int size) 
	{
		m_size = size;
		try 
		{
			m_data = new T[size];
		}
		catch (const std::bad_alloc& ex)
		{
			cout << "Невозможно выделить необходимый участок памяти под стек" << endl;
			throw ex;
		}
	}
	int size() 
	{
		return m_topIndex + 1;
	}
	bool empty()
	{
		return m_topIndex == -1;
	}
	void push(const T& elem) // добавить элемент 
	{
		if (m_topIndex == m_size - 1)
		{
			cout << "Невозможно добавить новый элемент в стек"<<endl;
			throw std::overflow_error("Overflow error");
		}
		m_data[++m_topIndex] = elem;
	}
	T pop() // извлечь элемент - удалить и вернуть 
	{
		if (m_topIndex == -1)
		{
			cout << "Невозможно извлечь элемент из стека, так как стек пустой" << endl;
			throw std::out_of_range("Out of range");
		}
		return m_data[m_topIndex--];
	}
	T top() // показать элемент - вернуть 
	{
		if (m_topIndex == -1)
		{
			cout << "Невозможно посмотреть элемент на вершине стека, так как стек пустой" << endl;
			throw std::logic_error("Logic error");
		}
		return m_data[m_topIndex];
	}

	void getStack()
	{
		for (int i = 0; i < m_topIndex+1; i++)
		{
			cout << m_data[i] << " ";
		}
		cout << endl;
	}

	~Stack()
	{
		delete[] m_data;
	}

};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Stack<int> st(5);

	cout << "Методы empty и size:" << endl;
	cout << "Стек пустой: " << st.empty() << "\t" << "Размер стека:" << st.size() << endl;
	cout << endl;

	cout << "Методы push и pop:" << endl;

	st.push(5);
	st.push(10);
	st.push(15);
	st.push(20);

	cout << "Стэк:";
	st.getStack();
	cout << "Стек пустой: " << st.empty() << "\t" << "Размер стека:" << st.size() << endl;
	cout << endl;

	int elem;
	elem = st.pop();

	cout << "Стэк:";
	st.getStack();
	cout << "Стек пустой: " << st.empty() << "\t" << "Размер стека:" << st.size() << endl;
	cout << "Elem = " << elem<<endl;
	cout << endl;

	cout << "Метод top:" << endl;
	cout << "Верхний элемент стека:" << st.top() << endl;
	cout << endl;
	

	cout << "Исключение 1:" << endl;
	Stack<int> ex(-2);

	/*cout << "Исключение 2:" << endl;
	Stack<int> ex(2); 
	ex.push(1);
	ex.push(2);
	ex.push(3);*/

	/*cout << "Исключение 3:" << endl;
	Stack<int> ex(1);
	ex.pop();*/

	/*cout << "Исключение 4:" << endl;
	Stack<int> ex(1);
	ex.top();*/
}