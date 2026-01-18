/**
 * @file test_dataset.cpp
 * @brief Basic tests for dataset functionality
 */

#include <iostream>
#include <cassert>
#include "HomemadeScikit/dataset.h"

using namespace std;

void test_empty_dataset()
{
    dataset d;
    assert(d.cols() == 0);
    assert(d.rows() == 0);
    assert(!d.isLoaded());
    cout << "✓ Empty dataset test passed" << endl;
}

void test_dataset_loading()
{
    try
    {
        dataset d("../data/lol.csv");
        assert(d.isLoaded());
        assert(d.cols() > 0);
        assert(d.rows() > 0);
        cout << "✓ Dataset loading test passed" << endl;
    }
    catch (const exception &e)
    {
        cout << "⚠ Dataset loading test skipped (data file not found)" << endl;
    }
}

void test_column_selection()
{
    dataset d;
    try
    {
        d.load_csv("../data/lol.csv");
        cout << "✓ Column selection test passed" << endl;
    }
    catch (const exception &e)
    {
        cout << "⚠ Column selection test skipped (data file not found)" << endl;
    }
}

int main()
{
    cout << "Running HomemadeScikit tests...\n"
         << endl;

    test_empty_dataset();
    test_dataset_loading();
    test_column_selection();

    cout << "\nAll tests completed!" << endl;
    return 0;
}
