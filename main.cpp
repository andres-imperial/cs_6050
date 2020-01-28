#define _USE_MATH_DEFINES
#include "math.h"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
  long long x;
  long long y;

  Point operator-(Point pointR) {
    return Point{this->x - pointR.x, this->y - pointR.y};
  }

  bool operator==(Point pointR) {
    return (this->x == pointR.x && this->y == pointR.y);
  }
};

long long crossProduct(Point pointA, Point pointB) {
  return pointA.x * pointB.y - pointA.y * pointB.x;
}

long long dotProduct(Point pointA, Point pointB) {
  return pointA.x * pointB.x + pointA.y * pointB.y;
}

int main(void)
{
  int numPoints = 0;
  long long originX, originY;
  cin >> numPoints;
  cin >> originX;
  cin >> originY;
  Point origin{0, 0};

  vector<Point> points(numPoints);

  int userX;
  int userY;
  for (int i = 0; i < numPoints; ++i) {
    cin >> userX;
    cin >> userY;
    points[i] = Point{userX - originX, userY - originY};
    if (points[i].x < 0 && points[i].y == 0 || points[i].y < 0) {
      points[i].x = -points[i].x;
      points[i].y = -points[i].y;
    }
  }

  sort(points.begin(), points.end(), [](Point left, Point right) {
    if (crossProduct(left, right) < 0) {
      return true;
    }
    return false;
  });

  unsigned int total = 0;
  for (int i = 1; i < points.size(); ++i) {
    if (crossProduct(points[i - 1], points[i]) != 0) {
      ++total;
    }
  }
  ++total;

  printf("%u\n", total);

  return 0;
}
