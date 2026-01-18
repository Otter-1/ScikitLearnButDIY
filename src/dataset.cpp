/**
 * @file dataset.cpp
 * @brief CSV dataset loader and handler implementation.
 */

#include "HomemadeScikit/dataset.h"
#include "HomemadeScikit/utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

dataset::dataset()
{
    settings.y = -1;
    settings.x = {};
    loaded = false;
    data = {};
}

dataset::dataset(string s) : dataset()
{
    if (ends_with(s, ".csv"))
        load_csv(s);
    else
        throw runtime_error("Dataset initialization: File type not supported\n");
}

vector<double> dataset::getRow(int index)
{
    vector<double> result = {};
    for (const int i : settings.x)
    {
        result.push_back(data[i].data[index].first);
    }
    reverse(result.begin(), result.end());
    return result;
}

int dataset::getIndex(string x)
{
    int n = data.size();
    for (int i = 0; i < n; i++)
    {
        if (x == data[i].header)
            return i;
    }
    return -1;
}

int dataset::loadHeaders(string line)
{
    int count = 0;

    column temp;
    temp.type = "double";
    temp.data = vector<pair<double, bool>>();

    size_t start = 0;
    size_t end = line.find(',');

    while (end != string::npos)
    {
        temp.header = line.substr(start, end - start);
        data.push_back(temp);

        start = end + 1;
        end = line.find(',', start);
        count++;
    }

    if (start < line.length())
    {
        temp.header = line.substr(start);
        data.push_back(temp);
        count++;
    }

    return count;
}

int dataset::loadLine(string line, int n)
{
    pair<double, bool> temp;
    int i = 0;

    vector<pair<double, bool>> a(n, {0.0, false});

    size_t start = 0;
    size_t end = line.find(',');

    while (end != string::npos && i < n)
    {
        size_t len = end - start;
        if (len == 0)
        {
            temp.second = false;
            temp.first = 0.0;
        }
        else
        {
            string token = line.substr(start, len);
            try
            {
                temp.first = stod(token);
                temp.second = true;
            }
            catch (const std::invalid_argument &)
            {
                temp.second = false;
                temp.first = 0.0;
            }
            catch (const std::out_of_range &)
            {
                temp.second = false;
                temp.first = 0.0;
            }
        }
        a[i] = temp;
        start = end + 1;
        end = line.find(',', start);
        i++;
    }

    if (i < n)
    {
        size_t len = (start < line.length()) ? (line.length() - start) : 0;
        if (len == 0)
        {
            temp.second = false;
            temp.first = 0.0;
        }
        else
        {
            string token = line.substr(start, len);
            try
            {
                temp.first = stod(token);
                temp.second = true;
            }
            catch (const std::invalid_argument &)
            {
                temp.second = false;
                temp.first = 0.0;
            }
            catch (const std::out_of_range &)
            {
                temp.second = false;
                temp.first = 0.0;
            }
        }
        a[i] = temp;
        i++;
    }

    if (i > n)
        return -1;

    for (; i < n; i++)
    {
        a[i].second = false;
        a[i].first = 0.0;
    }

    for (int j = 0; j < n; ++j)
    {
        data[j].data.push_back(a[j]);
    }

    return 0;
}

void dataset::load_csv(string filename)
{
    ifstream iFile(filename);
    if (!iFile.is_open())
        throw runtime_error("Cannot open file: " + filename);

    string line;
    if (!getline(iFile, line))
        throw runtime_error("Empty or invalid CSV file: " + filename);

    data.clear();

    int n = loadHeaders(line);
    int linesRead = 0;

    while (getline(iFile, line))
    {
        if (loadLine(line, n) != 0)
            throw runtime_error("ERROR in line");
        linesRead++;
    }
    loaded = true;
    cout << "Brief: " << linesRead << " lines read, " << n << " Headers, " << n * linesRead << " Entries" << endl;
}

int dataset::cols()
{
    return data.size();
}

int dataset::rows()
{
    if (data.empty())
        return 0;
    return data[0].data.size();
}

string dataset::getValue(int row, int col)
{
    if (col < 0 || col >= cols() || row < 0 || row >= rows())
        return "";
    auto &p = data[col].data[row];
    if (!p.second)
        return "x";
    return to_string(p.first);
}

void dataset::print()
{
    if (!loaded)
    {
        cout << "Dataset not loaded" << endl;
        return;
    }
    for (size_t i = 0; i < data.size(); ++i)
    {
        cout << data[i].header;
        if (i + 1 < data.size())
            cout << ",";
    }
    cout << endl;
    int r = rows();
    for (int row = 0; row < r; ++row)
    {
        for (size_t col = 0; col < data.size(); ++col)
        {
            cout << getValue(row, col);
            if (col + 1 < data.size())
                cout << ",";
        }
        cout << endl;
    }
}

dataset &dataset::chooseY(int i)
{
    if (i >= data.size())
    {
        settings.y = -1;
        return *this;
    }

    vector<int>::iterator found = find(settings.x.begin(), settings.x.end(), i);

    if (found != settings.x.end())
    {
        settings.x.erase(found);
    }
    settings.y = i;
    return *this;
}

dataset &dataset::chooseY(string feature)
{
    return chooseY(getIndex(feature));
}

dataset &dataset::chooseX(const vector<variant<string, int>> &values)
{
    int i;
    for (const variant<string, int> &v : values)
    {
        if (const int *ip = get_if<int>(&v))
        {
            i = *ip;
        }
        else
        {
            i = getIndex(std::get<string>(v));
        }

        if (i == settings.y || i >= data.size() || i == -1)
        {
            continue;
        }
        settings.x.push_back(i);
    }
    return *this;
}
