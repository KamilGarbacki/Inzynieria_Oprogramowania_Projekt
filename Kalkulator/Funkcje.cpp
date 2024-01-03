#include "Funkcje.h"

double Kalkulator::ln(double val)
{
	if (val <= 0) return false;
	return std::log(val);
}

double Kalkulator::odchylenie_standardowe(double val[], int n)
{
	double average = 0;

	for (int i = 0; i < n; i++) {
		average += val[i];
	}

	average /= n;

	double licznik = 0;

	for (int i = 0; i < n; i++) {
		licznik += pow(val[i] - average, 2);
	}

	double wariancja = licznik / n;

	double odchylenie = sqrt(wariancja);

	return odchylenie;
}

double Kalkulator::exponent(double val)
{
	return exp(val);
}


