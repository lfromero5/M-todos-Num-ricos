#include <iostream>
#include <iomanip>
#include <cstdio>
#include "math.h"

using namespace std;

double nu1(double t)
{
    return t + 1;
}

double nu2(double t)
{
    return t;
}

double u0(double x)
{
    return (x - 1)*(x - 1);
}

double fun(double x, double t)
{
    return 0;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, K;
    double h, tau, T, q, a;

    cin >> N;
    cin >> K;
    cin >> T;
    cin >> a;

    double **arr = new double*[N + 1];
    for (int i = 0; i < N + 1; i++)
        arr[i] = new double[K + 1];

    double *x = new double[N + 1];
    double *t = new double[K + 1];
    double *alpha = new double[N];
    double *beta = new double[N];

    h = 0.1;
    tau = T / K;
    q = tau / (h*h);

    for (int i = 0; i <= N; i++)
    {
        x[i] = i*h;
    }

    for (int n = 0; n <= K; n++)
    {
        t[n] = n*tau;
    }

    for (int n = 0; n <= K - 1; n++)
    {
        arr[0][n + 1] = nu1(t[n + 1]);
        arr[N][n + 1] = nu2(t[n + 1]);
    }

    for (int i = 0; i <= N; i++)
    {
        arr[i][0] = u0(x[i]);
    }

    for (int n = 1; n <= K; n++)    //    Metodo de barrido (Метод прогонки)
    {
        for (int i = 1; i < N; i++)
        {
            if (i == 1)
            {
                alpha[1] = -(q*a) / (-1 - 2 * q*a);
                beta[1] = (-arr[i][n - 1] - tau*fun(x[i], t[n])) / (-1 - 2 * a*q);
            }
            else
            {
                alpha[i] = -(q*a) / (-1 - 2 * q*a + q*a*alpha[i - 1]);
                beta[i] = (-arr[i][n - 1] - tau*fun(x[i], t[n]) - q*a*beta[i - 1]) / (-1 - 2 * a*q + q*a*alpha[i - 1]);
            }
        }
        arr[N - 1][n] = beta[N - 1];

        for (int i = N - 2; i > 0; i--)
            {
                arr[i][n] = alpha[i] * arr[i + 1][n] + beta[i];
        }
    }

    cout << " ";                          //   Conclusion (Вывод)
    for (int i = 0; i <= N; i++)
    {
        cout << " " << x[i];
    }

    cout << endl;

    for (int n = 0; n <= K; n++)
    {
        cout << t[n];
        for (int i = 0; i <= N; i++)
        {
            cout << " " << arr[i][n];
        }
        cout << endl;
    }

    return 0;
}
