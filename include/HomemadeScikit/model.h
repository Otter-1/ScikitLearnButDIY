#ifndef HOMEMADESCIKIT_MODEL_H
#define HOMEMADESCIKIT_MODEL_H

#include <vector>
#include <string>
#include "dataset.h"

using namespace std;

typedef struct grad
{
    vector<double> w;
    double b;
} grad;

typedef struct model_settings
{
    string algo = "gradient";
    int epochs = 1000;
    double step = 0.001;
} model_settings;

/**
 * @brief Linear regression model using gradient descent
 */
class model
{
private:
    vector<double> w;
    double b;
    double J;
    int n;
    dataset &mydata;

    void gradientIter(const double a);
    void logValues(int i);
    grad calculateGrad();
    void gradientDescent(const int n, const double a);

public:
    /** @brief Initialize model from dataset */
    model(dataset &);

    /** @brief Predict output for given features */
    double predict(const vector<double> &);

    /** @brief Calculate cost function */
    void calcJ();

    /** @brief Get current cost */
    double getJ() { return J; }

    /** @brief Train the model */
    void train(const model_settings &);

    /** @brief Export model to file */
    void export_to_file(string);
};

#endif // HOMEMADESCIKIT_MODEL_H
