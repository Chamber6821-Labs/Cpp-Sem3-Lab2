#include "brainhack.h"

Parallelepiped inputParallelepiped() {
  Vector3d a1, b1, c1, a2;
  std::cout << "Enter parallelepiped point a1: ";
  std::cin >> a1;
  std::cout << "Enter parallelepiped point b1: ";
  std::cin >> b1;
  std::cout << "Enter parallelepiped point c1: ";
  std::cin >> c1;
  std::cout << "Enter parallelepiped point a2: ";
  std::cin >> a2;
  return {a1, b1, c1, a2};
}

int main() {
  Parallelepiped p1 = {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}, {0, 1, 0}};
  Parallelepiped p2 = {{1, 1, 1}, {2, 1, 1}, {1, 1, 2}, {1, 2, 1}};

  std::cout << (parallelepipedIntersectParallelepiped(p1, p2)
                  ? "intersect"
                  : "do not intersect")
            << '\n';
}