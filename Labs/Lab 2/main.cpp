#include <iostream>
/*
1. Ѕазовый конструктор 

2.  онструктор копировани€(правило 3 - х) 

3. ќператор присваивани€ копированием(правило 3 - х)

4. ƒеструктор(правило 3 - х)

5. ќператоры + и +=

6. ќператор[] Ц чтение и изменение элемента

7. ќператоры <, >, ==

8. ќператоры ввода и вывода в поток

9. ћетод find Ц поиск первого вхождени€ символа в строку слева

10. ћетод length Ц длина строки

11. ћетод c_str Ц получить массив char

12. ћетод at дл€ получени€ доступа(чтение и изменение) к элементу строки с проверкой на выход за пределы строки
*/




class String
{
private:

	int m_size = 0;
	char* m_str = nullptr;

public:
	String() 
	{

	}; //дефолт конструктор (1)

	//String(const int a, int size) = delete;

	// конструктор по символу
	/*String(const char a, int size) : m_size(size), m_str(new char[m_size])
	{
		std::fill(m_str, m_str + m_size, a);
		m_str[m_size] = '\0';
	}*/

	String(const char* str) : m_size(strlen(str)), m_str(new char[m_size+1]) // конструктор по строке char
	{
		std::copy(str, str + m_size+1, m_str); // копирование 
		m_str[m_size] = '\0'; // терминальный символ
	}

	String(const String& other) : String(other.m_str) { } // конструктор копировани€ через делегирующий конструктор (2)

	String& operator=(String temp) // оператор присваивани€ копированием (3)
	{
		std::swap(m_size, temp.m_size);  // copy-and-swap idiom
		std::swap(m_str, temp.m_str);
		return *this;
	}

// ќператоры += и + (5)
	String& operator+=(const String& other) 
	{
		char* sup_str = new char[m_size + other.m_size+1]; // вспомогательна€ строка
		std::copy(m_str, m_str + m_size, sup_str); // копируем this строку во вспомогательную
		std::copy(other.m_str, other.m_str+other.m_size+1, sup_str+m_size); // копируем other строку во вспомогательную (захватыва€ терминирующий символ)


		delete[] m_str; // удал€ем изначальный m_str
		m_str = sup_str;
		sup_str = nullptr;
		m_size += other.m_size; // увеличиваем размер
		return *this;
	}
	String operator+(const String& other)
	{
		String temp = *this;
		temp += other;
		return temp;
	}

	char& operator[](int index) // оператор [] (6)
	{
		return m_str[index];
	}

// ќператоры >,<,== (7)
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


	int find(char sym) // метод find (9)
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

	int lenght() // метод lenght (10)
	{
		return m_size;
	}

	char* c_str() // метод c_str (11)
	{
		return m_str;
	}

	char& at(int index) // метод at (12)
	{
		if (0 <= index && index < m_size)
		{
			return m_str[index];
		}
	}

	~String() // деструктор (4)
	{
		if(m_str != nullptr)
			delete[] m_str;
	}


// ќператоры ввода и вывода в поток (8)
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
// инициализаци€ 
	String a = "Hello, "; // len = 7
	String b = "World!"; // len = 6
	std::cout << a << b << std::endl;
	std::cout << std::endl;

// инициализаци€ конструктором копировани€ / инициализац€ присваивани€ копированием
	String c = a;
	std::cout << "String c = a: " << c << std::endl;

	c = b;
	std::cout << "c = b: " << c << std::endl;
	std::cout << std::endl;

//ќператоры += и + 
	String d;
	d = a + b;
	std::cout <<"d = a + b: "<< d << std::endl;

	d += a;
	std::cout << "d += a: " << d << std::endl;
	std::cout << std::endl;
//ќператор []
	String e = a + b;
	e[12] = '?';
	std::cout << "e[12] = '?': " << e << std::endl;
	std::cout << std::endl;
//ќператоры >,<, ==
	std::cout << "a > b: "<<(a > b) << std::endl;
	std::cout << "a < b: " << (a < b) << std::endl;
	std::cout << "a == b: " << (a == b) << std::endl;
	std::cout << "c == b: " << (c == b) << std::endl;
	std::cout << std::endl;
//ќператор ввода/вывода в поток
	String f;
	std::cout << "In/out" << std::endl;
	std::cin >> f;
	std::cout << f << std::endl;
	
	
}