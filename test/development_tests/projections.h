#include <numbers>

#include "cppUnit.h"

#include "transformations.h"
#include "testutils.h"

SUITE("Orthographic")
{
    FIXTURE()
    {
        float height = 400;
        float width = 600;
        float near = 0.0f;
        float far = 100.0f;

        linalg::mat<4, 4, float> ortho = tl3d::orthographic(0, width, 0, height, near, far);

        FTEST("Point in center")
        {
            linalg::vec<3, float> point(300, 200, -50);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, 0.0f);
            assertEq(projected_point.y, 0.0f);
            assertEq(projected_point.z, 0.0f);
        }

        FTEST("Point in lower left corner")
        {
            linalg::vec<3, float> point(0, 0, 0);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, -1.0f);
            assertEq(projected_point.y, -1.0f);
            assertEq(projected_point.z, -1.0f);
        }

        FTEST("Point in upper right corner")
        {
            linalg::vec<3, float> point(600, 400, -100);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, 1.0f);
            assertEq(projected_point.y, 1.0f);
            assertEq(projected_point.z, 1.0f);
        }

        FTEST("Point off center")
        {
            linalg::vec<3, float> point(400.0f, 800.0f/3.0f, -200/3.0f);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, 2.0f * point.x / width - 1.0f);
            assertEq(projected_point.y, 2.0f * point.y / height - 1.0f);
            assertEq(projected_point.z, 2.0f * (-point.z - near) / (far - near) - 1.0f);
        }
    }
}

SUITE("Perspective")
{
    FIXTURE()
    {
        float height = 600;
        float width = 800;

        float fov = std::numbers::pi_v<float> / 4.0f;
        float aspect = width / height;
        float near = 0.1f;
        float far = 100.0f;

        linalg::mat<4, 4, float> pers = tl3d::perspective(fov, aspect, near, far);

        FTEST("Point in center")
        {
            linalg::vec<3, float> point(0, 0, 0);

            linalg::vec<4, float> projected_point = pers * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, 0.0f);
            assertEq(projected_point.y, 0.0f);
        }

        FTEST("Points approaching center")
        {
            const float z_start = -10;
            const float z_end = -60;

            // upper right corner
            float y = -z_start * std::tan(fov / 2.0f);
            float x = y * aspect;

            const size_t steps = 10;
            float zs[steps];
            for (size_t i = 0; i < steps; ++i)
            {
                float z = z_start + (z_end - z_start) / steps * i;

                linalg::vec<3, float> point(x, y, z);

                linalg::vec<4, float> projected_point = pers * linalg::vec<4, float>(point.x, point.y, point.z, 1);

                // the top of the rectangular cross-section of the frustum at this z
                float top = -point.z * std::tan(fov / 2.0f);
                // the right of the rectangular cross-section of the frustum at this z
                float right = top * aspect;

                float expected_y = point.y / top;
                float expected_x = point.x / right;

                assertLtEq(diffUlps(projected_point.x / projected_point.w, expected_x), 5);
                assertLtEq(diffUlps(projected_point.y / projected_point.w, expected_y), 5);

                zs[i] = projected_point.z / projected_point.w;
            }

            for (size_t i = 1; i < steps; ++i)
                assertGt(zs[i], zs[i-1]);
        }
    }
}