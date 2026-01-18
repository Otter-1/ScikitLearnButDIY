/**
 * @file model.cpp
 * @brief Linear regression model implementation.
 */

#include "HomemadeScikit/model.h"
#include "HomemadeScikit/utils.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdexcept>

model::model(dataset &d) : mydata(d)
{
    b = 0;
    n = mydata.rows();
    for (int i = 0; i < mydata.settings.x.size(); i++)
    {
        w.push_back(0);
    }

    calcJ();
}

void model::calcJ()
{
    J = 0;
    for (int i = 0; i < n; i++)
    {
        J += pow(dot(mydata.getRow(i), w) + b - mydata.data[mydata.settings.getY()].data[i].first, 2);
    }
    J /= (2 * n);
}

void model::logValues(int i)
{
    calcJ();
    printf("_________iteration: %d_________\n", i);
    printf("w: ");
    for (double wi : w)
        printf("%lf ", wi);
    printf("\nb: %lf\nJ: %lf\n", b, J);
    printf("_______________________________\n");
}

grad model::calculateGrad()
{
    grad grad;
    grad.b = 0;
    double y_i;
    vector<double> row;

    for (int i = 0; i < mydata.settings.x.size(); i++)
        grad.w.push_back(0);

    for (int i = 0; i < n; i++)
    {
        row = mydata.getRow(i);
        y_i = mydata.data[mydata.settings.getY()].data[i].first;

        for (int j = 0; j < mydata.settings.x.size(); j++)
        {
            grad.w[j] += (dot(row, w) + b - y_i) * row[j];
        }
        grad.b += dot(row, w) + b - y_i;
    }

    grad.b /= n;
    grad.w /= n;

    return grad;
}

void model::gradientIter(const double a)
{
    grad gradient = calculateGrad();

    w -= a * gradient.w;
    b = b - a * gradient.b;
}

void model::gradientDescent(const int n, const double a)
{
    for (int i = 0; i < n; i++)
    {
        gradientIter(a);
        if (i % 100 == 0)
            logValues(i);
    }
    calcJ();
}

void model::train(const model_settings &m)
{
    if (m.algo == "gradient")
        gradientDescent(m.epochs, m.step);
    else
        cout << "ERROR: inexistent model type" << endl;
}

double model::predict(const vector<double> &x)
{
    if (x.size() != w.size())
        throw runtime_error("predict: input size mismatch");
    return dot(x, w) + b;
}

void model::export_to_file(string filename)
{
    string suffix = ".anouar";

    if (!ends_with(filename, suffix))
    {
        if (filename.length() == 0)
        {
            filename = "model";
        }
        filename += ".anouar";
    }

    ofstream myfile(filename);

    myfile << "I ANOUAR APPROVE THIS FILE!!" << endl;
    myfile << b << "," << endl;
    for (const double wi : w)
    {
        myfile << wi << ",";
    }

    myfile.close();
}
