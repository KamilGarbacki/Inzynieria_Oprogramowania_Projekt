#include <iostream>
#include "Funkcje.h"

int main()
{
	double tab[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::cout << Kalkulator::ln(1) << std::endl;
	std::cout << Kalkulator::odchylenie_standardowe(tab, sizeof(tab) / sizeof(tab[0])) << std::endl;
	std::cout << Kalkulator::exponent(1) << std::endl;
}
