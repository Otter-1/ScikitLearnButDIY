/**
 * @file single_weight_example.cpp
 * @brief Simple linear regression example with single feature
 */

#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace std;

typedef struct grad
{
    double w;
    double b;
} grad;

// to predict is to calculate f(x) = wx + b
double predict(const double w, const double b, const double x)
{
    return w * x + b;
}

// J(w,b) = 1/2 sum((y-y')²) = 1/2 sum((wx+b-y)²)
double cost(const double w, const double b, const vector<double> &x, const vector<double> &y)
{
    int n = (int)x.size();

    if (!n)
        throw runtime_error("empty sample");
    if (n != (int)y.size())
        throw runtime_error("sample size doesn't match");

    double cost = 0;

    for (int i = 0; i < n; i++)
    {
        cost += pow(w * x[i] + b - y[i], 2);
    }
    return cost / (2 * n);
}

void logValues(const double w, const double b, const vector<double> &x, const vector<double> &y, int i)
{
    printf("_________iteration: %d_________\n", i);
    printf("w: %lf\nb: %lf\nJ: %lf\n", w, b, cost(w, b, x, y));
    printf("_______________________________\n");
}

// d J/ dw = sum (x(wx+b-y))
// d J/ db = sum (wx+b-y)
grad calculateGrad(const double w, const double b, const vector<double> &x, const vector<double> &y)
{
    int n = (int)x.size();

    if (!n)
        throw runtime_error("empty sample");
    if (n != (int)y.size())
        throw runtime_error("sample size doesn't match");

    grad grad;
    grad.b = 0;
    grad.w = 0;

    for (int i = 0; i < n; i++)
    {
        grad.b += w * x[i] + b - y[i];
        grad.w += x[i] * (w * x[i] + b - y[i]);
    }

    grad.b /= n;
    grad.w /= n;

    return grad;
}

// gradient descent:
// w = w - a * dJ/dw
// b = b - a * dJ/db

void gradientIter(const double a, double &w, double &b, const vector<double> &x, const vector<double> &y)
{
    grad grad = calculateGrad(w, b, x, y);

    w = w - a * grad.w;
    b = b - a * grad.b;
}

void gradientDescent(const int n, const double a, double &w, double &b, const vector<double> &x, const vector<double> &y)
{
    for (int i = 0; i < n; i++)
    {
        gradientIter(a, w, b, x, y);
        if (i % 100 == 0)
            logValues(w, b, x, y, i);
    }
}

int normalizeFeature(vector<double> &x, int f)
{
    for (double &i : x)
    {
        i /= f;
    }
    return f;
}

int main()
{
    vector<double> x, y;
    for (int i = 0; i < 1000; i++)
    {
        x.push_back(i * 3 - 2);
        y.push_back(i * 10 - 5);
    }

    int f = 1000;
    int n;
    double a, w, b;
    cout << "how many iterations? ";
    cin >> n;

    cout << "learning rate? ";
    cin >> a;

    cout << "initial w? ";
    cin >> w;

    cout << "initial b? ";
    cin >> b;

    normalizeFeature(x, f);
    normalizeFeature(y, f);

    gradientDescent(n, a, w, b, x, y);

    double x1;
    cout << "Model ready moving to prediction!\n";
    cout << "Enter x: ";
    cin >> x1;
    cout << "f(x)= " << predict(w, b, x1 / f) * f << endl;

    return 0;
}
