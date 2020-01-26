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

struct LetterA {
  vector<Segment> segments;

  bool evaluate() {
    // first do any segments share a point
    int middleSeg;
    Point sharedPoint;
    Point legA;
    Point legB;
    if (segments[0].sharePoint(segments[1], sharedPoint, legA, legB)) {
      // do something
      middleSeg = 2;
    } else if (segments[0].sharePoint(segments[2], sharedPoint, legA, legB)) {
      // do something
      middleSeg = 1;
    } else if (segments[1].sharePoint(segments[2], sharedPoint, legA, legB)) {
      // do something
      middleSeg = 0;
    } else {
      return false; // no common point found
    }

    if (crossProduct(legA, legB) == 0 || dotProduct(legA, legB) < 0) {
      return false;
    }

    if (crossProduct(legA, segments[middleSeg].start - sharedPoint) == 0 &&
        dotProduct(legB, segments[middleSeg].start - sharedPoint) >= 0) {
      if (crossProduct(legB, segments[middleSeg].end - sharedPoint) == 0 &&
          dotProduct(legA, segments[middleSeg].end - sharedPoint) >= 0) {
        auto ratioA = getRatio(legA, segments[middleSeg].start - sharedPoint);
        auto ratioB = getRatio(legB, segments[middleSeg].end - sharedPoint);
        if (ratioA || ratioB) {
          return false; // ratios were incorrect
        } else {
          return true;
        }
      }
    } else if (crossProduct(legA, segments[middleSeg].end - sharedPoint) == 0 &&
               dotProduct(legB, segments[middleSeg].end - sharedPoint) >= 0) {
      if (crossProduct(legB, segments[middleSeg].start - sharedPoint) == 0 &&
          dotProduct(legA, segments[middleSeg].start - sharedPoint) >= 0) {
        auto ratioA = getRatio(legA, segments[middleSeg].end - sharedPoint);
        auto ratioB = getRatio(legB, segments[middleSeg].start - sharedPoint);
        if (ratioA || ratioB) {
          return false; // ratios were incorrect
        } else {
          return true;
        }
      }
    } else {
      return false; // middle segment did not have a co linear point with leg
    }

    return false;
  }

  void print() {
    for (auto segment : segments) {
      segment.print();
      printf("\n");
    }
  }
};

int main(void)
{
  int numAs = 0;
  cin >> numAs;

  vector<LetterA> letterAs(numAs);
  int userX;
  int userY;
  for (int i = 0; i < numAs; ++i) {
    LetterA myA;
    for (int i = 0; i < 3; ++i) {
      cin >> userX;
      cin >> userY;
      Point start{userX, userY};
      cin >> userX;
      cin >> userY;
      Point end{userX, userY};
      myA.segments.push_back(Segment{start, end});
    }
    letterAs[i] = myA;
  }

  for (auto myA : letterAs) {
    if (myA.evaluate()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }

    return 0;
}
