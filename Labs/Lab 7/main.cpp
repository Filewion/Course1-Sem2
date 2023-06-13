#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

//��������� ������������ � �����������, �������� ���������, ������� �������� � ��������������� �������� :
//1.	�����������
//2.	�������������
//3.	����
//��������� ������ ������� ���������� � ������� ������, ����, ����� ��������� ������� ������.

enum class Color
{
	RED,
	GREEN,
	BLUE
};

class Shape
{
private:
	double m_x, m_y; // ���������� ������ 
	Color m_color;
public:
	Shape(double x, double y, Color color) : m_x(x), m_y(y), m_color(color) {};

	virtual double Area() = 0; //pure virtual 

	virtual	~Shape() {};
};



class Rectangle : public Shape // ������������� 
{
private:
	double m_a, m_b; // ������� ��������������
public:
	Rectangle(double x, double y, Color color, double a, double b) : Shape(x, y, color), m_a(a), m_b(b) {};

	double Area() override
	{
		return m_a * m_b;
	}
	~Rectangle() {};
};



class Triangle : public Shape // �����������
{
private:
	double m_a, m_b, m_c;
public:
	Triangle(double x, double y, Color color, double a, double b, double c) : Shape(x, y, color), m_a(a), m_b(b), m_c(c) {};

	double Area() override
	{
		double p = (m_a + m_b + m_c) / 2; // ������������ 
		return sqrt(p*(p-m_a)*(p-m_b)*(p-m_c)); // ������� ������
	}
	~Triangle() {};
};
class Circle : public Shape // ����
{
private:
	double m_r; // ������
public:
	Circle(double x, double y, Color color, double r) : Shape(x, y, color), m_r(r) {};

	double Area() override
	{
		return pow(m_r, 2) * acos(-1); 
	}
	~Circle() {};
};


int main()
{
	setlocale(LC_ALL, "rus");
	Shape* rect = new Rectangle(0, 0, Color::RED, 5, 6);
	Shape* circ = new Circle(5, 3, Color::BLUE, 10);
	Shape* triang = new Triangle(4, 7, Color::RED, 3, 4, 5);

	cout << "������� ��������������: " << rect->Area() << endl;
	cout << "������� �����: " << circ->Area() << endl;
	cout << "������� ������������: " << triang->Area();

	



}