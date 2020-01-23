#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
  int x;
  int y;

  Point operator-(Point pointR) {
    return Point{this->x - pointR.x, this->y - pointR.y};
  }
};

int crossProduct(Point pointA, Point pointB)
{
  return pointA.x * pointB.y - pointA.y * pointB.x;
}

int dotProduct(Point pointA, Point pointB)
{
  return pointA.x * pointB.x + pointA.y * pointB.y;
}

// Distance from origin
double distance(Point point) {
  return sqrt((double)(point.x * point.x + point.y * point.y));
}

double findMinDistance(Point pointA, Point pointB, Point origin) {
  if (dotProduct(origin - pointA, pointB - pointA) > 0 &&
      dotProduct(origin - pointB, pointA - pointB) > 0) {
    // min point is on line
    int area = crossProduct(origin - pointA, pointB - pointA);
    if (area < 0) {
      area = crossProduct(pointB - pointA, origin - pointA);
    }

    double base = distance(pointB - pointA);
    double minDistance = area / base;

    return minDistance;
  }

  return min(distance(pointA), distance(pointB));
}

double areaOfCircle(double radius) { return M_PI * radius * radius; }

int main(void)
{
  int numPoints = 0;
  int originX, originY;
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
    points[i] = {userX - originX, userY - originY};
  }

  // Find farthest point
  Point farthestPoint =
      *max_element(points.begin(), points.end(), [](Point left, Point right) {
        return distance(left) < distance(right);
      });

  // Find closest point
  vector<double> minDistances;
  for (int i = 1; i <= numPoints; ++i) {
    minDistances.push_back(
        findMinDistance(points[i - 1], points[i % numPoints], origin));
  }

  double minDistance = *min_element(minDistances.begin(), minDistances.end());
  double farthestDistance = distance(farthestPoint);

  auto area = areaOfCircle(farthestDistance) - areaOfCircle(minDistance);

  printf("%.18f\n", area);

  return 0;
}
