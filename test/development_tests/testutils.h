#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <bit>

int diffUlps(float f1, float f2)
{
    float x, y;
    if (f1 >= f2)
    {
        x = f1;
        y = f2;
    }
    else
    {
        x = f2;
        y = f1;
    }

    return std::bit_cast<unsigned long>(x) - std::bit_cast<unsigned long>(y);
}

#endif