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

struct Segment {
  Point start;
  Point end;

  bool sharePoint(Segment segmentR, Point &shared, Point &lVector,
                  Point &rVector) {
    if (this->end == segmentR.end) {
      shared = end;
      lVector = this->start - this->end;
      rVector = segmentR.start - segmentR.end;
      return true;
    } else if (this->end == segmentR.start) {
      shared = end;
      lVector = this->start - this->end;
      rVector = segmentR.end - segmentR.start;
      return true;
    } else if (this->start == segmentR.start) {
      shared = start;
      lVector = this->end - this->start;
      rVector = segmentR.end - segmentR.start;
      return true;
    } else if (this->start == segmentR.end) {
      shared = start;
      lVector = this->end - this->start;
      rVector = segmentR.start - segmentR.end;
      return true;
    }

    return false;
  }

  void print() {
    printf("%lli %lli %lli %lli", start.x, start.y, end.x, end.y);
  }
};

// Distance from origin
double distance(Point point) {
  return sqrt((double)point.x * point.x + (double)point.y * point.y);
}

double getRatio(Point pointA, Point pointB) {
  auto firstX = std::abs(pointB.x);
  auto firstY = std::abs(pointB.y);
  auto secondX = std::abs(pointA.x);
  auto secondY = std::abs(pointA.y);
  if (firstX * 5 < secondX || firstX * 1.25 > secondX)
    return true;
  if (firstY * 5 < secondY || firstY * 1.25 > secondY)
    return true;
  return false;
}

long long crossProduct(Point pointA, Point pointB) {
  return pointA.x * pointB.y - pointA.y * pointB.x;
}

long long dotProduct(Point pointA, Point pointB) {
  return pointA.x * pointB.x + pointA.y * pointB.y;
}

struct Rectangle {
  vector<Segment> segments;

  bool evaluate() {
    Point sharedPoint;
    Segment masterSegment = *segments.begin();
    segments.erase(segments.begin());
    Segment currentSegment = masterSegment;
    Point currentSharedPoint;
    Point legA;
    Point legB;
    for (auto iter = segments.begin(); iter != segments.end();) {
      if (currentSegment.sharePoint(*iter, currentSharedPoint, legA, legB)) {
        if (currentSharedPoint == sharedPoint) {
          return false;
        } else {
          sharedPoint = currentSharedPoint;
        }
        if (dotProduct(legA, legB) != 0) {
          return false; // they did not form a 90 degree corner
        }
        if (legA.x * legA.y != 0 || legB.x * legB.y != 0) {
          return false;
        }
        currentSegment = *iter;
        segments.erase(iter);
        iter = segments.begin();
      } else {
        ++iter;
      }
    }

    if (!segments.empty()) {
      return false;
    }

    if (currentSegment.sharePoint(masterSegment, currentSharedPoint, legA,
                                  legB)) {
      if (currentSharedPoint == sharedPoint) {
        return false;
      }
      if (dotProduct(legA, legB) != 0) {
        return false; // they did not form a 90 degree corner
      }
    } else {
      return false;
    }

    return true;
  }
};

int main(void)
{
  Rectangle myRectangle;

  int userX;
  int userY;
  for (int i = 0; i < 4; ++i) {
    cin >> userX;
    cin >> userY;
    Point start{userX, userY};
    cin >> userX;
    cin >> userY;
    Point end{userX, userY};
    myRectangle.segments.push_back(Segment{start, end});
  }

  if (myRectangle.evaluate()) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

    return 0;
}
