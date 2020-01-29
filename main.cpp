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
  unsigned long long numPoints = 0;
  cin >> numPoints;
  vector<Point> points(numPoints);

  int userX;
  int userY;
  for (int i = 0; i < numPoints; ++i) {
    cin >> userX;
    cin >> userY;
    points[i] = Point{userX, userY};
  }

  unsigned int total = 0;
  for (unsigned int counter = 0; counter < points.size(); ++counter) {
    auto newPoints = points;
    auto iter = newPoints.begin();
    Point origin = points[counter];
    newPoints.erase(newPoints.begin() + counter);

    for (auto &&point : newPoints) {
      point = point - origin;
      if ((point.x < 0 && point.y == 0) || point.y < 0) {
        point.x = -point.x;
        point.y = -point.y;
      }
    }

    sort(newPoints.begin(), newPoints.end(), [origin](Point left, Point right) {
      if (crossProduct(left, right) < 0) {
        return true;
      }
      return false;
    });

    unsigned int colinear = 1;
    for (int i = 1; i < newPoints.size(); ++i) {
      if (crossProduct(newPoints[i - 1], newPoints[i]) == 0) {
        ++colinear;
      } else {
        total += ((colinear) * (colinear - 1)) / 2;
        colinear = 1;
      }
    }
    total += ((colinear) * (colinear - 1)) / 2;
  }

  unsigned long long goodTriangles =
      (numPoints * (numPoints - 1) * (numPoints - 2)) / 6;
  goodTriangles -= total / 3;

  printf("%llu\n", goodTriangles);

  return 0;
}
