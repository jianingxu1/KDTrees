#include "Point.h"
#include <cmath>

Point::Point() {}

Point::Point(const std::vector<float> &coords) : coords(coords) {}

float Point::distanceTo(const Point &other) const {
  if (coords.size() != other.coords.size()) {
    // Handle error: Points have different dimensions.
    throw std::invalid_argument("Points have different dimensions.");
  }

  float sumOfSquares = 0.0;
  for (int i = 0; i < (int)coords.size(); ++i) {
    float diff = coords[i] - other.coords[i];
    sumOfSquares += diff * diff;
  }

  return std::sqrt(sumOfSquares);
}

void Point::print() const {
  std::cout << '(';
  int n = this->coords.size();
  for (int i = 0; i < n; ++i) {
    if (i != n - 1)
      std::cout << this->coords[i] << ", ";
    else
      std::cout << this->coords[i] << ')';
  }
}