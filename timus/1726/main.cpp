#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

namespace {

size_t ComputeContribution(const std::vector<size_t>& coords) {
  size_t number_of_houses = coords.size();

  std::vector<size_t> prefix(number_of_houses + 1, 0);

  for (size_t i = 0; i < number_of_houses; ++i) {
    prefix[i + 1] = prefix[i] + coords[i];
  }

  size_t total = 0;

  for (size_t i = 0; i < number_of_houses; ++i) {
    size_t sum_before = prefix[i];
    size_t sum_after = prefix[number_of_houses] - prefix[i + 1];
    size_t contribution_before = ((coords[i] * i) - sum_before);
    size_t contribution_after = (sum_after - (coords[i] * (number_of_houses - 1 - i)));
    total += contribution_before + contribution_after;
  }
  return total;
}
}  // namespace

int main() {
  size_t number_of_houses = 0;
  std::cin >> number_of_houses;

  std::vector<size_t> x_coords(number_of_houses);
  std::vector<size_t> y_coords(number_of_houses);

  for (size_t i = 0; i < number_of_houses; ++i) {
    std::cin >> x_coords[i];
    std::cin >> y_coords[i];
  }

  std::sort(x_coords.begin(), x_coords.end());
  std::sort(y_coords.begin(), y_coords.end());

  size_t sum_x = ComputeContribution(x_coords);
  size_t sum_y = ComputeContribution(y_coords);

  size_t total = sum_x + sum_y;
  std::cout << total / (number_of_houses * (number_of_houses - 1)) << '\n';
  return 0;
}
