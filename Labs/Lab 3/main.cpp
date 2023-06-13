#include<iostream>
using std::cout;
using std::cin;
using std::swap;
using std::endl;

//Реализуйте класс Complex для работы с комплексными числами.Он должен включать :
//1. Базовый конструктор
//2. Конструктор копирования
//3. Оператор присваивания копированием
//4. Деструктор
//5. Операторы += и + , *= и *
//6. Оператор ++ префиксный и постфиксный(увеличение действительной части числа на 1)
//7. Операторы ввода и вывода

class Complex
{
private:
	double m_a;
	double m_b;
public:
	Complex(double a = 0.0, double b = 0.0) : m_a(a), m_b(b) {};
	Complex(const Complex& z) = default;

	Complex& operator=(Complex z)
	{
		swap(m_a, z.m_a); //copy-and-swap idiom
		swap(m_b, z.m_b);
		return *this;
	}

	Complex& operator+=(const Complex& z)
	{
		m_a += z.m_a;                        
		m_b += z.m_b;
		return *this;
	}
	Complex operator+(Complex z)
	{
		z += *this;
		return z;
	}
	Complex& operator*=(const Complex& z)// (1+1i)(1+1i) = 1 + i + i - 1 = 2i
	{
		int a_ = (m_a * z.m_a) - (m_b * z.m_b);
		int b_ = (m_a * z.m_b) + (z.m_a * m_b);
		m_a = a_;
		m_b = b_;
		return *this;
	}
	Complex operator*(Complex z)
	{
		z *= *this;
		return z;
	}
	Complex& operator++() // pref
	{
		m_a += 1;
		return *this;
	}
	Complex operator++(int) // post
	{
		Complex temp = *this;
		this->m_a += 1;
		return temp;
	}
	friend std::ostream& operator <<(std::ostream& out, const Complex&);
	friend std::istream& operator>>(std::istream& in, Complex&);

	~Complex() = default;
};
std::ostream& operator<<(std::ostream& out, const Complex& z)
{
	out << z.m_a << "+" << z.m_b << "i" << endl;
	return out;
}
std::istream& operator>>(std::istream& in, Complex& z)
{
	in >> z.m_a >> z.m_b;
	return in;
}


int main()
{
	setlocale(LC_ALL, "rus");
	Complex z1,z2; 
	cout << "Введите z1" << endl;
	cin >> z1;
	cout << "Введите z2" << endl;
	cin >> z2;
	cout << endl;
	cout << "z1 = " << z1 << "z2 = " << z2 << endl;


	cout << "Операторы + и += :" << endl;
	Complex z3 = z1 + z2;
	cout << "z3 = z1+z2 = " << z3 << endl;
	z3 += z1;
	cout << "z3 += z1 = " << z3 << endl;

	cout << "Операторы * и *= :" << endl;
	z3 *= z1;
	cout << "z3 *= z1 = " << z3 << endl;
	z3 = z1 * z2;
	cout << "z3 = z1 * z2: "<<z3<<endl;


	cout << "Постфиксный и префиксный инкремент:" << endl;
	cout << "z1 = " << z1 << endl;
	++z1;
	cout << "++z1 = " << z1 << endl;
	z1++;
	cout << "z1++ = " << z1 << endl;


}
	
