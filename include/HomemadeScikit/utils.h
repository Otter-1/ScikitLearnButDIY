#ifndef HOMEMADESCIKIT_UTILS_H
#define HOMEMADESCIKIT_UTILS_H

#include <vector>
#include <string>

using namespace std;

// Vector operations
double dot(const vector<double> &v1, const vector<double> &v2);

vector<double> operator/(const vector<double> &v, double n);
vector<double> &operator/=(vector<double> &v, double n);
vector<double> &operator-=(vector<double> &v1, const vector<double> &v2);
vector<double> operator-(const vector<double> &v1, const vector<double> &v2);
vector<double> operator*(const vector<double> &v, const double n);
vector<double> operator*(const double n, const vector<double> &v);

// String utilities
bool ends_with(string m, string s);

#endif // HOMEMADESCIKIT_UTILS_H
