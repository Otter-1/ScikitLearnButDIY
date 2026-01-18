// Linear regression utilities
// Future plans:
//  - Implement diagonalization for faster computations
//  - Run it in CUDA for even faster computations

#include "HomemadeScikit/utils.h"
#include <cmath>

double dot(const vector<double> &v1, const vector<double> &v2)
{
    double product = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        product += v1[i] * v2[i];
    }
    return product;
}

vector<double> operator/(const vector<double> &v, double n)
{
    vector<double> result(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = v[i] / n;
    }
    return result;
}

vector<double> &operator/=(vector<double> &v, double n)
{
    for (int i = 0; i < v.size(); i++)
    {
        v[i] /= n;
    }
    return v;
}

vector<double> &operator-=(vector<double> &v1, const vector<double> &v2)
{
    for (int i = 0; i < v1.size(); i++)
    {
        v1[i] -= v2[i];
    }
    return v1;
}

vector<double> operator-(const vector<double> &v1, const vector<double> &v2)
{
    vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

vector<double> operator*(const vector<double> &v, const double n)
{
    vector<double> result(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result[i] = v[i] * n;
    }
    return result;
}

vector<double> operator*(const double n, const vector<double> &v)
{
    return v * n;
}

bool ends_with(string m, string s)
{
    if (m.length() <= s.length())
        return false;
    return (0 == m.compare(m.length() - s.length(), s.length(), s));
}
