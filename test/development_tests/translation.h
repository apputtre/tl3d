#include "cppUnit.h"

#include "linalg/include/mat.h"
#include "transformations.h"

SUITE("Translation")
{
    TEST("Test 1")
    {
        linalg::mat<4, 4, float> m(1);
        linalg::vec<3, float> t(1, -2, 3.5);

        auto result = tl3d::trans(m, t);

        assertEq(result, linalg::mat<4, 4, float> {
            {1, 0, 0, 1},
            {0, 1, 0, -2},
            {0, 0, 1, 3.5},
            {0, 0, 0, 1}
        });
    }
}