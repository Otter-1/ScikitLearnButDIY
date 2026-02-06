# HomemadeScikit

A lightweight C++ machine learning library implementing linear regression with gradient descent optimization.

## Features

- **CSV Data Loading**: Load and parse CSV files with support for missing values
- **Dataset Management**: Column-oriented data structure with flexible feature/target selection
- **Linear Regression**: Multiple linear regression using gradient descent
- **Vector Operations**: Custom vector arithmetic operators
- **Model Export**: Save trained models to disk

## Project Structure

```
HomemadeScikit/
├── include/HomemadeScikit/    # Header files (.h)
│   ├── column.h               # Column data structure
│   ├── data_settings.h        # Feature/target configuration
│   ├── dataset.h              # CSV dataset handling
│   ├── model.h                # Linear regression model
│   └── utils.h                # Utility functions
├── src/                       # Implementation files (.cpp)
│   ├── dataset.cpp
│   ├── model.cpp
│   └── utils.cpp
├── examples/                  # Example programs
│   ├── single_weight_example.cpp
│   └── multiple_regression.cpp
├── tests/                     # Unit tests
│   └── test_dataset.cpp
├── data/                      # Data files
│   └── lol.csv
├── CMakeLists.txt            # CMake build configuration
└── README.md                 # This file
```

## Building

### Prerequisites

- C++17 or later
- CMake 3.10+
- A C++ compiler (g++, clang, MSVC, etc.)

### Build Instructions

```bash
cd HomemadeScikit
mkdir build
cd build
cmake ..
cmake --build .
```

### Running Examples

```bash
# Single weight example (standalone)
./single_weight_example

# Multiple regression example
./multiple_regression
```

### Running Tests

```bash
cd build
ctest
```

## Usage Example

```cpp
#include "HomemadeScikit/dataset.h"
#include "HomemadeScikit/model.h"

int main() {
    // Load CSV file
    dataset data("data/mydata.csv");

    // Select features and target
    data.chooseX({0, 1, 2})        // Features at columns 0, 1, 2
        .chooseY("target");         // Target column by name

    // Create and train model
    model m(data);
    m.train({
        .algo = "gradient",
        .epochs = 1000,
        .step = 0.001
    });

    // Make predictions
    vector<double> input = {1.0, 2.0, 3.0};
    double prediction = m.predict(input);

    // Export trained model
    m.export_to_file("my_model");

    return 0;
}
```

## CSV Format

The library expects CSV files with:

- Headers in the first row
- Numeric values in data rows
- Missing values can be left empty or non-numeric

Example:

```
feature1,feature2,target
1.0,2.5,5.3
2.1,,6.4
3.0,3.1,7.1
```

## API Reference

### dataset

- `dataset()` - Create empty dataset
- `dataset(string filename)` - Load from CSV
- `load_csv(string filename)` - Load CSV file
- `int cols()` - Get number of columns
- `int rows()` - Get number of rows
- `dataset& chooseX(vector<variant<string, int>>)` - Select features
- `dataset& chooseY(string|int)` - Select target
- `vector<double> getRow(int index)` - Get feature row
- `void print()` - Print dataset to console

### model

- `model(dataset&)` - Initialize from dataset
- `void train(model_settings)` - Train the model
- `double predict(vector<double>)` - Make predictions
- `double getJ()` - Get current cost
- `void export_to_file(string)` - Save model

## Future Enhancements

- [ ] Implement diagonalization for faster computations
- [ ] CUDA acceleration for GPU training
- [ ] Multiple optimization algorithms (Adam, RMSprop)
- [ ] Regularization (L1, L2)
- [ ] Feature scaling utilities
- [ ] Model evaluation metrics

## License

MIT License

## Author

Anouar
