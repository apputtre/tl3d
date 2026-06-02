#include <iostream>

#include "development_tests/translation.h"

int main()
{
    std::cout << "Running tests..." << std::endl;

    std::cout << cppUnit::getSummary() << std::endl;

    return 0;
}