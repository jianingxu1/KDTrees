#include "Point.h"

Point::Point() {}

Point::Point(const std::vector<float> &coords) : coords(coords) {}

float Point::distanceTo(const Point &other) const {
  if (coords.size() != other.coords.size()) {
    // Handle error: Points have different dimensions.
    throw std::invalid_argument("Points have different dimensions.");
  }

  float sumOfSquares = 0.0;
  for (int i = 0; i < coords.size(); ++i) {
    float diff = coords[i] - other.coords[i];
    sumOfSquares += diff * diff;
  }

  return std::sqrt(sumOfSquares);
}