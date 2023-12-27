#include<cmath>
double logarytm(int x) {
	return log(x);
}
float odchylenie(float* tab, unsigned int ilosc)
{
    float sumowanie = 0;
    for (int u = 0; u < ilosc; u++)
    {
        sumowanie += tab[u];
    }

    float dodanie = sumowanie / ilosc;
    float potega;
    float sumapoteg = 0;

    for (int r = 0; r < ilosc; r++)
    {
        potega = tab[r] - dodanie;
        potega *= potega;
        sumapoteg += potega;
    }
    float wariancja = sumapoteg / ilosc;
    float odchylenie = sqrt(wariancja);

    return odchylenie;
}
double exponent(long double x) {
    return exp(x);
}