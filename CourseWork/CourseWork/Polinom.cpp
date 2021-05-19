#include "Polinom.h"
complex Polinom::FPol(Polinom& p, complex& x)
{
    int i;
    complex tmp = complex(0, 0);

    for (i = 0; i <= p.n; i++)
        tmp = tmp + pow(x, i) * p.mas[i];

    return tmp;
}

void Polinom::FindAllRoot(Polinom& pp, Root& r)
{
    int i, j;
    complex x1, x0;
    Polinom defp, p;

    p = pp;
    r.num = p.n;

    for (i = 0; i < r.num; i++)
    {
        defp.n = p.n - 1;

        for (j = 0; j < p.n; j++)
            defp.mas[j] = p.mas[j + 1] * complex(j + 1);

        x1 = complex(1, 1);

        do
        {
            x0 = x1;

            x1 = x0 - Polinom::FPol(p, x0) / Polinom::FPol(defp, x0);
        } while (abs(Polinom::FPol(p, x1)) > 1e-12);

        r.mas[i] = x1;

        for (j = p.n - 1; j >= 0; j--) p.mas[j] = p.mas[j] + p.mas[j + 1] * x1;
        for (j = 0; j < p.n; j++) p.mas[j] = p.mas[j + 1];
        p.n--;
    }
}
Polinom::Polinom(double** Matr, int columns) {
    n = columns;
    int k = 0;
    for (int i = columns-1; i >= 0; i--) {
        mas[k] = (-1)*Matr[0][i];
        k++;
    }
    mas[columns] = 1;
}

Polinom::Polinom(std::vector<double> p)
{
    n = p.size();
    int k = 0;
    for (int i = p.size() - 1; i >= 0; i--) {
        mas[k] = (-1) * p[i];
        k++;
    }
    mas[p.size()] = 1;
}
