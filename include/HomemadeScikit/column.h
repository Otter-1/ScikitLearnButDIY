#ifndef HOMEMADESCIKIT_COLUMN_H
#define HOMEMADESCIKIT_COLUMN_H

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Represents a single column in the dataset.
 *
 * Each column stores the header name, a vector of (value, is_set) pairs
 * for numeric values (missing values are represented with is_set == false),
 * and a string `type` describing the data type (currently "double").
 */
class column
{
public:
    string header;
    vector<pair<double, bool>> data; // (value, hasbeenset) pairs
    string type;                     // for now only double
};

#endif // HOMEMADESCIKIT_COLUMN_H
