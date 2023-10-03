#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>

struct Point {
  std::vector<float> coords;
  Point();
  Point(const std::vector<float> &coords);

  // Function to calculate the Euclidean distance between two points
  float distanceTo(const Point &other) const;
  void print() const;
};

#endif  // POINT_H