#include "pch.h"
#include "../Funkcje.cpp"

namespace Kalkulator_Tests {
	TEST(LogarithmTest, HandleZero) {
		EXPECT_FALSE(Kalkulator::ln(0));
	}

	TEST(LogarithmTest, HandleNegativeInput) {
		EXPECT_FALSE(Kalkulator::ln(0));
	}
	TEST(LogarithmTest, HandlePositiveInput) {
		EXPECT_EQ(Kalkulator::ln(1), 0);
		EXPECT_FLOAT_EQ(Kalkulator::ln(2), 0.69314718056);
	}

	TEST(OdchylenieStandardowe, HandlePositiveInput) {
		double tab[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		int n = sizeof(tab) / sizeof(tab[0]);
		EXPECT_FLOAT_EQ(Kalkulator::odchylenie_standardowe(tab, n), 2.8722813232690143299);
	}

	TEST(OdchylenieStandardowe, HandleNegativeInput) {
		double tab[10] = { -4, -5, -6, -7, -1, -2, -3, -9, -7, -1 };
		int n = sizeof(tab) / sizeof(tab[0]);
		EXPECT_FLOAT_EQ(Kalkulator::odchylenie_standardowe(tab, n), 2.6172504656604801147);
	}

	TEST(Eksponent, HandleZero) {
		EXPECT_EQ(Kalkulator::exponent(0), 1);
	}

	TEST(Eksponent, HandlePositiveInput) {
		EXPECT_FLOAT_EQ(Kalkulator::exponent(2), 7.38905609893);
	}

	TEST(Eksponent, HandleNegativeInput) {
		EXPECT_FLOAT_EQ(Kalkulator::exponent(-2), 0.13533528323);
	}
}
