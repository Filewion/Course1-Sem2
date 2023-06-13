#include <iostream>
//using std::cout;
//using std::endl;
//using std::swap;
using namespace std;
/*
���������� ��������� ����� ��� �������� ������(� ������� ������, ��������).������������� 3 ��������� ��������� : ��� ��������, ������� ������� N � M(N, M <= 3)
� ������� ������ ������ ���� :
1. ����������� �����������
2. �������� ������������ ������������
3. �������� ����� � ������
4. ��������� + , +=, *, *=
5. ��������++, ������� ����������� ��� �������� ������� �� 1
6. ����� ���������� ������������
7. ����� ��� �������� ��� ��������� � ��������� �������� ������� �� �������
*/

template<typename T, int N, int M>
class Matrix
{
public:

	T m_matrix[N][M]{ 0 };
	
	Matrix() = default; //default constructor 
	Matrix(const Matrix& matrix) = default; // default copy-constructor


	Matrix& operator+=(const Matrix& other) // �������� += (4)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				m_matrix[i][j] += other.m_matrix[i][j];
			}
		}
		return *this;
	}
	Matrix operator+(Matrix other) // �������� + (4)
	{
		other += *this;
		return other;
	}
	
	template<int S>
	Matrix<T,N,S> operator*(const Matrix<T,M,S> &other) // �������� * (4)
	{
		Matrix<T,N,S> sup_m;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < S; ++j)
			{
				for (int n = 0; n < M; ++n)
				{
					sup_m.m_matrix[i][j] += m_matrix[i][n] * other.m_matrix[n][j];
				}
			}
		}
		return sup_m;
	}

	Matrix& operator++() //�������� ++ ���������� (5)
	{
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				m_matrix[i][j]++;
			}
		}
		return *this;
	}
	Matrix operator++(int) //�������� ++ ����������� (5)
	{
		Matrix temp = *this;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				m_matrix[i][j]++;
			}
		}
		return temp;
	}

	T det() // ����� ���������� ������������(6) 
	{
		
		if (N == 1 && M==1)
			return m_matrix[0][0];
		else if (N == 2 && M == 2)
			return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
		else if (N == 3 && M == 3)
			return ((m_matrix[0][0] * m_matrix[1][1] * m_matrix[2][2]) + (m_matrix[0][1] * m_matrix[1][2] * m_matrix[2][0]) +
				(m_matrix[1][0] * m_matrix[2][1] * m_matrix[0][2]) - (m_matrix[0][2] * m_matrix[1][1] * m_matrix[2][0]) -
				(m_matrix[1][0] * m_matrix[0][1] * m_matrix[2][2]) - (m_matrix[0][0] * m_matrix[1][2] * m_matrix[2][1]));
		else exit(0);
	}

	T* operator [](int index) // ��������� � ��������(7)
	{
		return m_matrix[index];
	}

	//����-����� � ����� (3)
	template<typename T, int N, int M>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<T,N,M>& matrix);
	template<typename T, int N, int M>
	friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix);
};

template<typename T,int N, int M>
std::ostream& operator<<(std::ostream& out, const Matrix<T,N,M> &matrix)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			out << matrix.m_matrix[i][j] <<" ";
		}
		out << "\n";
	}
	return out;
}

template<typename T, int N, int M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& matrix)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			in >> matrix.m_matrix[i][j];
		}
	}
	return in;
}


using Matrix22i = Matrix<int, 2, 2>;
using Matrix33i = Matrix<int, 3, 3>;


int main()
{ 
	//����-����� ������
	Matrix<int,2,3> a1;
	Matrix<int, 3, 2> b1;
	Matrix33i a2;
	cout << "Enter 2x3 matrix" << endl;
	cin >> a1;
	cout << endl;
	cout << a1 << endl;
	cout << "Enter 3x2 matrix" << endl;
	cin >> b1;
	cout << endl;
	cout << b1 << endl;
	cout << "Enter 3x3 matrix" << endl;
	cin >> a2;
	cout << endl;
	cout << a2 << endl;;
	
	//�������������
	Matrix33i a3 = a2;
	cout << "Matrix33i a3 = a2:" <<"\n" << a2 << endl;

	//������������ 
	Matrix33i a4;
	a4 = a2;
	cout << "a4 = a2:" <<"\n" << a4 << endl;

	//�������� +=
	a3 += a2;
	cout << "a3 += a2:" << "\n" << a3 << endl;

	//�������� ++
	cout << "a3 + a2 =" << "\n" << a3 + a2 << endl;

	//�������� * (���������� �������)
	cout << "a4 * a2=" << "\n" << a4 * a2 << endl;

	//�������� * (������������ �������(NxM,MxS)
	cout << "a1*b1 = " << "\n" << a1 * b1 << endl;


	//�������� ++
	a2++;
	cout << "a2++ =" << "\n" << a2 << endl;
	++a2;
	cout << "++a2 =" << "\n" << a2 << endl;

	//���������� ������������
	cout << "det(a4) = " << " " << a4.det() << endl;

	//��������� �������� ������� �� �������
	cout << a2 << endl;
	a2[0][1] = 100;
	cout << "a2[0][1] = 100: " <<"\n"<< a2 << endl;


	



	

	
}
































