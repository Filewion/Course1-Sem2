#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

//Используя наследование и полиморфизм, напишите программу, которая работает с геометрическими фигурами :
//1.	Треугольник
//2.	Прямоугольник
//3.	Круг
//Программа должна хранить координаты и размеры фигуры, цвет, уметь вычислять площадь фигуры.

enum class Color
{
	RED,
	GREEN,
	BLUE
};

class Shape
{
private:
	double m_x, m_y; // координаты центра 
	Color m_color;
public:
	Shape(double x, double y, Color color) : m_x(x), m_y(y), m_color(color) {};

	virtual double Area() = 0; //pure virtual 

	virtual	~Shape() {};
};



class Rectangle : public Shape // прямоугольник 
{
private:
	double m_a, m_b; // стороны прямоугольника
public:
	Rectangle(double x, double y, Color color, double a, double b) : Shape(x, y, color), m_a(a), m_b(b) {};

	double Area() override
	{
		return m_a * m_b;
	}
	~Rectangle() {};
};



class Triangle : public Shape // треугольник
{
private:
	double m_a, m_b, m_c;
public:
	Triangle(double x, double y, Color color, double a, double b, double c) : Shape(x, y, color), m_a(a), m_b(b), m_c(c) {};

	double Area() override
	{
		double p = (m_a + m_b + m_c) / 2; // полупериметр 
		return sqrt(p*(p-m_a)*(p-m_b)*(p-m_c)); // формула Герона
	}
	~Triangle() {};
};
class Circle : public Shape // круг
{
private:
	double m_r; // радиус
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

	cout << "Площадь прямоугольника: " << rect->Area() << endl;
	cout << "Площадь круга: " << circ->Area() << endl;
	cout << "Площадь треугольника: " << triang->Area();

	



}