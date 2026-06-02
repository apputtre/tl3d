#include <iostream>

#include "development_tests/translation.h"
#include "development_tests/scale.h"

int main()
{
    std::cout << "Running tests..." << std::endl;

    std::string summary = cppUnit::getSummary();

    if (summary == "")
        std::cout << "All tests passed" << std::endl;
    else
        std::cout << summary << std::endl;

    return 0;
}