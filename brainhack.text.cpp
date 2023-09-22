#include "brainhack.h"
#include "doctest/doctest.h"

TEST_SUITE("Parallelepiped") {
  TEST_CASE("Parallelepiped::Parallelepiped(...)") {
    Parallelepiped p = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}};
    CHECK_EQ(p.top.a, Vector3d{0, 0, 0});
    CHECK_EQ(p.top.b, Vector3d{1, 0, 0});
    CHECK_EQ(p.top.c, Vector3d{1, 0, 1});
    CHECK_EQ(p.top.d, Vector3d{0, 0, 1});
    CHECK_EQ(p.bottom.a, Vector3d{0, 1, 0});
    CHECK_EQ(p.bottom.b, Vector3d{1, 1, 0});
    CHECK_EQ(p.bottom.c, Vector3d{1, 1, 1});
    CHECK_EQ(p.bottom.d, Vector3d{0, 1, 1});
  }
}

TEST_SUITE("parallelepipedIntersectParallelepiped") {
  TEST_CASE("equals") {
    Parallelepiped p = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}};
    CHECK(parallelepipedIntersectParallelepiped(p, p));
  }
  TEST_CASE("with offset") {
    Parallelepiped p1 = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}};
    Parallelepiped p2 = {{1, 1, 1}, {2, 1, 1}, {2, 1, 2}, {1, 2, 1}};
    CHECK(parallelepipedIntersectParallelepiped(p1, p2));
  }
  TEST_CASE("one inside other") {
    Parallelepiped p1 = {{0, 0, 0}, {3, 0, 0}, {3, 0, 3}, {0, 3, 0}};
    Parallelepiped p2 = {{1, 1, 1}, {2, 1, 1}, {2, 1, 2}, {1, 2, 1}};
    CHECK(parallelepipedIntersectParallelepiped(p1, p2));
  }
  TEST_CASE("not intersected") {
    Parallelepiped p1 = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}};
    Parallelepiped p2 = {{3, 3, 3}, {4, 3, 3}, {4, 3, 4}, {3, 4, 3}};
    CHECK(not parallelepipedIntersectParallelepiped(p1, p2));
  }
  TEST_CASE("on top of each other") {
    Parallelepiped p1 = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 1, 0}};
    Parallelepiped p2 = {{0, 2, 0}, {1, 2, 0}, {1, 2, 1}, {0, 3, 0}};
    CHECK(not parallelepipedIntersectParallelepiped(p1, p2));
  }
}

TEST_SUITE("Parallelogram") {
  TEST_CASE("parallelogramIntersectParallelogram equal") {
    Parallelogram p = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}};
    CHECK(parallelogramIntersectParallelogram(p, p));
  }
  TEST_CASE("segmentIntersectParallelogram") {
    Parallelogram p = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}};
    CHECK(segmentIntersectParallelogram(p, {{0, 0, 0}, {1, 0, 0}}));
    CHECK(segmentIntersectParallelogram(p, {{1, 0, 0}, {1, 0, 1}}));
    CHECK(segmentIntersectParallelogram(p, {{1, 0, 1}, {0, 0, 1}}));
    CHECK(segmentIntersectParallelogram(p, {{0, 0, 1}, {0, 0, 0}}));
  }
  TEST_CASE("Parallelogram::plane()") {
    {
      Parallelogram p = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}};
      CHECK_EQ(p.plane().normal, Vector3d{0, -1, 0});
      CHECK_EQ(p.plane().point, Vector3d{0, 0, 0});
    }
    {
      Parallelogram p = {{1, 1, 0}, {1, 0, 0}, {1, 0, 1}};
      CHECK_EQ(p.plane().normal, Vector3d{-1, 0, 0});
      CHECK_EQ(p.plane().point, Vector3d{1, 1, 0});
    }
    {
      Parallelogram p = {{1, 3, 5}, {1, 1, 5}, {11, 5, 2}};
      CHECK_EQ(p.plane().normal, Vector3d{6, 0, 20});
      CHECK_EQ(p.plane().point, Vector3d{1, 3, 5});
    }
  }
  TEST_CASE("pointBelongsToParallelogram vertices") {
    Parallelogram p = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}};
    CHECK(pointBelongsToParallelogram(p, {0, 0, 0}));
    CHECK(pointBelongsToParallelogram(p, {1, 0, 0}));
    CHECK(pointBelongsToParallelogram(p, {1, 0, 1}));
    CHECK(pointBelongsToParallelogram(p, {0, 0, 1}));
  }
}

TEST_SUITE("Segment") {
  TEST_CASE("Segment::line()") {
    Segment s = {{12, 9, 43}, {2, 14, 44}};
    CHECK_EQ(s.line().direction, Vector3d{-10, 5, 1});
    CHECK_EQ(s.line().point, Vector3d{2, 14, 44});
  }
}

TEST_SUITE("lineBelongsToPlane") {
  TEST_CASE("common") {
    Parallelogram par = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}};
    Plane p = par.plane();
    CHECK(lineBelongsToPlane(p, Segment{{0, 0, 0}, {1, 0, 0}}.line()));
    CHECK(lineBelongsToPlane(p, Segment{{1, 0, 0}, {1, 0, 1}}.line()));
    CHECK(lineBelongsToPlane(p, Segment{{1, 0, 1}, {0, 0, 1}}.line()));
    CHECK(lineBelongsToPlane(p, Segment{{0, 0, 1}, {0, 0, 0}}.line()));
  }
  TEST_CASE("cos") {
    Parallelogram par = {{0, 0, 0}, {1, 0, 0}, {1, 0, 1}};
    Segment s = {{0, 0, 1}, {0, 0, 0}};

    Plane p = par.plane();
    Line l = s.line();

    auto point = l.point;
    if (point == p.point) point += l.direction;

    CHECK_EQ(cos(p.normal, l.direction), 0);
    CHECK_EQ(cos(p.normal, p.point - point), 0);
    CHECK(almost_equal(0, cos(p.normal, l.direction)));
    CHECK(almost_equal(0, cos(p.normal, p.point - point)));
  }
}

TEST_SUITE("cross") {
  TEST_CASE("common first") {
    auto a = Vector3d{3, -3, 1};
    auto b = Vector3d{4, 9, 2};
    auto e = Vector3d{-15, -2, 39};
    REQUIRE((cross(a, b) == e));
  }
}
