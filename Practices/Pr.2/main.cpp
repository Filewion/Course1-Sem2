#include <iostream>



void qwer(int* mas1, int* mas2, int N)
{
	unsigned long long* from = (unsigned long long*)(mas1);
	unsigned long long* to = (unsigned long long*)(mas2);

	for (int i = 0; i < N / sizeof(unsigned long long); ++i)
	{
		*(to) = *(from);
		++to;
		++from;
	}

	char* from2 = (char*)(from);
	char* to2 = (char*)(to);

	for (int i = 0; i < N % sizeof(unsigned long long); ++i)
	{
		*(to2) = *(from2);
		++to2;
		++from2;
	}

}



int main()
{
	const int N = 5;
	int massi[N] = { 1,2,3,4,5 };
	int massi2[N] = { 0 };

	qwer(massi, massi2, sizeof(massi));

	for (int i = 0; i < sizeof(massi2) / sizeof(int); ++i)
	{
		std::cout << massi2[i] << " ";
	}




}