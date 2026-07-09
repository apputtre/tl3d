#include "cppUnit.h"

#include "transformations.h"

/*
Previously, quaternion noralization would not actually return the normalized quaternion.
*/
SUITE("Normalizing a quaternion")
{
    TEST("Test 1")
    {
        tl3d::quat<float> q(1, 1, 1, 1);

        tl3d::quat<float> normalized = q.norm();

        assertEq(normalized, tl3d::quat(0.5f, 0.5f, 0.5f, 0.5f));
    }
}