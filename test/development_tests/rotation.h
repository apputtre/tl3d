#include "cppUnit.h"

#include <numbers>
#include "transformations.h"

linalg::mat<4, 4, float> getRotationMatrix(float angle, linalg::vec<3, float> axis)
{
    linalg::vec<3, float> u = axis.norm();

    linalg::mat<4, 4, float> result;

    result[0][0] = u.x*u.x*(1 - std::cos(angle)) + std::cos(angle);
    result[0][1] = u.x*u.y*(1 - std::cos(angle)) - u.z*std::sin(angle);
    result[0][2] = u.x*u.z*(1 - std::cos(angle)) + u.y*std::sin(angle);
    result[1][0] = u.x*u.y*(1 - std::cos(angle)) + u.z*std::sin(angle);
    result[1][1] = u.y*u.y*(1 - std::cos(angle)) + std::cos(angle);
    result[1][2] = u.y*u.z*(1 - std::cos(angle)) - u.x*std::sin(angle);
    result[2][0] = u.x*u.z*(1 - std::cos(angle)) - u.y*std::sin(angle);
    result[2][1] = u.y*u.z*(1 - std::cos(angle)) + u.x*std::sin(angle);
    result[2][2] = u.z*u.z*(1 - std::cos(angle)) + std::cos(angle);
    result[3][0] = 0;
    result[3][1] = 0;
    result[3][2] = 0;
    result[3][3] = 1;

    return result;
}

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

void assertMatEq(const linalg::mat<4, 4, float>& m1, const linalg::mat<4, 4, float>& m2, TestEnvironment& tenv)
{
    for (size_t r = 0; r < m1.num_rows; ++r)
        for (size_t c = 0; c < m1.num_cols; ++c)
            tenv.assertLtEq(diffUlps(m1[r][c], m2[r][c]), 5);
}

SUITE("Rotation - quaternion")
{
    float pi = std::numbers::pi_v<float>;

    TEST("Rotating a matrix by a quaternion, 0 rad")
    {
        linalg::mat<4, 4, float> m(1);
        tl3d::quat<float> q(0.0f, linalg::vec<3, float>(1, 0, 0));

        tl3d::rotate(m, q);

        assertMatEq(m, linalg::mat<4, 4, float> {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }, *this);
    }

    TEST("Rotating a matrix by a quaternion, pi/3 rad about x")
    {
        linalg::mat<4, 4, float> m(1);
        tl3d::quat<float> q(pi/3.0f, linalg::vec<3, float>(1, 0, 0));

        tl3d::rotate(m, q);

        assertMatEq(m, getRotationMatrix(pi/3.0f, linalg::vec<3, float>(1, 0, 0)), *this);
    }

    TEST("Rotating a matrix by a quaternion, pi/6 rad about {1, 1, 1}")
    {
        linalg::mat<4, 4, float> m(1);
        tl3d::quat<float> q(pi/6.0f, linalg::vec<3, float>(1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f)));

        tl3d::rotate(m, q);

        assertMatEq(m, getRotationMatrix(pi/6.0f, linalg::vec<3, float>(1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f))), *this);
    }
}

SUITE("Rotation - axis angle")
{
    float pi = std::numbers::pi_v<float>;

    TEST("Rotating a matrix by 0 rad about x")
    {
        linalg::mat<4, 4, float> m(1);
        tl3d::rotate(m, 0.0f, {1, 0, 0});

        assertMatEq(m, linalg::mat<4, 4, float> {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }, *this);
    }

    TEST("Rotating a matrix by pi/3 rad about x")
    {
        linalg::mat<4, 4, float> m(1);
        tl3d::rotate(m, pi/3.0f, {1, 0, 0});

        assertMatEq(m, getRotationMatrix(pi/3.0f, linalg::vec<3, float>(1, 0, 0)), *this);
    }

    TEST("Rotating a matrix by a pi/6 rad about {1, 1, 1}")
    {
        linalg::mat<4, 4, float> m(1);
        tl3d::rotate(m, pi/6.0f, {1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f)});

        assertMatEq(m, getRotationMatrix(pi/6.0f, linalg::vec<3, float>(1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f), 1.0f/sqrt(3.0f))), *this);
    }
}