#include <iostream>
/*
1. ������� ����������� 

2. ����������� �����������(������� 3 - �) 

3. �������� ������������ ������������(������� 3 - �)

4. ����������(������� 3 - �)

5. ��������� + � +=

6. ��������[] � ������ � ��������� ��������

7. ��������� <, >, ==

8. ��������� ����� � ������ � �����

9. ����� find � ����� ������� ��������� ������� � ������ �����

10. ����� length � ����� ������

11. ����� c_str � �������� ������ char

12. ����� at ��� ��������� �������(������ � ���������) � �������� ������ � ��������� �� ����� �� ������� ������
*/




class String
{
private:

	int m_size = 0;
	char* m_str = nullptr;

public:
	String() 
	{

	}; //������ ����������� (1)

	//String(const int a, int size) = delete;

	// ����������� �� �������
	/*String(const char a, int size) : m_size(size), m_str(new char[m_size])
	{
		std::fill(m_str, m_str + m_size, a);
		m_str[m_size] = '\0';
	}*/

	String(const char* str) : m_size(strlen(str)), m_str(new char[m_size+1]) // ����������� �� ������ char
	{
		std::copy(str, str + m_size+1, m_str); // ����������� 
		m_str[m_size] = '\0'; // ������������ ������
	}

	String(const String& other) : String(other.m_str) { } // ����������� ����������� ����� ������������ ����������� (2)

	String& operator=(String temp) // �������� ������������ ������������ (3)
	{
		std::swap(m_size, temp.m_size);  // copy-and-swap idiom
		std::swap(m_str, temp.m_str);
		return *this;
	}

// ��������� += � + (5)
	String& operator+=(const String& other) 
	{
		char* sup_str = new char[m_size + other.m_size+1]; // ��������������� ������
		std::copy(m_str, m_str + m_size, sup_str); // �������� this ������ �� ���������������
		std::copy(other.m_str, other.m_str+other.m_size+1, sup_str+m_size); // �������� other ������ �� ��������������� (���������� ������������� ������)


		delete[] m_str; // ������� ����������� m_str
		m_str = sup_str;
		sup_str = nullptr;
		m_size += other.m_size; // ����������� ������
		return *this;
	}
	String operator+(const String& other)
	{
		String temp = *this;
		temp += other;
		return temp;
	}

	char& operator[](int index) // �������� [] (6)
	{
		return m_str[index];
	}

// ��������� >,<,== (7)
	bool operator>(const String& other) 
	{
		return m_size > other.m_size;
	}

	bool operator<(const String& other) 
	{
		return m_size< other.m_size;
	}

	bool operator==(const String& other)
	{
		if (m_size != other.m_size)
		{
			return false;
		}
		for (int i = 0; i < m_size; ++i)
		{
			if (m_str[i] != other.m_str[i])
			{
				return false;
			}
		}
		return true;
	}


	int find(char sym) // ����� find (9)
	{
		for (int i = 0; i < m_size; ++i)
		{
			if (m_str[i] == sym)
			{
				return i;
			}
			else
				return -1;
		}
	}

	int lenght() // ����� lenght (10)
	{
		return m_size;
	}

	char* c_str() // ����� c_str (11)
	{
		return m_str;
	}

	char& at(int index) // ����� at (12)
	{
		if (0 <= index && index < m_size)
		{
			return m_str[index];
		}
	}

	~String() // ���������� (4)
	{
		if(m_str != nullptr)
			delete[] m_str;
	}


// ��������� ����� � ������ � ����� (8)
	friend std::ostream& operator <<(std::ostream& out, String& str1);
	friend std::istream& operator >>(std::istream& in, String& str1); /// ???
};

std::ostream& operator <<(std::ostream& out, String& str) // (8)
{
	out << str.m_str;
	return out;
}

std::istream& operator >>(std::istream& in, String& str)
{
	char buf[1000];
	in >> buf;
	str = String(buf);
	return in;
}


int main()
{
// ������������� 
	String a = "Hello, "; // len = 7
	String b = "World!"; // len = 6
	std::cout << a << b << std::endl;
	std::cout << std::endl;

// ������������� ������������� ����������� / ������������ ������������ ������������
	String c = a;
	std::cout << "String c = a: " << c << std::endl;

	c = b;
	std::cout << "c = b: " << c << std::endl;
	std::cout << std::endl;

//��������� += � + 
	String d;
	d = a + b;
	std::cout <<"d = a + b: "<< d << std::endl;

	d += a;
	std::cout << "d += a: " << d << std::endl;
	std::cout << std::endl;
//�������� []
	String e = a + b;
	e[12] = '?';
	std::cout << "e[12] = '?': " << e << std::endl;
	std::cout << std::endl;
//��������� >,<, ==
	std::cout << "a > b: "<<(a > b) << std::endl;
	std::cout << "a < b: " << (a < b) << std::endl;
	std::cout << "a == b: " << (a == b) << std::endl;
	std::cout << "c == b: " << (c == b) << std::endl;
	std::cout << std::endl;
//�������� �����/������ � �����
	String f;
	std::cout << "In/out" << std::endl;
	std::cin >> f;
	std::cout << f << std::endl;
	
	
}