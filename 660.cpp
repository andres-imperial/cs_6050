#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x;
  int y;
};

int main(void) {
  int numPoints = 0;
  cin >> numPoints;

  if (numPoints < 4) {
    printf("0\n");
    return 0;
  }

  vector<Point> points(numPoints);
  int userX;
  int userY;
  for (int i = 0; i < numPoints; ++i) {
    cin >> userX;
    cin >> userY;
    points[i] = {userX, userY};
  }

  vector<Point> pointVectors;
  for (int i = 0; i < numPoints; ++i) {
    for (int j = i + 1; j < numPoints; ++j) {
      pointVectors.push_back(
          {points[i].x + points[j].x, points[i].y + points[j].y});
    }
  }

  sort(pointVectors.begin(), pointVectors.end(), [](Point left, Point right) {
    if (left.x < right.x)
      return true;
    else if (left.x > right.x)
      return false;
    else
      return left.y < right.y;
  });

  int total = 0;
  int index1 = 0, index2 = 0;
  int numVectors = numPoints * (numPoints - 1) / 2;
  while (index2 <= numVectors) {
    if (index2 == numVectors) {
      int k = index2 - index1;
      total += (unsigned long long)k * (k - 1) / 2;
      ++index2;
    } else if (pointVectors[index1].x == pointVectors[index2].x &&
               pointVectors[index1].y == pointVectors[index2].y) {
      ++index2;
    } else {
      int k = index2 - index1;
      total += (unsigned long long)k * (k - 1) / 2;
      index1 = index2;
    }
  }

  printf("%i\n", total);

  return 0;
}
