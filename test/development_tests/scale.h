#include "cppUnit.h"

#include "transformations.h"

SUITE("Scale")
{
    TEST("Scaling by a scalar")
    {
        linalg::mat<4, 4, float> m(1);
        float s = 2.5;

        tl3d::scale(m, s);

        assertEq(m, linalg::mat<4, 4, float> {
            {2.5, 0, 0, 0},
            {0, 2.5, 0, 0},
            {0, 0, 2.5, 0},
            {0, 0, 0, 1}
        });
    }

    TEST("Scaling by a vector")
    {
        linalg::mat<4, 4, float> m(1);
        linalg::vec<3, float> s(1, 2.5, -3);

        tl3d::scale(m, s);

        assertEq(m, linalg::mat<4, 4, float> {
            {1, 0, 0, 0},
            {0, 2.5, 0, 0},
            {0, 0, -3, 0},
            {0, 0, 0, 1}
        });
    }
}