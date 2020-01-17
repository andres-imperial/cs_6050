// What a mess this one is
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct Coord
{
  int x;
  int y;
};

int main(void)
{
  int numCoords = 0;
  cin >> numCoords;

  vector<Coord> coords(numCoords);
  int userX;
  int userY;
  for (int i = 0; i < numCoords; ++i) {
    cin >> userX;
    cin >> userY;
    coords[i] = {userX, userY};
  }

  sort(coords.begin(), coords.end(),
       [](Coord left, Coord right) { return left.x < right.x; });

  int index1 = 0, index2 = 0;
  unsigned long long total = 0;

  while (index2 <= numCoords) {
    if (index2 == numCoords) {
      int k = index2 - index1;
      total += (unsigned long long)k * (k - 1) / 2;
      ++index2;
    } else if (coords[index1].x == coords[index2].x) {
      ++index2;
    } else {
      int k = index2 - index1;
      total += (unsigned long long)k * (k - 1) / 2;
      index1 = index2;
    }
  }

  sort(coords.begin(), coords.end(),
       [](Coord left, Coord right) { return left.y < right.y; });

  index1 = 0, index2 = 0;

  while (index2 <= numCoords) {
    if (index2 == numCoords) {
      int k = index2 - index1;
      total += (unsigned long long)k * (k - 1) / 2;
      ++index2;
    } else if (coords[index1].y == coords[index2].y) {
      ++index2;
    } else {
      int k = index2 - index1;
      total += (unsigned long long)k * (k - 1) / 2;
      index1 = index2;
    }
  }

  sort(coords.begin(), coords.end(), [](Coord left, Coord right) {
    if (left.x < right.x)
      return true;
    else if (left.x > right.x)
      return false;
    else
      return left.y < right.y;
  });

  index1 = 0, index2 = 0;

  while (index2 <= numCoords) {
    if (index2 == numCoords) {
      int k = index2 - index1;
      total -= (unsigned long long)k * (k - 1) / 2;
      ++index2;
    } else if (coords[index1].x == coords[index2].x &&
               coords[index1].y == coords[index2].y) {
      ++index2;
    } else {
      int k = index2 - index1;
      total -= (unsigned long long)k * (k - 1) / 2;
      index1 = index2;
    }
  }

  printf("%lli", total);

  return 0;
}
