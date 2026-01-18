#ifndef HOMEMADESCIKIT_DATASET_H
#define HOMEMADESCIKIT_DATASET_H

#include <vector>
#include <variant>
#include <string>
#include "column.h"
#include "data_settings.h"

using namespace std;

/**
 * @brief A very small CSV dataset container.
 *
 * The dataset stores data in a column-oriented fashion using `column`.
 * It supports loading numerical CSV files (missing entries are allowed),
 * selecting features and target columns, and printing or retrieving rows.
 */
class dataset
{
private:
    bool loaded;

    /**
     * @brief Parse a header line and initialize columns
     * @param line The CSV header line
     * @return number of headers/columns found
     */
    int loadHeaders(string);

    /**
     * @brief Parse a CSV data line and append values to columns
     * @param line The CSV data line
     * @param n Number of columns (used to validate/align fields)
     * @return 0 on success, non-zero on parse error
     */
    int loadLine(string, int);

public:
    vector<column> data;
    data_settings settings;

    /** @brief Construct an empty dataset */
    dataset();

    /** @brief Construct a dataset and load from file */
    dataset(string);

    /** @brief Load a CSV file into this dataset */
    void load_csv(string);

    /** @brief Whether the dataset has been successfully loaded */
    bool isLoaded() { return loaded; }

    /** @brief Number of columns */
    int cols();

    /** @brief Number of rows */
    int rows();

    /** @brief Get a printable representation of the value at (row,col) */
    string getValue(int row, int col);

    /** @brief Print the dataset to stdout in CSV format */
    void print();

    /** @brief Get the column index given its header, or -1 if not found */
    int getIndex(string);

    /** @brief Choose feature columns by name or index */
    dataset &chooseX(const vector<variant<string, int>> &);

    /** @brief Choose the target column by name or index */
    dataset &chooseY(string);
    dataset &chooseY(int);

    /** @brief Return the feature values for a row as a vector */
    vector<double> getRow(int);
};

#endif // HOMEMADESCIKIT_DATASET_H
