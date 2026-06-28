#include <numbers>

#include "cppUnit.h"

#include "transformations.h"
#include "testutils.h"

SUITE("Orthographic")
{
    linalg::vec<4, float> project(const linalg::vec<4, float>& p, float left, float right, float bottom, float top, float near, float far)
    {
        float x = 2 / (right - left) * p.x - (right + left) / (right - left);
        float y = 2 / (top - bottom) * p.y - (top + bottom) / (top - bottom);
        float z = 2 / (far - near) * p.z - (far + near) / (far - near);
        float w = 1;

        return {x, y, z, w};
    }

    FIXTURE()
    {
        float height = 400;
        float width = 600;
        float near = -50.0f;
        float far = 50.0f;

        linalg::mat<4, 4, float> ortho = tl3d::orthographic(-width / 2, width / 2, -height / 2, height / 2, near, far);

        FTEST("Point in center")
        {
            linalg::vec<3, float> point(0, 0, (far + near) / 2);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, 0.0f);
            assertEq(projected_point.y, 0.0f);
            assertEq(projected_point.z, 0.0f);
        }

        FTEST("Point in lower left corner")
        {
            linalg::vec<3, float> point(-width / 2, -height / 2, near);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, -1.0f);
            assertEq(projected_point.y, -1.0f);
            assertEq(projected_point.z, -1.0f);
        }

        FTEST("Point in upper right corner")
        {
            linalg::vec<3, float> point(width / 2, height / 2, far);

            linalg::vec<4, float> projected_point = ortho * linalg::vec<4, float>(point.x, point.y, point.z, 1);

            assertEq(projected_point.x, 1.0f);
            assertEq(projected_point.y, 1.0f);
            assertEq(projected_point.z, 1.0f);
        }

        FTEST("Triangle")
        {
            float s = width / 3;
            float pi = std::numbers::pi_v<float>;

            // lower left
            linalg::vec<3, float> p1(-s/2, -s*std::sin(pi / 3)/2, 0);
            // lower right
            linalg::vec<3, float> p2(s/2, -s*std::sin(pi / 3)/2, 0);
            // top
            linalg::vec<3, float> p3(0, s*std::sin(pi / 3)/2, 0);

            linalg::vec<4, float> p1_p = ortho * linalg::vec<4, float>(p1, 1.0f);
            linalg::vec<4, float> p2_p = ortho * linalg::vec<4, float>(p2, 1.0f);
            linalg::vec<4, float> p3_p = ortho * linalg::vec<4, float>(p3, 1.0f);

            assertEq(p1_p, project({p1, 1}, -width/2, width/2, -height/2, height/2, near, far));
            assertEq(p2_p, project({p2, 1}, -width/2, width/2, -height/2, height/2, near, far));
            assertEq(p3_p, project({p3, 1}, -width/2, width/2, -height/2, height/2, near, far));
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