#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;


//���������� �����, ������� ����� ���������
//���������� � ������������ ��������� �� ���������� �����.
//����� ��������� �� ����� 30 ����.������ ���������� ������������������ 
//�������� �� ������� �������.���� ���������� ����� �������� ���� ������ � �����.
//������ �������� ������������������ ���������.





class Encr
{
private:
	int m_key[30]{ 0 };
	bool m_correctKey;
	bool m_correctStr;
	string* m_str;
	int m_count;
private:
	//�������� �� ����������� ������������������ ���������
	bool fibCheck(int mas[], int count)
	{
		if (mas[0] == 1 && mas[1] == 2)
		{
			for (int i = 2; i < count; ++i)
			{
				if (!(mas[i] == mas[i - 1] + mas[i - 2]))
					return false;
			}
		}
		else return false;
		return true;
	}
	//���������� ��������������� ������� �� ����������� 
	void sort(int mas[], int count)
	{
		for (int i = 0; i < count - 1; ++i)
		{
			for (int j = 0; j < count - i - 1; ++j)
			{
				if (mas[j] > mas[j + 1])
				{
					std::swap(mas[j], mas[j + 1]);
				}
			}
		}

	}
public:
	Encr() {}
	Encr(string* str, int& count)
	{
		if (count <= 30)
		{
			m_str = str;
			m_count = count;
			m_correctStr = true;
		}
		else
		{
			cout << "Incorrect string" << std::endl;
			m_correctStr = false;
		}
	}

	void Encode() // ���������� ����������                   
	{
		if (m_correctKey && m_correctStr)
		{
			int fibonacci[30]{ 1,2 }; // ������������������ ��������� 

			for (int i = 2; i < m_count; ++i)
			{
				fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
			}

			for (int i = 0; i < m_count; ++i)
			{
				for (int j = 0; j < m_count; ++j)
				{
					if (fibonacci[j] == m_key[i] && i != j)
					{
						std::swap(fibonacci[i], fibonacci[j]);
						std::swap(m_str[i], m_str[j]);
					}
				}
			}
		}
		else
		{
			cout << "Please, enter correct key and string" << std::endl;
		}
	}
	void Decode() // ���������� ������������ 
	{
		if (m_correctKey && m_correctStr)
		{
			int tmpkey[30]{};
			for (int i = 0; i < m_count; ++i)
			{
				tmpkey[i] = m_key[i];
			}

			int fibonacci[30]{ 1,2 };

			for (int i = 2; i < m_count; ++i)
			{
				fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
			}

			for (int i = 0; i < m_count; ++i)
			{
				for (int j = 0; j < m_count; ++j)
				{
					if (fibonacci[i] == tmpkey[j] && i != j)
					{
						std::swap(tmpkey[i], tmpkey[j]);
						std::swap(m_str[i], m_str[j]);
					}
				}
			}
		}
		else
		{
			cout << "Please, enter correct key and string" << std::endl;
		}
	}


	void SetKey(const int mas[]) // ���� ����� 
	{
		int tmpkey[30]{}; // ��������������� ������, ���������� ���� 

		for (int i = 0; i < m_count; ++i)
		{
			tmpkey[i] = mas[i];
		}

		sort(tmpkey, m_count); // ���������� ��� �������� 

		if (fibCheck(tmpkey, m_count)) // �������� � ���������� 
		{
			m_correctKey = true;
			for (int i = 0; i < m_count; ++i)
			{
				m_key[i] = mas[i];
			}
		}
		else
		{
			cout << "Incorrect key" << std::endl;
			m_correctKey = false;
		}

	}

	void PrintKey() // ����� �����  
	{
		if (m_correctKey)
		{
			for (int i = 0; i < m_count; ++i)
			{
				std::cout << m_key[i] << " ";
			}
			cout << std::endl;
		}
		else
			cout << "Please, enter correct key" << std::endl;
	}


	void SetStr(string* str, int& count) // ���� ������
	{
		if (count <= 30)
		{
			m_str = str;
			m_count = count;
			m_correctStr = true;
		}
		else
		{
			cout << "Incorrect string" << std::endl;
			m_correctStr = false;
		}
	}

	void PrintStr() // ����� ������ 
	{
		if (m_correctStr)
		{
			for (int i = 0; i < m_count; ++i)
			{
				cout << m_str[i] << " ";
			}
			cout << std::endl;
		}
		else
			cout << "Please, enter correct string" << std::endl;

	}
	~Encr() {};

};
int main()
{
	std::cout << "Enter string(30 words allowed):" << std::endl;
	string str;
	std::getline(cin, str);

	string masStr[30];
	int key[30];

	int count = 1;
	for (int i = 0; i < str.length() && count < 30; ++i)
	{
		if (str[i] != ' ')
		{
			masStr[count - 1] += str[i];
		}
		else
		{
			++count;
		}
	}
	cout << "Enter key, using space:" << std::endl;
	for (int i = 0; i < count; ++i)
	{
		cin >> key[i];
	}


	Encr qwe(masStr, count);

	qwe.SetKey(key);

	qwe.Encode();

	qwe.PrintStr();

	qwe.Decode();

	qwe.PrintStr();

}