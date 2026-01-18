#ifndef HOMEMADESCIKIT_DATA_SETTINGS_H
#define HOMEMADESCIKIT_DATA_SETTINGS_H

#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Configuration of which columns are features and which is the target
 *
 * - `y` is the index of the target (dependent variable)
 * - `x` is a vector of feature indices (independent variables)
 */
class data_settings
{
public:
    int y;
    vector<int> x;

    /** @brief Get the index of the target column */
    int getY() { return y; }

    /** @brief Get the feature indices */
    const vector<int> &getX() { return x; }

    /** @brief Print the feature indices to stdout (debug helper) */
    void readX()
    {
        cout << "X : ";
        for (const int i : x)
        {
            cout << i << ", ";
        }
        cout << endl;
    }
};

#endif // HOMEMADESCIKIT_DATA_SETTINGS_H
