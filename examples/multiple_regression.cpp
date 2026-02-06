/**
 * @file multiple_regression.cpp
 * @brief Multiple linear regression example using the HomemadeScikit library
 */

#include <vector>
#include <iostream>
#include "HomemadeScikit/dataset.h"
#include "HomemadeScikit/model.h"

using namespace std;

int main()
{
    try
    {
        // Load dataset from CSV file
        dataset mydata("data/data.csv");

        // Choose features and target
        // Can use string (column name) or int (column index)
        mydata.chooseX({0, 2, "row c", 5, "row j"}).chooseY("goal");
        mydata.chooseY(2); // Change target to index 2

        // Create and initialize model
        model m(mydata);

        cout << "Initial cost: " << m.getJ() << endl;

        // Train the model
        m.train({.algo = "gradient", .epochs = 1000, .step = 0.001});

        // Make predictions
        vector<double> testInput = {1.0, 2.0, 4, 5};
        cout << "Prediction: " << m.predict(testInput) << endl;

        // Export model
        m.export_to_file("model.anouar");

        cout << "Model trained and exported successfully!" << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
