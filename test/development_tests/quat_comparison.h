#include "cppUnit.h"

#include "transformations.h"

SUITE("Quaternion comparison")
{
    TEST("Equal quaternions")
    {
        tl3d::quat<float> q1(1, 2, 3, 4);
        tl3d::quat<float> q2(1, 2, 3, 4);

        assertEq(q1, q2, "Equal quaternions considered unequal!");
    }

    TEST("Unequal quaternions")
    {
        tl3d::quat<float> q1(1, 2, 3, 4);
        tl3d::quat<float> q2(4, 3, 2, 1);

        assertNeq(q1, q2, "Unequal quaternions considered equal!");
    }
}