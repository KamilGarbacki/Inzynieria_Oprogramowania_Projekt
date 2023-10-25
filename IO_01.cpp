#include<iostream>

using namespace std;



int main()
{
	int AA[10];
	int size = 0;
	for (int i = 0; i < 10; i++)
	{
		cout << "podaj liczbe" << endl;
		int liczba;
		cin >> liczba;
		AA[i] = liczba;
		if (liczba < 0)
		{
			size++;
		}
	}
	
	int* BB = new int[10];
	int index = 0;
	for (int i = 0; i < 10; i++)
	{
		if (AA[i] < 0)
		{
			BB[index] = AA[i];
			index++;
		}
	}
	cout << "liczb ujemnych bylo: " << size << endl;
	cout << "oto one: " << endl;

	for (int i = 0; i < size; i++)
	{
		cout << BB[i] << endl;
	}

	return 0;
}