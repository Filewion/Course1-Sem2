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
	int m_size = 0; // ������
	int m_topIndex = -1; // ������ �������� ��������
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
			cout << "���������� �������� ����������� ������� ������ ��� ����" << endl;
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
	void push(const T& elem) // �������� ������� 
	{
		if (m_topIndex == m_size - 1)
		{
			cout << "���������� �������� ����� ������� � ����"<<endl;
			throw std::overflow_error("Overflow error");
		}
		m_data[++m_topIndex] = elem;
	}
	T pop() // ������� ������� - ������� � ������� 
	{
		if (m_topIndex == -1)
		{
			cout << "���������� ������� ������� �� �����, ��� ��� ���� ������" << endl;
			throw std::out_of_range("Out of range");
		}
		return m_data[m_topIndex--];
	}
	T top() // �������� ������� - ������� 
	{
		if (m_topIndex == -1)
		{
			cout << "���������� ���������� ������� �� ������� �����, ��� ��� ���� ������" << endl;
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

	cout << "������ empty � size:" << endl;
	cout << "���� ������: " << st.empty() << "\t" << "������ �����:" << st.size() << endl;
	cout << endl;

	cout << "������ push � pop:" << endl;

	st.push(5);
	st.push(10);
	st.push(15);
	st.push(20);

	cout << "����:";
	st.getStack();
	cout << "���� ������: " << st.empty() << "\t" << "������ �����:" << st.size() << endl;
	cout << endl;

	int elem;
	elem = st.pop();

	cout << "����:";
	st.getStack();
	cout << "���� ������: " << st.empty() << "\t" << "������ �����:" << st.size() << endl;
	cout << "Elem = " << elem<<endl;
	cout << endl;

	cout << "����� top:" << endl;
	cout << "������� ������� �����:" << st.top() << endl;
	cout << endl;
	

	cout << "���������� 1:" << endl;
	Stack<int> ex(-2);

	/*cout << "���������� 2:" << endl;
	Stack<int> ex(2); 
	ex.push(1);
	ex.push(2);
	ex.push(3);*/

	/*cout << "���������� 3:" << endl;
	Stack<int> ex(1);
	ex.pop();*/

	/*cout << "���������� 4:" << endl;
	Stack<int> ex(1);
	ex.top();*/
}