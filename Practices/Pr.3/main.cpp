#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using std::cin;
using std::cout;
using std::endl;
using namespace sf;
//���������� ����� KinematicSolver.
//������������� ����������� ������� ���� ������� L1 � L2, ��������� ����� alpha � beta, 
//������� Solve(x, y), ������� ����� ������������ ���� �� �������� �����������.
//����������������� ���� �������.����� �� ���������� ������� �� ������, ����� ������� ������������ ��� ������ SFML.

class KinematicSolver
{
public:
	unsigned int m_L1=0, m_L2=0; // ����� ����� � ���������� 
	double hinge1_x=0, hinge1_y=0; // ���������� ������� 1
	double hinge2_x = 0, hinge2_y = 0; // ���������� ������� 2 
	double m_alpha1=0, m_beta1=0; // ���� � ������ ������
	double m_alpha2=0, m_beta2=0; // ���� �� ������ ������ 

public:
	KinematicSolver() {};
	KinematicSolver(unsigned int l1, unsigned int l2) // ����� ��������������
	{
		m_L1 = l1;
		m_L2 = l2;
	}

	void Solve(double x, double y)
	{
		int sign; // �������� �� ��������������� ���������
		if (y < 0)
			sign = -1;
		else
			sign = 1;
		double sqrL1 = pow(m_L1, 2), sqrL2 = pow(m_L2, 2); // �������� ���� ����� � ���������� 
		double B = sqrt(pow(x, 2) + pow(y, 2)); // ����� �������, ������������ ������ �/� � ������ M(x, y)
		double sqrB = pow(x, 2) + pow(y, 2); // ������� ����� 


		double O1, O2, O3; // ��������������� ���� 
		O1 = acos(x / B); 
		O2 = acos((sqrL1 - sqrL2 + sqrB) / (2 * B * m_L1));

		m_alpha1 = sign*(O1 - O2); 
		m_alpha2 = sign * (O1 + O2);

		O3 = acos((sqrL1 + sqrL2 - sqrB) / (2 * m_L1 * m_L2));

		m_beta1 = sign * (acos(-1) - O3);
		m_beta2 = -m_beta1;

		hinge1_x = m_L1 * cos(m_alpha1);
		hinge1_y = m_L1 * sin(m_alpha1);

		hinge2_x = m_L1 * cos(m_alpha2);
		hinge2_y = m_L1 * sin(m_alpha2);

	}
	void SetLengths(unsigned int l1, unsigned int l2)
	{
		m_L1 = l1;
		m_L2 = l2;
	}
};



int main()
{

	cout << "Enter lenghts of lines:" << endl;
	unsigned int l1, l2;
	cin >> l1 >> l2;
	KinematicSolver solv(l1,l2);

	cout << "Enter coordinates:" << endl;
	double x, y;
	cin >> x >> y;
	solv.Solve(x,y);
	cout << solv.m_alpha1 << "   " << solv.m_beta1 << endl;
	cout << solv.m_alpha2 << "   " << solv.m_beta2<< endl;



	RenderWindow window(VideoMode(1000.f, 1000.f), "Inversed kinematic");
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	


	//����� ��� � ������ ����:
	RectangleShape Ox(Vector2f(1000.f, 1.f));
	RectangleShape Oy(Vector2f(1.f, 1000.f));
	Ox.setFillColor(Color::White);
	Oy.setFillColor(Color::White);
	Ox.setPosition(0.f, 500.f);
	Oy.setPosition(500.f, 0.f);
	Ox.setPosition(0.f, 500.f);
	Oy.setPosition(500.f, 0.f);
	
	//����� "�����" � "����������" � �������� �� ��, ��� ������� ��������� - 50 ��������.
	//������ ���� �����-����������
	RectangleShape arm1_1(Vector2f(static_cast<float>(50 * solv.m_L1 ), 5.f));
	RectangleShape arm1_2(Vector2f(static_cast<float>(50 * solv.m_L2), 5.f));
	arm1_1.setFillColor(Color::Red);
	arm1_2.setFillColor(Color::Red);

	//������ ���� �����-���������� 
	RectangleShape arm2_1(Vector2f(static_cast<float>(50 * solv.m_L1), 5.f));
	RectangleShape arm2_2(Vector2f(static_cast<float>(50 * solv.m_L2), 5.f));
	arm2_1.setFillColor(Color::Green);
	arm2_2.setFillColor(Color::Green);

	//����� ������� �� ������, ������� �� ������ ����
	arm1_1.setPosition(500.f, 500.f); // � ����� �/�
	arm1_1.rotate(static_cast<float>(-1 * solv.m_alpha1 * 180 / acos(-1))); // ������� �� ���� m_alpha1

	//!!! ��������� �� -1 � ������ �������� ����� ��� ����, ����� ����������� �� ������� ������� ���� �������������(���� ������ ��� � ��� � �/� � ����������, � � ���� ��������)
	//!!! ����� .rotate ��������� �� �������, � �������, ������� �������� �������� ������ ��� 

	arm1_2.setPosition(static_cast<float>(500 + 50*solv.hinge1_x), static_cast<float>(500 - 50*solv.hinge1_y)); // � ����� "�����" 
	arm1_2.rotate(static_cast<float>((-1 * solv.m_beta1 * 180 / acos(-1)) + (-1 * solv.m_alpha1 * 180 / acos(-1)))); // ������� �� ���� m_beta1(���-�� �����)(�� �� m_alpha1+m_beta1 ���-�� ��� �x)

	// �� �� �����, �� �� ������ ����� 
	arm2_1.setPosition(500.f, 500.f); // � ����� �/�
	arm2_1.rotate(static_cast<float>(-1 * solv.m_alpha2 * 180 / acos(-1))); // ������� �� ���� m_alpha2 

	arm2_2.setPosition(static_cast<float>(500 + 50 * solv.hinge2_x), static_cast<float>(500 - 50 * solv.hinge2_y)); // � ����� "�����" 
	arm2_2.rotate(static_cast<float>( ( - 1 * solv.m_beta2 * 180 / acos(-1)) + (-1 * solv.m_alpha2 * 180 / acos(-1)))); // ������� �� ���� m_beta2(���-�� �����)
	

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(arm1_1);
		window.draw(arm1_2);
		window.draw(arm2_1);
		window.draw(arm2_2);
		window.draw(Ox);
		window.draw(Oy);
		window.display();

	}
	
}
